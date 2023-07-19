/** \file AsyncPackage.cpp
* Implementation file for the AsyncPackage class
* \author Tiago Gomes
* \date 16.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "AsyncPackage.h"

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

using namespace std;

//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------

CAsyncPackage::CAsyncPackage(EAsyncTypes_t type, vector<PayloadUnit_t> payload) :
	m_type(type),
	m_payload(payload)
{
	m_identifier = EProductionTestUtilPackages_t::Async;
	m_size = sizeof(m_type) + m_payload.size() * sizeof(PayloadUnit_t);
}

CAsyncPackage::CAsyncPackage()
{

}

CAsyncPackage::~CAsyncPackage()
{

}

