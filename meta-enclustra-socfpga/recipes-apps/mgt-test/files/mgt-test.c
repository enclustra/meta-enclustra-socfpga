#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#define MGT_BASE    0xFF280000
#define PLL_BASE    0xff290000
#define MGT_LEN     0x1000
#define PLL_LEN     0x1000
#define REFCLK_MHZ  125
#define VERSION     "0.4"

#define debug_print(...) printf("\x1b[0m" __VA_ARGS__)
#define info_print(...) printf("\x1b[33m" __VA_ARGS__)

uint32_t* mgt_mem = NULL;
uint32_t* pll_mem = NULL;

uint32_t mem_read(uint32_t* mem, uint32_t offset)
{
    uint32_t addr = offset / sizeof(uint32_t);
    uint32_t retval = mem[addr];
    debug_print("    Read  0x%08x from 0x%08x\r\n", retval, addr);
    return retval;
}

void mem_write(uint32_t* mem, uint32_t offset, uint32_t value)
{
    uint32_t addr = offset / sizeof(uint32_t);
    debug_print("    Write 0x%08x  to  0x%08x\r\n", value, addr);
    mem[addr] = value;
}

void mem_modify(uint32_t* mem, uint32_t offset, uint32_t value, uint32_t mask)
{
    uint32_t val = mem_read(mem, offset);
    val = (val & ~mask) | (value & mask);
    mem_write(mem, offset, val);
}

int mem_init(uint32_t base, uint32_t len, uint32_t** mem)
{
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    *mem = (uint32_t*)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, base);
    if (*mem == MAP_FAILED) {
        perror("Can't map memory");
        return -1;
    }
    return 0;
}

uint64_t get_time_ms()
{
    struct timespec time;
    if (clock_gettime(CLOCK_REALTIME, &time))
    {
        return 0;
    }
    return (time.tv_sec * 1000) + (time.tv_nsec / 1000000);
}

int mgt_test()
{
    info_print("MGT test version %s\r\n", VERSION);

    // Check if fPLL is locked (read from capability register needs no bus access check)
    uint32_t lock = mem_read(pll_mem, 0x280 * 4) & 0x01;
    info_print("fPLL lock status: %i\r\n", lock);

    // Check bus access
    uint32_t busy = mem_read(pll_mem, 0x280 * 4) & 0x04;
    if (busy)
    {
        info_print("Bus is busy\r\n");
        return -1;
    }

    // PLL recalibration
    mem_write(pll_mem, 0x100 * 4, 0x02);
    mem_write(pll_mem, 0x000 * 4, 0x01);

    // Wait until calibration has finished
    while (1)
    {
        uint32_t status = mem_read(pll_mem, 0x280 * 4) & 0x06;
        if (status == 0x00)
        {
            break;
        }
        sleep(1);
    }

    // Print data rate
    uint32_t pll_m = ((mem_read(pll_mem, 0x12c * 4) & 0x01) << 8) | mem_read(pll_mem, 0x12b * 4);
    uint32_t pll_n = (mem_read(pll_mem, 0x12c * 4) >> 3) & 0x1f;
    uint32_t pll_l = (uint32_t)powf(2.0, (float)((mem_read(pll_mem, 0x12c * 4) >> 1) & 0x03));
    uint32_t data_rate = 2 * REFCLK_MHZ / pll_n * pll_m / pll_l;
    info_print("Data rate: %i Mbps\r\n", data_rate);

    // Check bus access
    busy = mem_read(mgt_mem, 0x281 * 4) & 0x04;
    if (busy)
    {
        info_print("Bus is busy\r\n");
        return -1;
    }

    // Channel calibration
    mem_write(mgt_mem, 0x100 * 4, 0x22);
    mem_write(mgt_mem, 0x000 * 4, 0x01);

    // Wait until calibration has finished
    while (1)
    {
        uint32_t status = mem_read(pll_mem, 0x281 * 4) & 0x07;
        if (status == 0x00)
        {
            break;
        }
        sleep(1);
    }

    // Enable reset
    debug_print("Enable reset\r\n");
    mem_write(mgt_mem, 0x2e2 * 4, 0xf0); // get software control of reset
    mem_write(mgt_mem, 0x2e2 * 4, 0xfa); // enable digital reset
    mem_write(mgt_mem, 0x2e2 * 4, 0xff); // enable analog reset

    sleep(1); // without sleep, we only read 0xff

    // Enable PRBS 31 generator in 64bit mode
    debug_print("Enable PRBS generator\r\n");
    mem_modify(mgt_mem, 0x006 * 4, 0x44, 0xcf);
    mem_modify(mgt_mem, 0x007 * 4, 0x00, 0xf0);
    mem_modify(mgt_mem, 0x008 * 4, 0x10, 0x70);
    mem_modify(mgt_mem, 0x110 * 4, 0x03, 0x07);

    // Enable PRBS 31 checker in 64bit mode
    debug_print("Enable PRBS checker\r\n");
    mem_modify(mgt_mem, 0x00a * 4, 0x80, 0x80);
    mem_modify(mgt_mem, 0x00b * 4, 0x0c, 0xfc);
    mem_modify(mgt_mem, 0x00c * 4, 0x01, 0x01);
    mem_modify(mgt_mem, 0x13f * 4, 0x0e, 0x0f);

    // Release reset
    debug_print("Release reset\r\n");
    mem_write(mgt_mem, 0x2e2 * 4, 0xfa);
    mem_write(mgt_mem, 0x2e2 * 4, 0xf0);

    // Enable PRBS counter
    debug_print("Enable PRBS counter\r\n");
    mem_modify(mgt_mem, 0x300 * 4, 0x01, 0x01); // enable counter
    mem_modify(mgt_mem, 0x300 * 4, 0x02, 0x02); // reset
    mem_modify(mgt_mem, 0x300 * 4, 0x00, 0x02); // clear reset

    uint64_t start_time_ms = get_time_ms();

    // Check result
    sleep(10);

    // Disable PRBS counter
    mem_modify(mgt_mem, 0x300 * 4, 0x00, 0x01);

    // Capture snapshot of counter registers
    mem_modify(mgt_mem, 0x300 * 4, 0x04, 0x04);
    uint64_t end_time_ms = get_time_ms();

    uint64_t error_counter = 0;
    error_counter |= (uint64_t)mem_read(mgt_mem, 0x301 * 4);
    error_counter |= (uint64_t)mem_read(mgt_mem, 0x302 * 4) << 8;
    error_counter |= (uint64_t)mem_read(mgt_mem, 0x303 * 4) << 16;
    error_counter |= (uint64_t)mem_read(mgt_mem, 0x304 * 4) << 24;
    error_counter |= (uint64_t)mem_read(mgt_mem, 0x305 * 4) << 32;
    error_counter |= (uint64_t)mem_read(mgt_mem, 0x306 * 4) << 40;
    error_counter |= (uint64_t)mem_read(mgt_mem, 0x307 * 4) << 48;

    uint64_t bit_counter = 0;
    bit_counter |= (uint64_t)mem_read(mgt_mem, 0x30d * 4);
    bit_counter |= (uint64_t)mem_read(mgt_mem, 0x30e * 4) << 8;
    bit_counter |= (uint64_t)mem_read(mgt_mem, 0x30f * 4) << 16;
    bit_counter |= (uint64_t)mem_read(mgt_mem, 0x310 * 4) << 24;
    bit_counter |= (uint64_t)mem_read(mgt_mem, 0x311 * 4) << 32;
    bit_counter |= (uint64_t)mem_read(mgt_mem, 0x312 * 4) << 40;
    bit_counter |= (uint64_t)mem_read(mgt_mem, 0x313 * 4) << 48;

    // Check if channel is locked (rx_is_lockedtodata)
    uint32_t locked_to_data = mem_read(mgt_mem, 0x280 * 4) & 0x01;
    uint32_t locked_to_ref = (mem_read(mgt_mem, 0x280 * 4) & 0x02) >> 1;

    // Calculate BER and data rate
    double bit_double = (double)bit_counter * 64.0;
    double error_double = (double)error_counter;
    double running_time_ms = (double)(end_time_ms - start_time_ms);
    double ber = (error_double + 1.0) / bit_double;

    info_print("Status after %.1f seconds:\r\n", running_time_ms/1000);
    info_print("Locked: clock %i, data %i\r\n", locked_to_ref, locked_to_data);
    info_print("Bits: %.0f, errors: %.0f\r\n", bit_double, error_double);
    info_print("BER: %.3e\r\n", ber);

    debug_print("Exit\r\n");
    return 0;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    ret = mem_init(MGT_BASE, MGT_LEN, &mgt_mem);
    if (ret)
    {
        return ret;
    }
    ret = mem_init(PLL_BASE, PLL_LEN, &pll_mem);
    if (ret)
    {
        return ret;
    }
    ret = mgt_test();
    if (ret)
    {
        return ret;
    }
    return 0;
}

