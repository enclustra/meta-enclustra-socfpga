/** \file ProductionTestUtilTypes.h
* \brief Header file for types defined for use by the Production Test Util project
* \author Tiago Gomes
* \date 11.07.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//#include <iostream>
#include <string>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <algorithm> // std::remove

/**
Here we bring the <cstdint> types into scope - code will most likely compile even if we don't do this, but it's bad
practice because we can't guarantee that the implementation will put the symbols in the global namespace.
*/

using std::int8_t;
using std::int16_t;
using std::int32_t;
using std::int64_t;
using std::uint8_t;
using std::uint16_t;
using std::uint32_t;
using std::uint64_t;
using std::size_t;

typedef enum {
	EEthTest = 0,		 /*!< Ethernet Test		*/
	EAxiIoTest = 1,		 /*!< AXI IO Test		*/
	EAxiMemoryTest = 2,  /*!< AXI Memory Test	*/
	EXadcTest = 3,		 /*!< XADC Test			*/
	EFlashSpiTest = 4,	 /*!< Flash SPI Test	*/
	EAxiClockTest = 5,	 /*!< AXI Clock Test 	*/
	ELinuxMemtester = 6, /*!< Linux Memtester   */
	ELinuxMtdTester = 7, /*!< Linux MTD Tester	*/
	ELinuxStorageTester = 8, /*!< Linux Storage Tester	*/
	ELinuxI2cTester = 9, /*!< Linux I2C Tester */
	EGroupTest = 10,	 	 /*!< Group Test */
	ELinuxIperfTester = 11, 	/*!< Linux Iperftester 	*/
	ELinuxSysmonTester = 12,
	EBramSpeedTest = 13,     /*!< for Speedtesting purpose only*/
	EAxiVersionTest = 14,     /*!< Axi Version Test*/
	EI2cTest = 15,   /*!< Axi Version Test*/
	EFx3LoopbackTest = 16,     /*!< Fx3Loopback Test*/
	ELedTest = 17,			    /*!< Led Test*/
	EAxiSpiFlashTest = 18,     /*!< AXI SPI Flash Test*/
	ELinuxVersionTest = 19,     /*!< Linux Version Test*/
	EUbootTest = 20,           /*!< Uboot Test*/
	EIntelTemperatureTest = 21 ,          /*!< Intel Temperature Test*/
	EClimateChamber = 22,			/*!< Not a Test, but like a Test*/
	EAxiMgtTest = 23,
    EVideoTest = 24,           /*!< Video Test*/
	ELinuxMdioTest = 25,   /*!< Mdio Test*/
	ETarget = 26,           /*!< Required for Repairsheet*/
	EEfuseTest = 27,		/*!< Efuse Test */
	EProvisioning = 28,		/*!< Provisioning */
    ELinuxPcieTester = 29,    /*!< PCIe Test*/
	ESdCardMatchTester = 30, /*!< SD card match Test*/
	ELinuxMioTest = 31, /*!< Linux MIO loopback Test*/
} EProductionTestUtilTests_t;


typedef enum class EProductionTestUtilPackages_t {
	MemoryMapped	= 0x1186F0B3,
	Async			= 0x12DE8783,
	Error			= 0x13A4D099,
	Print			= 0x14BF86A7
} EProductionTestUtilPackages_t;

typedef enum class EAsyncTypes_t {
	version = 0,
} EAsyncTypes_t;

typedef enum EObserverLevel_t {
	Critical = 1,
	Error = 2,
	Warning = 4,
	Log = 8,
	Debug = 16,
	Notice = 32,
	All = 63,
	Boot = 0x1000,
} EObserverLevel_t;

typedef struct ExceptionHandling_t {
	bool catched;
	bool parsingXmlFailed;
//	std::string catchedBy;
} ExceptionHandling_t;

typedef enum ETesterUser_t {
	EUserBasic = 1,
	EUserSophisticated
} ETesterUser_t;

typedef enum ETargetTestMode_t {
	ERunTestFull=1,
	ERunTestWithReset,
	ERunTestOnly
}ETargetTestMode_t;

typedef struct ETargetFx3Match_t {
	std::string targetName ="";
	std::string fx3SerialNr ="";
}ETargetFx3Match_t;

typedef enum ETargetStatus_t {
	ETargetNotStarted = 0x00,
	ETargetTestRunning = 0x01,
	ETargetTestFailed = 0x04,
	ETargetTestPassed = 0x08,
	ETargetTestException = 0x10,
	ETargetTestSevereFailure = 0x20,
	ETargetTestOvercurrent = 0x40,
	ETargetTestOvercurrentFailed = 0x44
} ETargetStatus_t;

typedef struct s_BurnInTestStage {
	std::string stageName;
	int32_t nominalTemperature;
	int32_t nominalHumidity;
	uint32_t durationMin;
	std::string testName;
	uint32_t endlessLoops;
	ETargetTestMode_t testMode;
	uint32_t resetIfFailed;
	bool testRunPresent;
	bool dewProtection;
	bool airDryerActive;
}s_BurnInTestStage;

typedef enum EPowerSupplyStatus_t {
	EOutputOff = 0x00,
	EOnCVMode = 0x01,
	EOnCCMode = 0x02,
	EStateUnknown = 0xff,
} EPowerSupplyStatus_t;


