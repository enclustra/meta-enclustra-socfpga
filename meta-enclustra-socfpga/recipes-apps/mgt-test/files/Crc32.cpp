/** \file Crc32.c
* Implementation file for the Crc32 class
* \author Tiago Gomes
* \date 11.11.2016
*
* This is a helper class to compute CRC32
*
* NOTE: This code was adapted from code obtained at http://www.sunshine2k.de/articles/coding/crc/understanding_crc.html
* and code obtained from BOOST libraries.
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "Crc32.h"

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------
Crc32::Crc32(const uint32_t polynomial, const uint32_t initial_remainder, const uint32_t final_xor_value, const bool reflect_data, const bool reflect_remainder) :
	m_polynomial(polynomial),
	m_initial_remainder(initial_remainder),
	m_final_xor_value(final_xor_value),
	m_reflect_data(reflect_data),
	m_reflect_remainder(reflect_remainder)
{
	BuildTable();
}

Crc32::~Crc32()
{

}

//-------------------------------------------------------------------------------------------------
// Method definitions
//-------------------------------------------------------------------------------------------------
uint32_t Crc32::Compute(const void* data, const uint32_t size)
{
	uint8_t *p = (uint8_t*)data;

	uint32_t crc = m_initial_remainder; // CRC is set to specified initial value 

	for (uint32_t byte = 0; byte < size; byte++, p++)
	{
		// reflect input byte if specified, otherwise input byte is taken as it is 
		uint8_t curByte = (m_reflect_data ? Reflect8(*p) : *p);

		// XOR-in next input byte into MSB of crc and get this MSB, that's our new intermediate divident 
		uint8_t pos = (uint8_t)((crc ^ (curByte << 24)) >> 24);
		// Shift out the MSB used for division per lookuptable and XOR with the remainder 
		crc = (uint32_t)((crc << 8) ^ (uint32_t)(m_crcTable[pos]));
	}
	// reflect result crc if specified, otherwise calculated crc value is taken as it is
	crc = (m_reflect_remainder ? Reflect32(crc) : crc);
	// Xor the crc value with specified final XOR value before returning 
	return (uint32_t)(crc ^ m_final_xor_value);
}

void Crc32::BuildTable()
{
	const uint32_t polynomial = m_polynomial;
	m_crcTable.resize(256);

	for (int divident = 0; divident < 256; divident++) // iterate over all possible input byte values 0 - 255
	{
		uint32_t curByte = (uint32_t)(divident << 24); // move divident byte into MSB of 32Bit CRC
		for (uint32_t bit = 0; bit < 8; bit++)
		{
			if ((curByte & 0x80000000) != 0)
			{
				curByte <<= 1;
				curByte ^= polynomial;
			}
			else
			{
				curByte <<= 1;
			}
		}
		m_crcTable[divident] = curByte;
	}
}

uint32_t Crc32::Reflect32(uint32_t word)
{
	uint32_t        reflection = 0;
	uint32_t const  one = 1;

	for (std::size_t i = 0; i < 32; ++i, word >>= 1)
	{
		if (word & one)
		{
			reflection |= (one << (32 - 1u - i));
		}
	}
	return reflection;
}

uint8_t Crc32::Reflect8(uint8_t word)
{
	uint8_t        reflection = 0;
	uint8_t const  one = 1;

	for (std::size_t i = 0; i < 8; ++i, word >>= 1)
	{
		if (word & one)
		{
			reflection |= (one << (8 - 1u - i));
		}
	}
	return reflection;
}
