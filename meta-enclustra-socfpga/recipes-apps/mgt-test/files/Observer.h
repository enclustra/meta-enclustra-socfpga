/** \file Observer.h
* Header file for the Observer class, part of the Production Test Util.
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
#include "IObserver.h"

//-------------------------------------------------------------------------------------------------
// Interface definition

//-------------------------------------------------------------------------------------------------
/**
* \brief C++ class for the Observer
*/
class CObserver
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	CObserver();

	virtual ~CObserver();

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:

	/**
	* \brief	Add new Observer to the list
	*
	* \param	observer			Pointer to Observer
	*
	*/
	void Add(IObserver * observer);

	/**
	* \brief	Remove existing Observer from the list
	*
	* \param	observer			Pointer to Observer
	*
	*/
	void Remove(IObserver * observer);

	/**
	* \brief	Creates a timestamp and notifies all observers about a new event
	*
	* \param	sourceClassName					Class which generated the event
	* \param	level							Severity of the event
	* \param	message							Event description
	*
	*/
	void Update(const std::string & sourceClassName, EObserverLevel_t level, const std::string & message);

	/**
	* \brief	Creates a timestamp and notifies all observers about the new measurement values
	*
	* \param	sourceClassName					Class which generated the event
	* \param	source							Type of test who created this message
	* \param	message							values to be written
	*
	*/
	void Update(const std::string & sourceClassName, EProductionTestUtilTests_t source, std::vector<float> & values);

	void Update(const std::string & sourceClassName, bool passed, boost::property_tree::ptree resultCases);
	void FinishFile(bool passed);

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	std::vector <IObserver *> m_ObserverList;

};
