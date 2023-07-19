/** \file PackageHandler.h
* Header file for the CPackageHandler class.
* \author Tiago Gomes
* \date 08.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "GenericPackageHandler.h"
#include "ICommunicationInterface.h"
#include "IAsyncType.h"
#include "Crc32.h"
#include "Observer.h"

// package commands
const uint16_t READ_CMD					= 0x0000;
const uint16_t READ_RESPONSE_CMD		= 0x8000;
const uint16_t WRITE_CMD				= 0x0001;
const uint16_t WRITE_RESPONSE_CMD		= 0x8001;
const uint16_t SETBITS_CMD				= 0x0002;
const uint16_t SETBITS_RESPONSE_CMD		= 0x8002;
const uint16_t CLEARBITS_CMD			= 0x0003;
const uint16_t CLEARBITS_RESPONSE_CMD	= 0x8003;

// package error/response codes
const uint32_t RESPONSE_SUCCESS			= 0x00000000;
const uint32_t RESPONSE_CRC_ERROR		= 0x40000000;

// CRC parameters
const uint32_t POLYNOMIAL				= 0x04C11DB7;
const uint32_t INITIAL_REMAINDER		= 0xFFFFFFFF;
const uint32_t FINAL_XOR_VALUE			= 0xFFFFFFFF;
const bool REFLECT_DATA					= true;
const bool REFLECT_REMAINDER			= true;

// Pkg Error codes	
const uint32_t VALID_PACKAGE			= 0;
const uint32_t CRC_ERROR				= 1;
const uint32_t INVALID_PACKAGE			= 2;
const uint32_t VALID_HEADER				= 3;
const uint32_t NODATA_ERROR				= 4;
const uint32_t TIMEOUT					= 5;

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class for the CPackageHandler
*/
class CPackageHandler : public CGenericPackageHandler
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:

	CPackageHandler(ICommunicationInterface* CommunicationInterface_p, IAsyncType* Async_p, IAsyncType* Error_p, IAsyncType* Print_p);

	~CPackageHandler();

	//-------------------------------------------------------------------------------------------------
	// Public Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Get the name of the object for logging purposes
	*
	* \returns									Name of the class instance
	*/
	std::string GetName();

	/**
	* \brief Sends a Memory Mapped Package
	*
	* \param[in]	MemoryMappedPackage			A Memory Mapped Package object
	*/
	void SendPackage(CMemoryMappedPackage & MemoryMappedPackage);

	/**
	* \brief Sends a Async Package
	*
	* \param[in]	AsyncPackage			A Async Package object
	*/
	void SendPackage(CAsyncPackage & AsyncPackage);

	/**
	* \brief Sends a Error Package
	*
	* \param[in]	ErrorPackage			A Error Package object
	*/
	void SendPackage(CErrorPackage & ErrorPackage);

	/**
	* \brief Sends a Print Package
	*
	* \param[in]	PrintPackage			A Print Package object
	*/
	void SendPackage(CPrintPackage & PrintPackage);

	/**
	* \brief Receives a Package
	*
	* \param[out]	identifier					Identifier of Package
	* \param[out]	cmd							Command for Memory Mapped Packages
	* \param[out]	frameNr						FrameNr for Memory Mapped Packages
	* \param[out]	addr_response_asynctype		Address or Response Code for Memory Mapped Packages, or Async type for Async Packages
	* \param[out]	payload						Payload of Package
	*
	* \returns									The result of package parsing (i.e., if the CRC received in the CRC field matches the CRC calculated locally, valid package, etc.)
	*/
	uint32_t ReceivePackage(CMemoryMappedPackage& Package);

	uint32_t ReceivePackage(CAsyncPackage & ReceivedPackage);

	/**
	* \brief Flushes the COM Port, should be used when ReceivePackage() returns an error so all the remaining data can be discarded
	*
	*/
	void DiscardData();

	void SetTimeout(uint32_t Timeout);

	/**
	* \brief Attach observer
	*
	* \param observer						Observer
	*/
	void AttachObserver(CObserver * observer);

	//-------------------------------------------------------------------------------------------------
	// Private Method declarations
	//-------------------------------------------------------------------------------------------------
private:
	/**
	* \brief Get Word of 32-bit from a vector of bytes
	*
	* \param[in]	dataVector					Vector of bytes
	* \param[in]	byteIndex					Index of first byte of the intended word
	*
	* \returns									Word of 32-bit indexed by 'byteIndex' from 'dataVector'
	*/
	uint32_t GetInt32FromVector(const vector <uint8_t>& dataVector, uint32_t byteIndex);

	/**
	* \brief Get Word of 16-bit from a vector of bytes
	*
	* \param[in]	dataVector					Vector of bytes
	* \param[in]	byteIndex					Index of first byte of the intended word
	*
	* \returns									Word of 16-bit indexed by 'byteIndex' from 'dataVector'
	*/
	uint16_t GetInt16FromVector(const vector <uint8_t>& dataVector, uint32_t byteIndex);

	//-------------------------------------------------------------------------------------------------
	// Private Members declarations
	//-------------------------------------------------------------------------------------------------
private:
	const string m_name = "PackageHandler";

	ICommunicationInterface* m_CommunicationInterface_p;

	IAsyncType* m_Async_p;
	IAsyncType* m_Error_p;
	IAsyncType* m_Print_p;

	string m_Version;

	Crc32* m_CrcEngine;
	uint32_t m_Timeout;
	CObserver * m_observer;
};
