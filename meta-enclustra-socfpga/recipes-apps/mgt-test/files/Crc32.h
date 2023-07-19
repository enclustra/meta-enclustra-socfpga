/** \file Crc32.h
* Header file for the Crc32 class
* \author Tiago Gomes
* \date 11.11.2016
*
* This is a helper class to compute CRC32
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "ProductionTestUtilTypes.h"
using namespace std;

//-------------------------------------------------------------------------------------------------
// Class definition
//-------------------------------------------------------------------------------------------------

/**
* \brief C++ class for the Crc32
*/
class Crc32
{
	//-------------------------------------------------------------------------------------------------
	// Construction/destruction
	//-------------------------------------------------------------------------------------------------
public:
	Crc32(const uint32_t polynomial, const uint32_t initial_remainder, const uint32_t final_xor_value, const bool reflect_data, const bool reflect_remainder);

	~Crc32();

	//-------------------------------------------------------------------------------------------------
	// Public Method declarations
	//-------------------------------------------------------------------------------------------------
public:
	uint32_t Compute(const void* data, const uint32_t size);

	//-------------------------------------------------------------------------------------------------
	// Private Method declarations
	//-------------------------------------------------------------------------------------------------
private:
	/**
	* \brief Build CRC look-up table for CRC calculation
	*
	*/
	void BuildTable();

	/**
	* \brief Reflects a word of 32-bits (i.e., LSB bit becomes MSB bit and so on...)
	*
	* \param[in]	word					Word to reflect
	*
	* \returns								Reflected word
	*/
	uint32_t Reflect32(uint32_t word);

	/**
	* \brief Reflects a word of 8-bits (i.e., LSB bit becomes MSB bit and so on...)
	*
	* \param[in]	word					Word to reflect
	*
	* \returns								Reflected word
	*/
	uint8_t	Reflect8(uint8_t word);

	//-------------------------------------------------------------------------------------------------
	// Private Members declarations
	//-------------------------------------------------------------------------------------------------
private:
	// crc calculation parameters
	uint32_t m_polynomial;
	uint32_t m_initial_remainder;
	uint32_t m_final_xor_value;
	bool m_reflect_data;
	bool m_reflect_remainder;

	// crc look-up table
	vector <uint32_t> m_crcTable;
};