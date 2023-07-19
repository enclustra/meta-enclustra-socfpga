//-----------------------------------------------------------------------------
// Copyright (c) 2023 Enclustra GmbH, Switzerland (info@enclustra.com)
//-----------------------------------------------------------------------------

#pragma once

#include <cstdint>

// registers
//---------------------------------------------------------
static const uint32_t REG_CTRL                   = 0x00;
static const uint32_t REG_STATUS                 = 0x04;
static const uint32_t REG_CFG                    = 0x08;
static const uint32_t REG_INFO_REFCLK            = 0x2000;
static const uint32_t REG_INFO_CHANNELS          = 0x3000;

static const uint32_t REG_TX_BIT_COUNT_LANE_0_LO = 0x10;
static const uint32_t REG_TX_BIT_COUNT_LANE_0_HI = 0x14;
static const uint32_t REG_ERROR_COUNT_LANE_0_LO  = 0x18;
static const uint32_t REG_ERROR_COUNT_LANE_0_HI  = 0x1C;

static const uint32_t REG_TX_BIT_COUNT_LANE_1_LO = 0x20;
static const uint32_t REG_TX_BIT_COUNT_LANE_1_HI = 0x24;
static const uint32_t REG_ERROR_COUNT_LANE_1_LO  = 0x28;
static const uint32_t REG_ERROR_COUNT_LANE_1_HI  = 0x2C;

static const uint32_t REG_TX_BIT_COUNT_LANE_2_LO = 0x30;
static const uint32_t REG_TX_BIT_COUNT_LANE_2_HI = 0x34;
static const uint32_t REG_ERROR_COUNT_LANE_2_LO  = 0x38;
static const uint32_t REG_ERROR_COUNT_LANE_2_HI  = 0x3C;

static const uint32_t REG_TX_BIT_COUNT_LANE_3_LO = 0x40;
static const uint32_t REG_TX_BIT_COUNT_LANE_3_HI = 0x44;
static const uint32_t REG_ERROR_COUNT_LANE_3_LO  = 0x48;
static const uint32_t REG_ERROR_COUNT_LANE_3_HI  = 0x4C;

static const uint32_t REG_TX_BIT_COUNT_LANE_4_LO = 0x50;
static const uint32_t REG_TX_BIT_COUNT_LANE_4_HI = 0x54;
static const uint32_t REG_ERROR_COUNT_LANE_4_LO  = 0x58;
static const uint32_t REG_ERROR_COUNT_LANE_4_HI  = 0x5C;

static const uint32_t REG_TX_BIT_COUNT_LANE_5_LO = 0x60;
static const uint32_t REG_TX_BIT_COUNT_LANE_5_HI = 0x64;
static const uint32_t REG_ERROR_COUNT_LANE_5_LO  = 0x68;
static const uint32_t REG_ERROR_COUNT_LANE_5_HI  = 0x6C;

static const uint32_t REG_PLL_STATUS             = 0x70;
static const uint32_t REG_DATARATE               = 0x74;


// bit mask/offset definitions
//----------------------------------------------------

// offset for result registers between 2 channels
static const uint32_t RESULT_LANE_OFFSET         = 0x10;

// control register
static const uint32_t CTRL_START                 = 0x01;

// status register
static const uint32_t RSLT_NOT_STARTED           = 0x00;
static const uint32_t RSLT_RUNNING               = 0x01;
static const uint32_t RSLT_FAILED                = 0x02;
static const uint32_t RSLT_WRONG_CONFIG          = 0x04;
static const uint32_t RSLT_SUCCESS               = 0x08;

// config register
static const uint32_t CFG_MASK                   = 0xFF;
static const uint32_t CFG_DURATION_SHIFT         = 0;
static const uint32_t CFG_DEVICE_SHIFT           = 8;

// device definitions
static const uint32_t DEVICE_ARRIA10             = 0x0A;
static const uint32_t DEVICE_CYCLONEV            = 0x05;
