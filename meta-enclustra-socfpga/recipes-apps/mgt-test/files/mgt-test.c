#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>

#define MGT_BASE    0xFF280000
#define MGT_LEN     0x1000
#define VERSION     "0.2"

uint32_t* mem = NULL;
off_t page_offset = 0;

uint32_t mem_read(uint32_t offset)
{
    uint32_t addr = (page_offset + offset) / sizeof(uint32_t);
    uint32_t retval = mem[addr];
    printf("    Read  0x%08x from 0x%08x\r\n", retval, addr);
    return retval;
}

void mem_write(uint32_t offset, uint32_t value)
{
    uint32_t addr = (page_offset + offset) / sizeof(uint32_t);
    printf("    Write 0x%08x  to  0x%08x\r\n", value, addr);
    mem[addr] = value;
}

void mem_modify(uint32_t offset, uint32_t value, uint32_t mask)
{
    uint32_t val = mem_read(offset);
    val = (val & ~mask) | (value & mask);
    mem_write(offset, val);
}

int mem_init()
{
    size_t pagesize = sysconf(_SC_PAGE_SIZE);
    off_t page_base = (MGT_BASE / pagesize) * pagesize;
    page_offset = MGT_BASE - page_base;

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    mem = (uint32_t*)mmap(NULL, page_offset + MGT_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, page_base);
    if (mem == MAP_FAILED) {
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
    printf("MGT test version %s\r\n", VERSION);

    // Check access
    mem_read(0x200 * 4);
    mem_read(0x204 * 4);
    mem_read(0x205 * 4);
    mem_read(0x210 * 4);
    mem_read(0x211 * 4);
    mem_read(0x212 * 4);

    // Request bus access


    // Enable reset
    printf("Enable reset\r\n");
    mem_write(0x2e2 * 4, 0xf0); // get software control of reset
    mem_write(0x2e2 * 4, 0xfa); // enable digital reset
    mem_write(0x2e2 * 4, 0xff); // enable analog reset

    // Enable PRBS 31 generator in 64bit mode
    printf("Enable PRBS generator\r\n");
    mem_modify(0x006 * 4, 0x44, 0xcf);
    mem_modify(0x007 * 4, 0x00, 0xf0);
    mem_modify(0x008 * 4, 0x10, 0x70);
    mem_modify(0x110 * 4, 0x03, 0x07);

    // Enable PRBS 31 checker in 64bit mode
    printf("Enable PRBS checker\r\n");
    mem_modify(0x00a * 4, 0x80, 0x80);
    mem_modify(0x00b * 4, 0x0c, 0xfc);
    mem_modify(0x00c * 4, 0x01, 0x01);
    mem_modify(0x13f * 4, 0x0e, 0x0f);

    // Release reset
    printf("Release reset\r\n");
    mem_write(0x2e2 * 4, 0xfa);
    mem_write(0x2e2 * 4, 0xf0);

    // Enable PRBS counter
    printf("Enable PRBS counter\r\n");
    mem_modify(0x300 * 4, 0x01, 0x01); // enable counter
    mem_modify(0x300 * 4, 0x02, 0x02); // reset
    mem_modify(0x300 * 4, 0x00, 0x02); // clear reset

    uint64_t start_time_ms = get_time_ms();

    // Check result
    sleep(10);

    // Capture snapshot of counter registers
    mem_modify(0x300 * 4, 0x04, 0x04);
    uint64_t end_time_ms = get_time_ms();

    uint64_t error_counter = 0;
    error_counter |= (uint64_t)mem_read(0x301 * 4);
    error_counter |= (uint64_t)mem_read(0x302 * 4) << 8;
    error_counter |= (uint64_t)mem_read(0x303 * 4) << 16;
    error_counter |= (uint64_t)mem_read(0x304 * 4) << 24;
    error_counter |= (uint64_t)mem_read(0x305 * 4) << 32;
    error_counter |= (uint64_t)mem_read(0x306 * 4) << 40;
    error_counter |= (uint64_t)mem_read(0x307 * 4) << 48;

    uint64_t bit_counter = 0;
    bit_counter |= (uint64_t)mem_read(0x30d * 4);
    bit_counter |= (uint64_t)mem_read(0x30e * 4) << 8;
    bit_counter |= (uint64_t)mem_read(0x30f * 4) << 16;
    bit_counter |= (uint64_t)mem_read(0x310 * 4) << 24;
    bit_counter |= (uint64_t)mem_read(0x311 * 4) << 32;
    bit_counter |= (uint64_t)mem_read(0x312 * 4) << 40;
    bit_counter |= (uint64_t)mem_read(0x313 * 4) << 48;

    // check if channel is locked (rx_is_lockedtodata)
    uint32_t locked_to_data = mem_read(0x280 * 4) & 0x01;
    uint32_t locked_to_ref = (mem_read(0x280 * 4) & 0x02) >> 1;

    // calculate BER and data rate
    double bit_double = (double)bit_counter;
    double error_double = (double)error_counter;
    double running_time_ms = (double)(end_time_ms - start_time_ms);

    double rate = ((bit_double / running_time_ms) / 1000) * 31; // * 31 because PRBS31
    double ber = (error_double + 1.0) / bit_double;

    printf("status after %.1f seconds:\r\n", running_time_ms/1000);
    printf("locked: clock %i, data %i\r\n", locked_to_ref, locked_to_data);
    printf("bits: %.0f, errors: %.0f\r\n", bit_double, error_double);
    printf("rate: %.0f Mbps, ber: %f\r\n", rate, ber);

    return 0;
}

int main(int argc, char *argv[])
{
    int ret = 0;
    ret = mem_init();
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

