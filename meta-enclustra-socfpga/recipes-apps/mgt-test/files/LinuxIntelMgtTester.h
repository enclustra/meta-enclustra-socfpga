//-----------------------------------------------------------------------------
// Copyright (c) 2023 Enclustra GmbH, Switzerland (info@enclustra.com)
//-----------------------------------------------------------------------------

#pragma once

#include "RunnableTest.h"

class LinuxIntelMgtTester : public RunnableTest
{

public:

    virtual void Work();

private:

    struct result
    {
        uint64_t bit_counter;
        uint64_t error_counter;
    };

    // register read/write
    uint32_t GetInfoRefclkReg(uint32_t address);
    uint32_t GetInfoChannelReg(uint32_t address);
    uint8_t GetPllReg(uint32_t address);
    void SetPllReg(uint32_t address, uint8_t data);
    uint8_t GetMgtReg(uint32_t instance, uint32_t address);
    void SetMgtReg(uint32_t instance, uint32_t address, uint8_t data);
    void ModifyMgtReg(uint32_t instance, uint32_t address, uint8_t data, uint8_t mask);

    // test execution
    void EnableReset(uint32_t instance);
    void ReleaseReset(uint32_t instance);
    bool GetPllLockStatus();
    int PllCalibration();
    uint32_t GetDataRateMbps(uint32_t refclk);
    void SaveSleep(unsigned milliSeconds);

    int ChannelCalibration(uint32_t instance);
    void Configuration(uint32_t instance);
    void StartCounter(uint32_t instance);
    void StopCounter(uint32_t instance);
    struct result GetResult(uint32_t instance);

};
