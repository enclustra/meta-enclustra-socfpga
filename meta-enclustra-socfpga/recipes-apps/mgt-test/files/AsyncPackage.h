/** \file AsyncPackage.h
* Header file for the AsyncPackage class.
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
* \brief C++ class for the AsyncPackage
*/
class CAsyncPackage : public GenericPackage
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Constructor
	*
	*/
	CAsyncPackage(EAsyncTypes_t type, std::vector<PayloadUnit_t> payload);

	CAsyncPackage();

	~CAsyncPackage();

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	EAsyncTypes_t m_type;
	std::vector<PayloadUnit_t> m_payload;
};
