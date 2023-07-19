/** \file IRegisterInterface.h
* Header file for the IRegisterInterface interface, part of the Production Test Util.
* \author Tiago Gomes
* \date 11.07.2016
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

class IRegisterInterface
{
	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:

	/**
	* \brief Get the name of the object for logging purposes
	*
	* \returns								Name of the class instance
	*/
	virtual std::string GetName() = 0;

	/**
	* \brief Read from the module tester.
	*
	* \param address				Read address
	* \returns						Read data
	*/
	virtual std::uint32_t Read(std::uint32_t address) = 0;

	/**
	* \brief Read a block of data from the module tester.
	*
	* \param address				Initial address
	* \param size					Number of bytes to read
	* \param data					Vector containing read data only
	* \returns						Read data
	*/
	virtual void ReadBlock(std::uint32_t address, std::uint32_t size, std::vector<uint32_t>& data) = 0;

	/**
	* \brief Write to the module tester.
	*
	* \param address				Write address
	* \param data					Write data
	*/
	virtual void Write(std::uint32_t address, std::uint32_t data) = 0;

	/**
	* \brief Write a block of data to the module tester.
	*
	* \param address				Initial address where data will be written to
	* \param data					Vector containing the data
	*/
	virtual void WriteBlock(std::uint32_t address, const std::vector<uint32_t>& data) = 0;

	/**
	* \brief Set bits of a word at specific address in memory
	*
	* \param address				Write address
	* \param data					Write data ('1' will set the corresponding bit)
	*/
	virtual void SetBits(std::uint32_t address, std::uint32_t data) = 0;

	/**
	* \brief Clear bits of a word at specific address in memory
	*
	* \param address				Write address
	* \param data					Write data ('1' will clear the corresponding bit)
	*/
	virtual void ClearBits(std::uint32_t address, std::uint32_t data) = 0;
};
