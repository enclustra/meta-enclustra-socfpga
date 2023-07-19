/** \file ErrorPackage.cpp
* Implementation file for the ErrorPackage class
* \author Tiago Gomes
* \date 16.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "ErrorPackage.h"

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

using namespace std;

//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------

CErrorPackage::CErrorPackage(uint32_t code, string payload) :
	m_code(code),
	m_payload(payload)
{
	m_identifier = EProductionTestUtilPackages_t::Error;

	uint32_t originalSize = payload.size();
	uint32_t paddedSize = (originalSize + 3) & ~0x03; // multiple of 4 bytes

	m_size = sizeof(code) + paddedSize;
	m_payload.resize(paddedSize); //add extra bytes so the size is multiple of 4 bytes
}

CErrorPackage::CErrorPackage() :
	m_code(0)
{
	m_identifier = EProductionTestUtilPackages_t::Error;
	m_size = 0;
	m_payload.clear();
}

CErrorPackage::~CErrorPackage()
{

}

void CErrorPackage::SetError(uint32_t code, string payload)
{
	uint32_t originalSize = payload.size();
	uint32_t paddedSize = (originalSize + 3) & ~0x03; // multiple of 4 bytes

	m_size = sizeof(code) + paddedSize;
	m_code = code;
	m_payload = payload;
	m_payload.resize(paddedSize);
}
