/** \file PrintPackage.h
* Header file for the PrintPackage class.
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
* \brief C++ class for the PrintPackage
*/
class CPrintPackage : public GenericPackage
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	/**
	* \brief Constructor
	*
	*/
	CPrintPackage(std::string payload);

	CPrintPackage();

	~CPrintPackage();

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
	void SetPayload(std::string payload);

public:
	std::string m_payload;
};
