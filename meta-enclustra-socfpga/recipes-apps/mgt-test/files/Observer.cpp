/** \file Observer.c
* Implementation file for the Observer class, part of the Production Test Util.
* \author Tiago Gomes
* \date 25.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "Observer.h"
//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------
using namespace std;

//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------
CObserver::CObserver()
{

}

CObserver::~CObserver()
{

}

//-------------------------------------------------------------------------------------------------
// Method definitions
//-------------------------------------------------------------------------------------------------
void CObserver::Add(IObserver * observer)
{
	m_ObserverList.push_back(observer);
}

void CObserver::Remove(IObserver * observer)
{
	m_ObserverList.erase(std::remove(m_ObserverList.begin(), m_ObserverList.end(), observer), m_ObserverList.end());
}


#ifndef _WIN32
#define time // we need to find a way to get the time in MB without OS...
#endif

void CObserver::Update(const string & sourceClassName, EObserverLevel_t level, const string & message)
{
	time_t timeStamp;
	time(&timeStamp); // get time

	for (uint32_t observerIndex = 0; observerIndex < m_ObserverList.size(); observerIndex++)
	{
		IObserver * CurrentObserver = m_ObserverList.at(observerIndex);
		CurrentObserver->Update(timeStamp, sourceClassName, level, message);
	}
}


void CObserver::Update(const std::string & sourceClassName, EProductionTestUtilTests_t source, std::vector<float> & values)
{
	time_t timeStamp;
	time(&timeStamp); // get time

	for (uint32_t observerIndex = 0; observerIndex < m_ObserverList.size(); observerIndex++)
	{
		IObserver * CurrentObserver = m_ObserverList.at(observerIndex);
		CurrentObserver->Update(timeStamp, sourceClassName, source, values);
	}
}

void CObserver::Update(const std::string & sourceClassName, bool passed, boost::property_tree::ptree resultCases) {

	time_t timeStamp;
	time(&timeStamp); // get time

	for (uint32_t observerIndex = 0; observerIndex < m_ObserverList.size(); observerIndex++)
	{
		IObserver * CurrentObserver = m_ObserverList.at(observerIndex);

		CurrentObserver->Update(timeStamp, sourceClassName, passed, resultCases);
	}
}

void CObserver::FinishFile(bool passed)
{
	for (uint32_t observerIndex = 0; observerIndex < m_ObserverList.size(); observerIndex++)
	{
		IObserver * CurrentObserver = m_ObserverList.at(observerIndex);

		CurrentObserver->FinishFile(passed);
	}

}



