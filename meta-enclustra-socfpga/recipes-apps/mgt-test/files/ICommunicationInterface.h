/** \file ICommunicationInterface.h
* Header file for the ICommunicationInterface interface, part of the Production Test Util.
* \author Tiago Gomes
* \date 07.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "ProductionTestUtilTypes.h"
using namespace std;

typedef enum class ECharacter_size_t {
	seven = 7,
	eight = 8
} ECharacter_size_t;

typedef enum class EParity_t {
	even = 0,
	none = 1,
	odd = 2
} EParity_t;

typedef enum class EStop_bits_t {
	one = 0,
	onepointfive = 1,
	two = 2
} EStop_bits_t;

typedef enum class EFlow_Control_t {
	none = 0,
	hardware = 1,
	software = 2
} EFlow_control_t;


//-------------------------------------------------------------------------------------------------
// Interface definition
//-------------------------------------------------------------------------------------------------

class ICommunicationInterface
{
	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:

	/**
	* \brief Open COM port
	*
	* \param port[in]				Device name, example "/dev/ttyUSB0" or "COM4"
	* \param baud_rate[in]			Sommunication speed, example 9600 or 115200
	* \param char_size[in]			Set data size
	* \param parity[in]				Set parity bit
	* \param stopBits[in]			Set number of stop bits
	* \param flowControl[in]		Set flow control bit
	* \param timeoutInMiliSec		Set the maximum time to wait for data when a Read function is called
	*
	*/
	virtual void OpenPort(const std::string& port,
		const uint32_t baud_rate,
		const ECharacter_size_t char_size,
		const EParity_t parity,
		const EStop_bits_t stopBits,
		const EFlow_control_t flowControl,
		const uint32_t timeoutInMiliSec) = 0;

	/**
	* \brief Close COM port
	*
	*/
	virtual void ClosePort() = 0;

	/**
	* \brief Send Data through COM port
	*
	* \param[in] data				Data to send
	*/
	virtual void SendData(const vector <uint8_t> & data) = 0;

	/**
	* \brief Checks if there is data available to read in the COM port
	*
	* \returns						TRUE if there is valid data to read in the COM port
	*/
	virtual bool CheckDataIsAvailable() = 0;

	/**
	* \brief Receive Data from COM port
	*
	* \param[in] data				Data vector where received data will be stored
	* \param[in] size				Intended size of the data received
	*
	* \returns						Size of received data, if COM port has less than the intended size
	*/
	virtual uint32_t ReceiveData(vector <uint8_t> &data, const uint32_t size) = 0;

	/**
	* \brief Check if COM port is open
	*
	* \ returns					TRUE if COM port is open, FALSE if closed
	*/
	virtual bool IsOpen() = 0;

	/**
	* \brief Discard Data currently present on COM port
	*
	*/
	virtual void DiscardData() = 0;

	/**
	* \brief Activate/Deactivate boot logging
	*
	*/
	virtual void SetBootActive(bool active) = 0;

	/**
	* \brief Obtain previously recorded bootlog data
	*
	*/
	virtual string GetBootlog() = 0;

};
