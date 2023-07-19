/** \file RegisterInterface.h
* Header file for the RegisterInterface class.
* \author Tiago Gomes
* \date 12.07.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "IRegisterInterface.h"

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class for the Register Interface
*/
class CLinuxRegisterInterface : public IRegisterInterface
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	CLinuxRegisterInterface(off_t offset, size_t length);

	virtual ~CLinuxRegisterInterface();

	//-------------------------------------------------------------------------------------------------
	// Method declarations
	//-------------------------------------------------------------------------------------------------
public:

	/**
	* \brief Get the name of the object for logging purposes
	*
	* \returns						Name of the class instance
	*/
	std::string GetName();

	/**
	* \brief Read from the module tester.
	*
	* \param address				Read address
	* \returns						Read data
	*/
	std::uint32_t Read(std::uint32_t address);

	/**
	* \brief Read a block of data from the module tester.
	*
	* \param address				Initial address
	* \param size					Number of bytes to read
	* \param data					Vector containing read data only
	* \returns						Read data
	*/
	void ReadBlock(std::uint32_t address, std::uint32_t size, std::vector<uint32_t>& data);

	/**
	* \brief Write to the module tester.
	*
	* \param address				Write address
	* \param data					Write data
	*/
	void Write(std::uint32_t address, std::uint32_t data);

	/**
	* \brief Write a block of data to the module tester.
	*
	* \param address				Initial address where data will be written to
	* \param data					Vector containing the data
	*/
	void WriteBlock(std::uint32_t address, const std::vector<uint32_t>& data);

	/**
	* \brief Set bits of a word at specific address in memory
	*
	* \param address				Write address
	* \param data					Write data ('1' will set the corresponding bit)
	*/
	void SetBits(std::uint32_t address, std::uint32_t data);

	/**
	* \brief Clear bits of a word at specific address in memory
	*
	* \param address				Write address
	* \param data					Write data ('1' will clear the corresponding bit)
	*/
	void ClearBits(std::uint32_t address, std::uint32_t data);

private:
	std::string m_name = "LinuxRegisterInterface";
	volatile uint32_t *m_mem;
	int m_fd;
	off_t m_page_base;
};
