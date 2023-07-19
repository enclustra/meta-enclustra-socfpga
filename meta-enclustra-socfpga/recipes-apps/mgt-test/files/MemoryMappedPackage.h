/** \file MemoryMappedPackage.h
* Header file for the MemoryMappedPackage class.
* \author Tiago Gomes
* \date 16.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "GenericPackage.h"

typedef uint32_t PayloadUnit_t;

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class for the Async Interface
*/
class CMemoryMappedPackage : public GenericPackage
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Constructor
	*
	*/
	CMemoryMappedPackage(uint16_t command, uint16_t frameNumber, uint32_t addressResponse, std::vector<PayloadUnit_t> payload);

	CMemoryMappedPackage();

	~CMemoryMappedPackage();

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	uint16_t m_command;
	uint16_t m_frameNumber;
	uint32_t m_addressResponse;
	std::vector<PayloadUnit_t> m_payload;
};
