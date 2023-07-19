/**************************************************************************************************
**  Copyright (c) 2013 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

#ifndef _EnUtil_Conversions_h
#define _EnUtil_Conversions_h

//*****************************************************************************
// Includes
//*****************************************************************************
#include <string>
#include <sstream>
#include "EnTypes.h"
//*****************************************************************************
// Macros
//*****************************************************************************


//*****************************************************************************
// Forward Definitions
//*****************************************************************************
namespace EnUtil {
	namespace Conversions {

		//*****************************************************************************
		// Declarations
		//*****************************************************************************

		/**
		* \brief	Convert integer to string
		*
		* \param number	Integer to convert
		* \return		Resulting string
		*/
		//****************************************************************
		template<typename T>
		std::string ConvertInt(const T number)
			//****************************************************************
		{
			std::stringstream ss;
			ss << number;
			return ss.str();
		}

		/**
		* \brief Convert a number to a byte array
		*
		* \param number		Number to convert
		* \param bytes		Number of bytes to convert (LS-bytes)
		* \param byteArray_p	Array to write the result into
		*/
		//****************************************************************
		template<typename T>
		void NumberToByteArray(T number,
			const en_uint8 bytes,
			en_byte* const byteArray_p)
			//****************************************************************
		{
			for (en_uint8 byteNr = 0; byteNr < bytes; byteNr++)
			{
				byteArray_p[byteNr] = (number >> (8 * byteNr)) & 0xFF;
			}
		}

		/**
		* \brief Convert a byte array to a number
		*
		* \param bytes			Number of bytes to convert to number (starting at byte 0)
		* \param byteArray_p	Byte array to convert to number
		* \return				Number generated
		*/
		//****************************************************************
		template<typename T>
		T NumberFromByteArray(const en_uint8 bytes,
			const en_byte* const byteArray_p)
			//****************************************************************
		{
			T number = 0;
			for (en_uint8 byteNumber = 0; byteNumber < bytes; byteNumber++)
			{
				number += ((en_uint32)byteArray_p[byteNumber]) << (8 * byteNumber);
			}
			return number;
		}

		/**
		* \brief	Bitrevert a number
		*
		* \param input	Number to bitrevert
		* \return		Bitreverse of input
		*/
		//****************************************************************
		template<typename T>
		T BitRevert(T input)
			//****************************************************************
		{

			//Initialize
			T output = 0;

			//Loop over all bits
			for (en_uint8 bit = 0; bit < sizeof(T) * 8; bit++)
			{
				output <<= 1;
				if (input & 0x01)
				{
					output += 0x01;
				}
				input >>= 1;
			}
			return output;
		}
	}
}

#endif
