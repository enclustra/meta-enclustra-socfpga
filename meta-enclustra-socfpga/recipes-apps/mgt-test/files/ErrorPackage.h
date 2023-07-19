/** \file ErrorPackage.h
* Header file for the ErrorPackage class.
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

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class for the ErrorPackage
*/
class CErrorPackage : public GenericPackage
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Constructor
	*
	*/
	CErrorPackage(uint32_t code, std::string payload);

	CErrorPackage();

	~CErrorPackage();

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
	void SetError(uint32_t code, std::string payload);

public:
	uint32_t m_code;
	std::string m_payload;
};
