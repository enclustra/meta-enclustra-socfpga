/** \file GenericPackage.h
* Header file for the GenericPackage, part of the Production Test Util.
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

#include "ProductionTestUtilTypes.h"

//-------------------------------------------------------------------------------------------------
// Interface definition
//-------------------------------------------------------------------------------------------------

class GenericPackage
{
	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	EProductionTestUtilPackages_t m_identifier;
	uint32_t m_size;
};
