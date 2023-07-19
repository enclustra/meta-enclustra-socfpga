/** \file IObserver.h
* Header file for the IObserver interface, part of the Production Test Util.
* \author Tiago Gomes
* \date 25.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "ProductionTestUtilTypes.h"
#if defined(__linux__)
namespace boost{
	namespace property_tree{
		typedef int ptree;
}
}
#else
#if defined(__microblaze__)
namespace boost{
	namespace property_tree{
		typedef int ptree;
}
}
#else
#include <boost/property_tree/ptree.hpp>
#include <JsonParser/json_parser.hpp>
#endif
#endif
//#include <boost/property_tree/json_parser.hpp>

//-------------------------------------------------------------------------------------------------
// Interface definition
//-------------------------------------------------------------------------------------------------

class IObserver
{
	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:


	/**
	* \brief	Notify observer about a new event: Textmessage
	*
	* \param	timeStamp						time stamp of the event
	* \param	source							Class which generated the event
	* \param	level							Severity of the event
	* \param	message							Event description
	*
	*/
	virtual void Update(time_t timeStamp, const std::string & sourceClassName, EObserverLevel_t level, const std::string & message) = 0;

	/**
	* \brief	Notify observer about a new event: Datavalues
	*
	* \param	timeStamp						time stamp of the event
	* \param	source							Class which generated the event
	* \param	messageSender					Type of test who created the message
	* \param	values							array of values
	*
	*/
	virtual void Update(time_t timeStamp, const std::string & sourceClassName, EProductionTestUtilTests_t messageSender, std::vector<float> & values) = 0;
	virtual void Update(time_t timeStamp, const std::string & sourceClassName, bool passed, boost::property_tree::ptree resultCases) = 0;
	virtual void FinishFile(bool passed) = 0;

};
