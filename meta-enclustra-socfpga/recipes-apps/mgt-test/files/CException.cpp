/**************************************************************************************************
**  Copyright (c) 2013 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

//*****************************************************************************
// Includes
//*****************************************************************************
#include "CException.h"
#include "CGeneralException.h"
#include <string>

namespace EnUtil {
	//*****************************************************************************
	// Construct / Destruct
	//*****************************************************************************
	std::map<en_uint32, std::string> CException::s_messages;
	en_uint32 CException::s_memAllocRun = 1;
	en_uint32 CException::s_memAllocatedLast = 0;
	en_uint32 CException::s_nextErrorNumber = 0;
	en_uint32 CException::s_nextTypeNumber = 0;
	en_uint32 CException::ID = GetNextFreeTypeId();

	//****************************************************************
	CException::CException(const en_uint32 id)
		//****************************************************************
		: m_trace(""),
		m_userCode(USER_ERROR_INTERNAL_ERROR),
		m_id(id)
	{
		if (s_memAllocatedLast != GetMemAllocRun())
		{
			SetMessages();
			s_memAllocatedLast = GetMemAllocRun();
		}
	}

	//****************************************************************
	CException::CException(const std::string info,
		const en_uint32 error)
		//****************************************************************
		: m_trace(""),
		m_code(error),
		m_userCode(USER_ERROR_INTERNAL_ERROR),
		m_id(ID)
	{

		if (s_memAllocatedLast != GetMemAllocRun())
		{
			SetMessages();
			s_memAllocatedLast = GetMemAllocRun();
		}
		AppendInfo("CException: " + s_messages[error]);
		AppendInfo(" in " + info);
	}

	//****************************************************************
	CException::~CException()
		//****************************************************************
	{
	}

	//*****************************************************************************
	// Public Member Functions
	//*****************************************************************************

	//****************************************************************
	void CException::AssignUserCode(const en_uint32 code)
		//****************************************************************
	{
		if ((code == USER_ERROR_NO_ERROR) || (code == USER_ERROR_INTERNAL_ERROR))
		{
			throw CException(EN_EXPT_INFO, CGeneralException::ECode_IllegalUserErrorCode);
		}
		m_userCode = code;
	}

	//****************************************************************
	const en_uint32 CException::GetUserCode()
		//****************************************************************
	{
		return m_userCode;
	}

	//****************************************************************
	const en_uint32 CException::GetTypeId()
		//****************************************************************
	{
		return m_id;
	}

	//****************************************************************
	const en_uint32 CException::GetCode() const
		//****************************************************************
	{
		return m_code;
	}

	//****************************************************************
	void CException::AppendInfo(std::string info)
		//****************************************************************
	{
		if (EN_EXPT_ENABLE_TRACE)
		{
			m_trace += info;
		}
	}

	//****************************************************************
	const std::string CException::GetTrace() const
		//****************************************************************
	{
		return m_trace;
	}

	//****************************************************************
	std::string CException::GetMessage_() const
		//****************************************************************
	{
		//unknown code
		if (s_messages.count(m_code) == 0)
		{
			return "Unknown Error Code";
		}
		return s_messages[m_code];
	}


	//****************************************************************
	CException& CException::Rethrow(const std::string info)
		//****************************************************************
	{
		AppendInfo("");
		AppendInfo(GetMessage_() + " in");
		AppendInfo(info);
		return *this;
	}

	//****************************************************************
	CException& CException::Rethrow(const std::string info,
		const en_uint32 newError)
		//****************************************************************
	{
		m_code = newError;
		return Rethrow(info);
	}

	//****************************************************************
	void CException::FreeMemory()
		//****************************************************************
	{
		s_memAllocRun++;
		s_messages.clear();
	}

	//*****************************************************************************
	// Protected Member Functions
	//*****************************************************************************

	//****************************************************************
	en_uint32 CException::GetNextFreeCode()
		//****************************************************************
	{
		en_uint32 nextCode = s_nextErrorNumber;
		s_nextErrorNumber++;
		return nextCode;
	}

	//****************************************************************
	en_uint32 CException::GetNextFreeTypeId()
		//****************************************************************
	{
		en_uint32 nextId = s_nextTypeNumber;
		s_nextTypeNumber++;
		return nextId;
		return 0;
	}

	//****************************************************************
	en_uint32 CException::GetMemAllocRun()
		//****************************************************************
	{
		return s_memAllocRun;
	}

	//****************************************************************
	void CException::SetCode(const en_uint32 error)
		//****************************************************************
	{
		if (s_messages.count(error) == 0)
		{
			throw CException(EN_EXPT_INFO, CGeneralException::ECode_IllegalErrorCode);
		}
		m_code = error;

	}

}
