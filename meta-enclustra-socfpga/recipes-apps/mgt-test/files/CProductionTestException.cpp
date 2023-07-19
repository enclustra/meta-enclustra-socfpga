/**************************************************************************************************
**  Copyright (c) 2013 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

//*****************************************************************************
// Includes
//*****************************************************************************
#include "CProductionTestException.h"
#ifdef _WIN32
#include <MctLibApi.h>
#include <FtdiLibApi.h>
#endif
namespace EnUtil {
	//*****************************************************************************
	// Construct / Destruct
	//*****************************************************************************
	en_uint32 CProductionTestException::s_memAllocatedLast = 0;
	en_uint32 CProductionTestException::ID = GetNextFreeTypeId();

	//*****************************************************************************
	// Error Codes
	//*****************************************************************************
	CProductionTestException::ECode CProductionTestException::ECode_Success;
	CProductionTestException::ECode CProductionTestException::ECode_CanNotFoundXmlFile;
	CProductionTestException::ECode CProductionTestException::ECode_CanNotFoundXsdFile;
	CProductionTestException::ECode CProductionTestException::ECode_XmlFileHasWrongExtension;
	CProductionTestException::ECode CProductionTestException::ECode_XsdFileHasWrongExtension;
	CProductionTestException::ECode CProductionTestException::ECode_ErrorParsingXmlFile;
	CProductionTestException::ECode CProductionTestException::ECode_XmlValueOutofRange;
	CProductionTestException::ECode CProductionTestException::ECode_RamVectorOutofRange;
	CProductionTestException::ECode CProductionTestException::ECode_ComPortTimeout;
	CProductionTestException::ECode CProductionTestException::ECode_ComPortError;
	CProductionTestException::ECode CProductionTestException::ECode_PackageCommandError;
	CProductionTestException::ECode CProductionTestException::ECode_PackageFrameNumberError;
	CProductionTestException::ECode CProductionTestException::ECode_PackageResponseCrcErrorDetected;
	CProductionTestException::ECode CProductionTestException::ECode_PackageReceivedCrcErrorDetected;
	CProductionTestException::ECode CProductionTestException::ECode_InvalidPackageReceived;
	CProductionTestException::ECode CProductionTestException::ECode_BoostException;
	CProductionTestException::ECode CProductionTestException::ECode_StdException;
	CProductionTestException::ECode CProductionTestException::ECode_UnknownException;
	CProductionTestException::ECode CProductionTestException::ECode_TargetXmlSettingsIsNotValid;
	CProductionTestException::ECode CProductionTestException::ECode_TestGroupNotFound;
	CProductionTestException::ECode CProductionTestException::ECode_MmapFailed;
	CProductionTestException::ECode CProductionTestException::ECode_McTError;
	CProductionTestException::ECode CProductionTestException::ECode_FtdiError;
	CProductionTestException::ECode CProductionTestException::ECode_Fx3LibError;
	CProductionTestException::ECode CProductionTestException::ECode_PowerIssue;
	CProductionTestException::ECode CProductionTestException::ECode_SysMonError;
	CProductionTestException::ECode CProductionTestException::ECode_ModuleDetectionError;
	CProductionTestException::ECode CProductionTestException::ECode_NotAllowedToProgram;
	CProductionTestException::ECode CProductionTestException::ECode_JtagCodeError;
	CProductionTestException::ECode CProductionTestException::ECode_NoFx3FoundError;
	CProductionTestException::ECode CProductionTestException::ECode_FailedToAccessClimateChamber;
	CProductionTestException::ECode CProductionTestException::ECode_FailedToSetupDevice;
	CProductionTestException::ECode CProductionTestException::ECode_TargetSetupFailed;
	CProductionTestException::ECode CProductionTestException::ECode_NoModulesInBurnIn;

	//****************************************************************
	CProductionTestException::CProductionTestException(const std::string info,
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
	CProductionTestException::CProductionTestException(const std::string info,
		const ECode error,
		const int MctLibCode)
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
		std::stringstream ss;
#ifdef _WIN32
		if (error == CProductionTestException::ECode_Fx3LibError) {
			ss << std::hex << MctLibCode;
			AppendInfo(" Fx3LibCode 0x" + ss.str());
		}
		else if (error == CProductionTestException::ECode_FtdiError) {
			ss << FtdiLib_GetErrorString((FTDILIB_RESULT)MctLibCode);
			AppendInfo(" FtdiLib error " + ss.str());
		}
		else {
			ss << MctLib_GetErrorString((MCTLIB_RESULT)MctLibCode);
			AppendInfo(" MctLib error " + ss.str());
		}
#endif

	}


	//****************************************************************
	CProductionTestException::~CProductionTestException()
		//****************************************************************
	{
	}

	//*****************************************************************************
	// Public Functions
	//*****************************************************************************

	//****************************************************************
	CProductionTestException& CProductionTestException::Rethrow(const std::string info)
		//****************************************************************
	{
		return dynamic_cast<CProductionTestException&>(CException::Rethrow(info));
	}

	//****************************************************************
	CProductionTestException& CProductionTestException::Rethrow(const std::string info,
		const en_uint32 newError)
		//****************************************************************
	{
		return dynamic_cast<CProductionTestException&>(CException::Rethrow(info, newError));
	}

	//*****************************************************************************
	// Private Functions
	//*****************************************************************************

	//****************************************************************
	void CProductionTestException::SetMessages()
		//****************************************************************
	{
		s_messages[ECode_Success] = "No error, operation was successful";
		s_messages[ECode_CanNotFoundXmlFile] = "XML File could not be found";
		s_messages[ECode_CanNotFoundXsdFile] = "XSD File could not be found";
		s_messages[ECode_XmlFileHasWrongExtension] = "File is not an .xml file";
		s_messages[ECode_XsdFileHasWrongExtension] = "File is not an .xsd file";
		s_messages[ECode_ErrorParsingXmlFile] = "Error parsing XML file";
		s_messages[ECode_XmlValueOutofRange] = "Error in xml File, value out of range or min>max";
		s_messages[ECode_RamVectorOutofRange] = "RAM vector is out of range";
		s_messages[ECode_ComPortTimeout] = "COM port timeout, check if the other end is working or try to increase the timeout timer so the other end has time to process and return data in time";
		s_messages[ECode_ComPortError] = "COM port error (e.g., cable disconnected, board not programmed)";
		s_messages[ECode_PackageCommandError] = "Package with wrong command or command not expected";
		s_messages[ECode_PackageFrameNumberError] = "Package frame number does not match the expected one";
		s_messages[ECode_PackageResponseCrcErrorDetected] = "Package response indicates board has detected a CRC error on the message previous sent";
		s_messages[ECode_PackageReceivedCrcErrorDetected] = "A CRC error was detected in the received package";
		s_messages[ECode_InvalidPackageReceived] = "A invalid package was received, package identifier is unknown";
		s_messages[ECode_BoostException] = "A boost exception was trigger";
		s_messages[ECode_StdException] = "A Std exception was trigger";
		s_messages[ECode_UnknownException] = "An unknown exception was trigger";
		s_messages[ECode_TargetXmlSettingsIsNotValid] = "The Target XML file contain errors";
		s_messages[ECode_TestGroupNotFound] = "The requested TestGroup was not found";
		s_messages[ECode_MmapFailed] = "Failed to Map /dev/mem";
		s_messages[ECode_McTError] = "An MCT function returned an error:";
		s_messages[ECode_FtdiError] = "An Ftdi Lib function returned an error:";
		s_messages[ECode_Fx3LibError] = "An FX3 Lib function returned an error:";
		s_messages[ECode_PowerIssue] = "PowerIssue, Check Module Power";
		s_messages[ECode_SysMonError] = "System Monitor error, Value not in expected range";
		s_messages[ECode_ModuleDetectionError] = "Ftdi access error, possible problems: none or multiple modules, names of Ftdi wrong";
		s_messages[ECode_NotAllowedToProgram] = "Programming of Modules is not allowed during e.g. Burn-in test";
		s_messages[ECode_JtagCodeError] = "The device Jtag code does not match expected code";
		s_messages[ECode_NoFx3FoundError] = "No FX3 device found";
		s_messages[ECode_FailedToAccessClimateChamber] = "Error of Climate Chamber";
		s_messages[ECode_FailedToSetupDevice] = "Error Remote device not found";
		s_messages[ECode_TargetSetupFailed] = "Setup function failed, check log";
		s_messages[ECode_NoModulesInBurnIn] = "There are no modules left to be tested";
	}
}

