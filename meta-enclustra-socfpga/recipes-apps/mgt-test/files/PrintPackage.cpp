/** \file PrintPackage.cpp
* Implementation file for the PrintPackage class
* \author Tiago Gomes
* \date 16.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "PrintPackage.h"

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

using namespace std;

//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------

CPrintPackage::CPrintPackage(string payload) :
	m_payload(payload)
{
	m_identifier = EProductionTestUtilPackages_t::Print;

	uint32_t originalSize = payload.size();
	uint32_t paddedSize = (originalSize + 3) & ~0x03; // multiple of 4 bytes

	m_size = paddedSize;
	m_payload.resize(paddedSize); //add extra bytes so the size is multiple of 4 bytes
}

CPrintPackage::CPrintPackage()
{
	m_identifier = EProductionTestUtilPackages_t::Print;
	m_size = 0;
	m_payload.clear();
}

CPrintPackage::~CPrintPackage()
{

}

void CPrintPackage::SetPayload(string payload)
{
	uint32_t originalSize = payload.size();
	uint32_t paddedSize = (originalSize + 3) & ~0x03; // multiple of 4 bytes

	m_size = paddedSize;
	m_payload = payload;
	m_payload.resize(paddedSize); //add extra bytes so the size is multiple of 4 bytes
}
