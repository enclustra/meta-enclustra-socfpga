/** \file GenericPackageHandler.h
* Header file for the CGenericPackageHandler class.
* \author Tiago Gomes
* \date 24.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "MemoryMappedPackage.h"
#include "AsyncPackage.h"
#include "ErrorPackage.h"
#include "PrintPackage.h"

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class for the CPackageHandler
*/
class CGenericPackageHandler
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:

	//-------------------------------------------------------------------------------------------------
	// Public Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Get the name of the object for logging purposes
	*
	* \returns									Name of the class instance
	*/
	virtual std::string GetName() = 0;

	/**
	* \brief Sends a Memory Mapped Package
	*
	* \param[in]	MemoryMappedPackage			A Memory Mapped Package object
	*/
	virtual void SendPackage(CMemoryMappedPackage & MemoryMappedPackage) = 0;

	/**
	* \brief Sends a Async Package
	*
	* \param[in]	AsyncPackage			A Async Package object
	*/
	virtual void SendPackage(CAsyncPackage & AsyncPackage) = 0;

	/**
	* \brief Sends a Error Package
	*
	* \param[in]	ErrorPackage			A Error Package object
	*/
	virtual void SendPackage(CErrorPackage & ErrorPackage) = 0;

	/**
	* \brief Sends a Print Package
	*
	* \param[in]	PrintPackage			A Print Package object
	*/
	virtual void SendPackage(CPrintPackage & PrintPackage) = 0;

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
	virtual uint32_t ReceivePackage(CMemoryMappedPackage& Package) = 0;

	/**
	* \brief Flushes the COM Port, should be used when ReceivePackage() returns an error so all the remaining data can be discarded
	*
	*/
	virtual void DiscardData() = 0;
};
