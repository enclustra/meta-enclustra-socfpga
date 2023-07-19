/**************************************************************************************************
**  Copyright (c) 2013 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

//*****************************************************************************
// Includes
//*****************************************************************************
#include "CGeneralException.h"

namespace EnUtil {
	//*****************************************************************************
	// Construct / Destruct
	//*****************************************************************************
	en_uint32 CGeneralException::s_memAllocatedLast = 0;
	en_uint32 CGeneralException::ID = GetNextFreeTypeId();

	//*****************************************************************************
	// Error Codes
	//*****************************************************************************
	CGeneralException::ECode CGeneralException::ECode_Success;
	CGeneralException::ECode CGeneralException::ECode_NotYetImplemented;
	CGeneralException::ECode CGeneralException::ECode_NullPointer;
	CGeneralException::ECode CGeneralException::ECode_IllegalArgumentCombination;
	CGeneralException::ECode CGeneralException::ECode_ArgumentOutOfRange;
	CGeneralException::ECode CGeneralException::ECode_LeadsToIllegalState;
	CGeneralException::ECode CGeneralException::ECode_IndexOutOfRange;
	CGeneralException::ECode CGeneralException::ECode_CouldNotAllocateMemory;
	CGeneralException::ECode CGeneralException::ECode_FileAccessError;
	CGeneralException::ECode CGeneralException::ECode_IllegalEnumValue;
	CGeneralException::ECode CGeneralException::ECode_IllegalErrorCode;
	CGeneralException::ECode CGeneralException::ECode_IllegalUserErrorCode;

	//****************************************************************
	CGeneralException::CGeneralException(const std::string info,
		const ECode error)
		//****************************************************************
		: CException(ID)
	{
		if (GetMemAllocRun() != s_memAllocatedLast)
		{
			SetMessages();
			s_memAllocatedLast = GetMemAllocRun();
		}
		SetCode(error);
		AppendInfo("CGeneralException: " + s_messages[error]);
		AppendInfo(" in " + info);
	}

	//****************************************************************
	CGeneralException::~CGeneralException()
		//****************************************************************
	{
	}

	//*****************************************************************************
	// Public Functions
	//*****************************************************************************

	//****************************************************************
	CGeneralException& CGeneralException::Rethrow(const std::string info)
		//****************************************************************
	{
		return dynamic_cast<CGeneralException&>(CException::Rethrow(info));
	}

	//****************************************************************
	CGeneralException& CGeneralException::Rethrow(const std::string info,
		const en_uint32 newError)
		//****************************************************************
	{
		return dynamic_cast<CGeneralException&>(CException::Rethrow(info, newError));
	}

	//*****************************************************************************
	// Private Functions
	//*****************************************************************************

	//****************************************************************
	void CGeneralException::SetMessages()
		//****************************************************************
	{
		s_messages[ECode_Success] = "No error, operation was successful";
		s_messages[ECode_NotYetImplemented] = "This functionality is not yet implemented";
		s_messages[ECode_NullPointer] = "Unexpected null pointer";
		s_messages[ECode_IllegalArgumentCombination] = "The argument combination passed is not allowed";
		s_messages[ECode_ArgumentOutOfRange] = "An argument passed to a function was out of range";
		s_messages[ECode_LeadsToIllegalState] = "Call leads to illegal internal state";
		s_messages[ECode_IndexOutOfRange] = "Index out of range";
		s_messages[ECode_CouldNotAllocateMemory] = "Memory could not be allocated due to out of memory";
		s_messages[ECode_FileAccessError] = "File could not be accessed";
		s_messages[ECode_IllegalEnumValue] = "Wrong enum value passed";
		s_messages[ECode_IllegalUserErrorCode] = "Illegal user error code was assigned to exception";
	}
}
