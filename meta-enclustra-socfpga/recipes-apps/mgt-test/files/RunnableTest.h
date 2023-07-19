/** \file RunnableTest.h
* Header file for the runnable linux test
* \author Sven Huerlimann
* \date 06.03.2017
*
* Copyright (c) 2017 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <cstdint>
#include <thread>
#include <utility>
#include <atomic>
#include <errno.h>
#include <unistd.h>

#include "IRegisterInterface.h"

#ifdef __MICROBLAZE__
#include "TimerInterface.h"
#endif

static const uint32_t REG_CTRL_OFS				= 0x00;

static const uint32_t CTRL_START_MASK 			= 0x00000001;
static const uint32_t CTRL_ABORT_MASK           = 0x00000002;

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class RunnableTest. All linux testers should inherit from this class
*/
class RunnableTest
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	RunnableTest()
	 : started(false){
	}

#ifndef __MICROBLAZE__
	virtual ~RunnableTest() {
		if(mThread.joinable()) {
			mThread.join();
		}
	}
#endif

	//-------------------------------------------------------------------------------------------------
	// Public Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Do the test. Must be overriden by the tester class implementation
	*
	*/
	virtual void Work() = 0;


	/**
	 * \brief BusyWait loop. Checks the control register for abort or start flag. If started runs the test,
	 * 	      then continues with the busywait loop again. If aborted it returns.
	 */
	void BusyWait() {
		uint32_t ctrlReg = 0;

		while(1)
		{
			// busy wait while not start or abort
			do
			{
				usleep(500000);
				ReadMem(REG_CTRL_OFS, ctrlReg);
			} while (!(ctrlReg & (CTRL_ABORT_MASK | CTRL_START_MASK)));

			// if it is aborted -> return
			if (ctrlReg & CTRL_ABORT_MASK)
			{
				WriteMem(REG_CTRL_OFS, 0);
				return;
			}

			// if it is started -> run the test, continue with busy-wait loop
			if (ctrlReg & CTRL_START_MASK)
			{
				// clear start bit
				//ctrlReg &= ~(CTRL_START_MASK);
				//WriteMem(REG_CTRL_OFS, ctrlReg);
				// do some work
				(this)->Work();
			}
		}
	}

	/**
	* \brief Setup the test
	*
	* \param RegisterInterface_p		Pointer to register interface
	* \param regOffset					Register address
	* \param regSize					Size of the register memory region
	*/
	void Setup(IRegisterInterface* RegisterInterface_p, uint32_t regOffset, uint32_t regSize) {
		mRegOffset = regOffset;
		mRegisterInterface = RegisterInterface_p;
		mRegSize = regSize;
	}

	/**
	* \brief Run the test. This will start the test in a new thread
	*
	*/
#ifndef __MICROBLAZE__
	void Run() {
		started = true;
		mThread = std::thread(&RunnableTest::BusyWait, this);
	}

	/**
	* \brief Tear down the test
	*
	*/
	virtual void TearDown() {
		if(mThread.joinable()) {
			mThread.join();
		}return;
	};
#endif

	/**
	 * \brief Writes to the tester memory. Verifies that this address is inside the testers memory region
	 *
	 * \param offset	offset of the register
	 * \param value		value to be written
	 */
	int WriteMem(uint32_t offset, uint32_t value)
	{
		if(offset < mRegSize)
		{
			mRegisterInterface->Write(offset + mRegOffset, value);
		}
		else
		{
			return EACCES;
		}
		return 0;
	}

	/**
	 * \brief Reads value from the tester memory. Verifies that the address is inside the testers memory region
	 *
	 * \param offset		offset of the register
	 * \return 				value from the register
	 */
	uint32_t ReadMem(uint32_t offset, uint32_t& value)
	{
		if(offset < mRegSize)
		{
			value = mRegisterInterface->Read(offset + mRegOffset);
		}
		else
		{
			return EACCES;
		}
		return 0;
	}

	//-------------------------------------------------------------------------------------------------
	// Member variables
	//-------------------------------------------------------------------------------------------------
protected:

	/// Pointer to memory interface
	IRegisterInterface* mRegisterInterface;

	/// Offset of the tester
	uint32_t mRegOffset;

	/// Size of register bank
	uint32_t mRegSize;

private:
	/// Pointer to register bank area of tester
	//uint32_t* mRegMem;
#ifndef __MICROBLAZE__
	/// Thread that is currently doing work
	std::thread mThread;
#endif
	/// If thread is currently running
	std::atomic<bool> started;
};



