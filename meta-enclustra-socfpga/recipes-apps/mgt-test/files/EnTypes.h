/**************************************************************************************************
**  Copyright (c) 2013 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

#ifndef _EnUtil_Types_h
#define _EnUtil_Types_h

#include <stdint.h>

namespace EnUtil {

	/**
	* \brief Dummy function to suppress compiler warnings
	*
	* \param var	Variable to remove warnings for
	*/
	template<typename T>
	void unreferenced_variable(T var) {}

	/** Unsigned Integer 64 bits */
	typedef uint64_t en_uint64;
	/** Unsigned Interger 32 bits */
	typedef uint32_t en_uint32;
	/** Unisgned Interger 16 bits */
	typedef uint16_t en_uint16;
	/** Unsigned Integer 8 bits */
	typedef uint8_t en_uint8;
	/** Byte */
	typedef unsigned char en_byte;
	/** Signed Integer 64 bits */
	typedef int64_t en_int64;
	/** Signed Integer 32 bits */
	typedef int32_t en_int32;
	/** Signed Integer 16 bits */
	typedef int16_t en_int16;
	/** Signed Integer 8 bits */
	typedef int8_t en_int8;

}


#endif
