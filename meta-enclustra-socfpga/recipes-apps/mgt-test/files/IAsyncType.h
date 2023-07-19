/** \file IAsyncType.h
* Header file for the IAsyncType interface, part of the Production Test Util.
* \author Tiago Gomes
* \date 15.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "ProductionTestUtilTypes.h"
#include "GenericPackage.h"
#include "Observer.h"

//-------------------------------------------------------------------------------------------------
// Interface definition
//-------------------------------------------------------------------------------------------------

class IAsyncType
{
	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	virtual	void ReceivedData(std::vector <uint8_t> & data) = 0;

	virtual void AttachObserver(CObserver * observer) = 0;

};
