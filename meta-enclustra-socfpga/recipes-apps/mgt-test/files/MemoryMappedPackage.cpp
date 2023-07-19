/** \file MemoryMappedPackage.cpp
* Implementation file for the MemoryMappedPackage class
* \author Tiago Gomes
* \date 16.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "MemoryMappedPackage.h"

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

using namespace std;

//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------

CMemoryMappedPackage::CMemoryMappedPackage(uint16_t command, uint16_t frameNumber, uint32_t addressResponse, vector<PayloadUnit_t> payload) :
	m_command(command),
	m_frameNumber(frameNumber),
	m_addressResponse(addressResponse),
	m_payload(payload)
{
	m_identifier = EProductionTestUtilPackages_t::MemoryMapped;
	m_size = sizeof(m_command) + sizeof(m_frameNumber) + sizeof(m_addressResponse) + m_payload.size() * sizeof(PayloadUnit_t);
}

CMemoryMappedPackage::CMemoryMappedPackage() :
	m_command(0),
	m_frameNumber(0),
	m_addressResponse(0)
{
	m_identifier = EProductionTestUtilPackages_t::MemoryMapped;
	m_size = 0;
	m_payload.clear();
}

CMemoryMappedPackage::~CMemoryMappedPackage()
{

}

