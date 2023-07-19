/** \file LinuxComPort.h
* Header file for the MBComPort class.
* \author Matthias Frei
* \date 6.12.2017
*
* Copyright (c) 2017 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "ICommunicationInterface.h"
#include <iostream>

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class for the MBComPort Interface
*/
class CLinuxComPort : public ICommunicationInterface
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Constructor
	*
	*/
	CLinuxComPort();

	~CLinuxComPort();

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Open COM port
	*
	* \param port[in]				device name, example "/dev/ttyUSB0" or "COM4"
	* \param baud_rate[in]			communication speed, example 9600 or 115200
	* \param char_size[in]			set data size
	* \param parity[in]				set parity bit
	* \param stopBits[in]			set number of stop bits
	* \param flowControl[in]		set flow control bit
	* \param RxBufferSize[in]		set the maximum number of bytes that can be read using a single ReadData() call
	*
	*/
	void OpenPort(const std::string& port,
		const uint32_t baud_rate,
		const ECharacter_size_t char_size,
		const EParity_t parity,
		const EStop_bits_t stopBits,
		const EFlow_control_t flowControl,
		const uint32_t RxBufferSize);

	/**
	* \brief Close COM port
	*
	*/
	void ClosePort();

	/**
	* \brief Send Data through COM port
	*
	* \param[in] data				Data to send
	*/
	void SendData(const vector <uint8_t>& data);

	/**
	* \brief Checks if there is data available to read in the COM port
	*
	* \returns						TRUE if there is valid data to read in the COM port
	*/
	bool CheckDataIsAvailable();

	/**
	* \brief Receive Data from COM port
	*
	* \param[in] data				Data vector where received data will be stored
	* \param[in] size				Intended size of the data received
	*
	* \returns						Size of received data, if COM port has less than the intended size
	*/
	uint32_t ReceiveData(vector <uint8_t> &data, const uint32_t size);

	/**
	* \brief Check if COM port is open
	*
	* \ returns					TRUE if COM port is open, FALSE if closed
	*/
	bool IsOpen();

	/**
	* \brief Discard Data currently present on COM port
	*
	*/
	void DiscardData();

	void SetBootActive(bool active);

	string GetBootlog();

private: 
	string m_StringBuffer;

	bool m_isOpen;
	int m_fileDesc;

};
