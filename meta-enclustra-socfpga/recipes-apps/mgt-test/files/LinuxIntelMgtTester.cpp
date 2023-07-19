//-----------------------------------------------------------------------------
// Copyright (c) 2023 Enclustra GmbH, Switzerland (info@enclustra.com)
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <math.h>

#include "LinuxIntelMgtTester.h"
#include "IntelMgtTesterRegisterDefinitions.h"


// Address offset of block memory
static const uint32_t BLOCKMEM_OFFSET        = 0x00000000;
static const uint32_t BLOCKMEM_ADDRESS_RANGE = 0x00001000;

// Address offset of fPLL reconfiguration interface
static const uint32_t PLL_OFFSET             = 0x00001000;
static const uint32_t PLL_ADDRESS_RANGE      = 0x00001000;

// Address offset of System ID storing reference clock frequency
static const uint32_t INFO_REFCLK_OFFSET     = 0x00002000;
static const uint32_t INFO_REFCLK_RANGE      = 0x00000008;

// Address offset of System ID storing number of channels
static const uint32_t INFO_CHANNEL_OFFSET    = 0x00003000;
static const uint32_t INFO_CHANNEL_RANGE     = 0x00000008;

// Address offset of XCVR reconfiguration interface (6 x back to back)
static const uint32_t MGT_OFFSET             = 0x00008000;
static const uint32_t MGT_ADDRESS_RANGE      = 0x00001000;


uint32_t LinuxIntelMgtTester::GetInfoRefclkReg(uint32_t address)
{
    uint32_t readData = 0;
    ReadMem(INFO_REFCLK_OFFSET + address, readData);
    return readData;
}

uint32_t LinuxIntelMgtTester::GetInfoChannelReg(uint32_t address)
{
    uint32_t readData = 0;
    ReadMem(INFO_CHANNEL_OFFSET + address, readData);
    return readData;
}

// Following methods are used to access the transceiver registers.
// A register map can be found in following link:
// https://www.intel.com/content/www/us/en/docs/programmable/683617/21-1/transceiver-register-map.html
// Note that in the register map the addresses for the fPLL are written as "F.0x000" and the addresses for the XCVR PHY as "C.0x000"

uint8_t LinuxIntelMgtTester::GetPllReg(uint32_t address)
{
    uint32_t readData = 0;
    ReadMem(PLL_OFFSET + address, readData);
    return static_cast<uint8_t>(readData);
}

void LinuxIntelMgtTester::SetPllReg(uint32_t address, uint8_t data)
{
    WriteMem(PLL_OFFSET+ address, static_cast<uint32_t>(data));
}

uint8_t LinuxIntelMgtTester::GetMgtReg(uint32_t instance, uint32_t address)
{
    uint32_t readData = 0;
    uint32_t offset = MGT_OFFSET + (instance * MGT_ADDRESS_RANGE);
    ReadMem(offset + address, readData);
    return static_cast<uint8_t>(readData);
}

void LinuxIntelMgtTester::SetMgtReg(uint32_t instance, uint32_t address, uint8_t data)
{
    uint32_t offset = MGT_OFFSET + (instance * MGT_ADDRESS_RANGE);
    WriteMem(offset + address, static_cast<uint32_t>(data));
}

void LinuxIntelMgtTester::ModifyMgtReg(uint32_t instance, uint32_t address, uint8_t data, uint8_t mask)
{
    uint8_t value = GetMgtReg(instance, address);
    value = (value & ~mask) | (data & mask);
    SetMgtReg(instance, address, value);
}

bool LinuxIntelMgtTester::GetPllLockStatus()
{
    uint8_t lock = GetPllReg(0x280 * 4) & 0x01;
    return static_cast<bool>(lock);
}

int LinuxIntelMgtTester::PllCalibration()
{
    // See section "7.5.2. Fractional PLL Recalibration"
    // in "Intel® Arria® 10 Transceiver PHY User Guide"
    // https://www.intel.com/content/www/us/en/docs/programmable/683617/20-1/introduction.html
    
    // Check bus access
    uint8_t busy = GetPllReg(0x280 * 4) & 0x04;
    if (busy)
    {
        return -1;
    }

    // PLL recalibration
    SetPllReg(0x100 * 4, 0x02);
    SetPllReg(0x000 * 4, 0x01);

    // Wait until calibration has finished
    while (1)
    {
        uint8_t status = GetPllReg(0x280 * 4) & 0x06;
        if (status == 0x00)
        {
            break;
        }
        sleep(1);
    }

    return 0;
}

uint32_t LinuxIntelMgtTester::GetDataRateMbps(uint32_t refclk)
{
    // See section "3.1.3 fPLL"
    // in "Intel® Arria® 10 Transceiver PHY User Guide"
    // https://www.intel.com/content/www/us/en/docs/programmable/683617/20-1/introduction.html
    //
    // VCO-freq = 2 * M * input-reference-clock / N.
    // TX-PMA-frequency = data-rate = VCO-freq / L
    uint32_t pll_m = ((static_cast<uint32_t>(GetPllReg(0x12c * 4)) & 0x01) << 8) | static_cast<uint32_t>(GetPllReg(0x12b * 4));
    uint32_t pll_n = (static_cast<uint32_t>(GetPllReg(0x12c * 4)) >> 3) & 0x1f;
    uint32_t pll_l = static_cast<uint32_t>(powf(2.0, static_cast<float>((GetPllReg(0x12c * 4) >> 1) & 0x03)));
    double data_rate = 2.0 * static_cast<double>(refclk) / 1000000.0 / pll_n * pll_m / pll_l;
    return static_cast<uint32_t>(data_rate);
}

int LinuxIntelMgtTester::ChannelCalibration(uint32_t instance)
{
    // See section "7.5.4. PMA Recalibration"
    // in "Intel® Arria® 10 Transceiver PHY User Guide"
    // https://www.intel.com/content/www/us/en/docs/programmable/683617/20-1/introduction.html

    // Check bus access
    uint8_t busy = GetMgtReg(instance, 0x281 * 4) & 0x04;
    if (busy)
    {
        return -1;
    }

    // Channel calibration
    SetMgtReg(instance, 0x100 * 4, 0x22);
    SetMgtReg(instance, 0x000 * 4, 0x01);

    // Wait until calibration has finished
    while (1)
    {
        uint8_t status = GetMgtReg(instance, 0x281 * 4) & 0x07;
        if (status == 0x00)
        {
            break;
        }
        sleep(1);
    }

    return 0;
}

void LinuxIntelMgtTester::EnableReset(uint32_t instance)
{
    // See "6.8. Steps to Perform Dynamic Reconfiguration"
    // in "Intel® Arria® 10 Transceiver PHY User Guide"
    // https://www.intel.com/content/www/us/en/docs/programmable/683617/20-1/introduction.html
    //
    // Not sure if analog reset and digital reset needs to be separated, but it seems to work like that
    SetMgtReg(instance, 0x2e2 * 4, 0xf0); // get software control of reset
    SetMgtReg(instance, 0x2e2 * 4, 0xfa); // enable digital reset
    SaveSleep(1);
    SetMgtReg(instance, 0x2e2 * 4, 0xff); // enable analog reset

    // Sleep is required here, not mentioned in documentation
    SaveSleep(1000);
}

void LinuxIntelMgtTester::ReleaseReset(uint32_t instance)
{
    // See "4.3.1.4. Resetting the Transceiver Channel During Device Operation"
    // in "Intel® Arria® 10 Transceiver PHY User Guide"
    // https://www.intel.com/content/www/us/en/docs/programmable/683617/20-1/introduction.html

    // Release TX analog reset
    SetMgtReg(instance, 0x2e2 * 4, 0xfb);
    SaveSleep(1);

    // Release TX digital reset
    SetMgtReg(instance, 0x2e2 * 4, 0xf3);
    SaveSleep(1);

    // Release RX analog reset
    SetMgtReg(instance, 0x2e2 * 4, 0xfa);
    SaveSleep(1);

    // Release RX digital reset
    SetMgtReg(instance, 0x2e2 * 4, 0xf0);
    SaveSleep(1);
}

void LinuxIntelMgtTester::Configuration(uint32_t instance)
{
    // See "Example 6. Enabling the PRBS31 pattern generator in 64-bit mode"
    // and "Example 10. Enabling the PRBS31 pattern checker in 64-bit mode"
    // in "Intel® Arria® 10 Transceiver PHY User Guide"
    // https://www.intel.com/content/www/us/en/docs/programmable/683617/20-1/introduction.html

    // Enable PRBS 31 generator in 64bit mode
    ModifyMgtReg(instance, 0x006 * 4, 0x44, 0xcf);
    ModifyMgtReg(instance, 0x007 * 4, 0x00, 0xf0);
    ModifyMgtReg(instance, 0x008 * 4, 0x10, 0x70);
    ModifyMgtReg(instance, 0x110 * 4, 0x03, 0x07);

    // Enable PRBS 31 checker in 64bit mode
    ModifyMgtReg(instance, 0x00a * 4, 0x80, 0x80);
    ModifyMgtReg(instance, 0x00b * 4, 0x0c, 0xfc);
    ModifyMgtReg(instance, 0x00c * 4, 0x01, 0x01);
    ModifyMgtReg(instance, 0x13f * 4, 0x0e, 0x0f);
}

void LinuxIntelMgtTester::StartCounter(uint32_t instance)
{
    // Enable PRBS counter
    ModifyMgtReg(instance, 0x300 * 4, 0x05, 0x05); // enable counter
    ModifyMgtReg(instance, 0x300 * 4, 0x02, 0x02); // reset
    ModifyMgtReg(instance, 0x300 * 4, 0x00, 0x02); // clear reset
}

void LinuxIntelMgtTester::StopCounter(uint32_t instance)
{
    // Disable PRBS counter
    ModifyMgtReg(instance, 0x300 * 4, 0x00, 0x01);
}

struct LinuxIntelMgtTester::result LinuxIntelMgtTester::GetResult(uint32_t instance)
{
    struct result data;

    // Both error and bit counters are split into 7 individual 8-bit registers
    data.error_counter = 0;
    data.error_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x301 * 4));
    data.error_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x302 * 4)) << 8;
    data.error_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x303 * 4)) << 16;
    data.error_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x304 * 4)) << 24;
    data.error_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x305 * 4)) << 32;
    data.error_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x306 * 4)) << 40;
    data.error_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x307 * 4)) << 48;

    data.bit_counter = 0;
    data.bit_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x30d * 4));
    data.bit_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x30e * 4)) << 8;
    data.bit_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x30f * 4)) << 16;
    data.bit_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x310 * 4)) << 24;
    data.bit_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x311 * 4)) << 32;
    data.bit_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x312 * 4)) << 40;
    data.bit_counter |= static_cast<uint64_t>(GetMgtReg(instance, 0x313 * 4)) << 48;

    // Always 64 bits are tested at once.
    // To get the correct amount of data, the counter needs to be multiplied with 64.
    // This is not clearly documented by Intel but this gives the same result as the transceiver toolkit
    data.bit_counter *= 64;

    return data;
}

void LinuxIntelMgtTester::SaveSleep(unsigned milliSeconds)
{
    // Make sure sleep does not terminate too early when it gets interrupted by a signal
    timespec requested, remaining;
    remaining.tv_sec = milliSeconds/1000;
    remaining.tv_nsec = (milliSeconds % 1000) * 1000000;

    do
    {
        requested.tv_nsec = remaining.tv_nsec;
        requested.tv_sec = remaining.tv_sec;
        if (nanosleep(&requested, &remaining) == 0)
        {
            return;
        }
    }
    while (errno == EINTR);
}

void LinuxIntelMgtTester::Work()
{
    uint32_t statusReg = RSLT_RUNNING;
    WriteMem(REG_STATUS, statusReg);
    WriteMem(REG_CTRL_OFS, 0x00);

    // Get settings
    uint32_t config = 0;
    ReadMem(REG_CFG, config);
    uint8_t duration = (config >> CFG_DURATION_SHIFT) & CFG_MASK;
    uint8_t device = (config >> CFG_DEVICE_SHIFT) & CFG_MASK;
    uint8_t channels = GetInfoChannelReg(0);
    uint32_t refClk = GetInfoRefclkReg(0);

    // Check configured settings
    if ((device != DEVICE_ARRIA10) || (channels > 6))
    {
        statusReg |= RSLT_WRONG_CONFIG;
        statusReg &=~ RSLT_RUNNING;
        WriteMem(REG_STATUS, statusReg);
        return;
    }

    // Calibrate PLL
    if (PllCalibration())
    {
        statusReg |= RSLT_FAILED;
        statusReg &=~ RSLT_RUNNING;
        WriteMem(REG_STATUS, statusReg);
        return;
    }

    // Calibrate all lanes
    for (uint32_t instance=0; instance<channels; instance++)
    {
        if (ChannelCalibration(instance))
        {
            statusReg |= RSLT_FAILED;
            statusReg &=~ RSLT_RUNNING;
            WriteMem(REG_STATUS, statusReg);
            return;
        }
    }

    // Read PLL frequency
    uint32_t dataRateMbps = GetDataRateMbps(refClk);
    WriteMem(REG_DATARATE, dataRateMbps);

    // Configure PRBS generator/checker
    for (uint32_t instance=0; instance<channels; instance++)
    {
        EnableReset(instance);
        Configuration(instance);
        ReleaseReset(instance);
    }

    // Check if fPLL is locked
    bool lock = GetPllLockStatus();
    WriteMem(REG_PLL_STATUS, (lock == true) ? 1 : 0);
    if (!lock)
    {
        statusReg |= RSLT_FAILED;
        statusReg &=~ RSLT_RUNNING;
        WriteMem(REG_STATUS, statusReg);
        return;
    }

    // Run test
    for (uint32_t instance=0; instance<channels; instance++)
    {
        StartCounter(instance);
    }
    SaveSleep(static_cast<unsigned>(duration) * 1000);
    for (uint32_t instance=0; instance<channels; instance++)
    {
        StopCounter(instance);
    }

    // Get result
    for (uint32_t instance=0; instance<channels; instance++)
    {
        struct result channelResult = GetResult(instance);

        WriteMem(REG_TX_BIT_COUNT_LANE_0_LO + (instance * RESULT_LANE_OFFSET), static_cast<uint32_t>(channelResult.bit_counter & 0xFFFFFFFF));
        WriteMem(REG_TX_BIT_COUNT_LANE_0_HI + (instance * RESULT_LANE_OFFSET), static_cast<uint32_t>(channelResult.bit_counter >> 32));
        WriteMem(REG_ERROR_COUNT_LANE_0_LO + (instance * RESULT_LANE_OFFSET), static_cast<uint32_t>(channelResult.error_counter & 0xFFFFFFFF));
        WriteMem(REG_ERROR_COUNT_LANE_0_HI + (instance * RESULT_LANE_OFFSET), static_cast<uint32_t>(channelResult.error_counter >> 32));
    }

    // End of test
    statusReg |= RSLT_SUCCESS;
    statusReg &=~ RSLT_RUNNING;
    WriteMem(REG_STATUS, statusReg);

    return;
}
