/**************************************************************************************************
**  Copyright (c) 2016 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

#pragma once

//*****************************************************************************
// Includes
//*****************************************************************************
#include "CException.h"

//*****************************************************************************
// Macros
//*****************************************************************************
#define EN_EXPT_THROW_NOT_YET_IMPLEMENTED {throw CGeneralException(EN_EXPT_INFO, CGeneralException::ECode_NotYetImplemented);}
#define EN_EXPT_FUNCTION_NOT_YET_IMPLEMENTED {try{EN_EXPT_THROW_NOT_YET_IMPLEMENTED}catch(CException& ex){EN_EXPT_RETHROW(ex);}}
#define EN_EXPT_THROW_ARGUMENT_OUT_OF_RANGE {throw CGeneralException(EN_EXPT_INFO, CGeneralException::ECode_ArgumentOutOfRange);}
#define EN_EXPT_THROW_NULL_POINTER {throw CGeneralException(EN_EXPT_INFO, CGeneralException::ECode_NullPointer);}

//*****************************************************************************
// Forward Definitions
//*****************************************************************************
namespace EnUtil {


	//*****************************************************************************
	// Declarations
	//*****************************************************************************
	/**
	* \brief	General Exceptions
	*
	* \author Oliver Bruendler
	*/
	class CProductionTestException : public CException
	{
	public:
		//*************************************************************************
		// Exception Type ID
		//*************************************************************************
		/** ID of this exception class*/
		static en_uint32 ID;

		//*************************************************************************
		// Error Codes
		//*************************************************************************
		/**
		* Typedef to prevent exception codes from other exceptions to be passed to the
		* constructor of this exception.
		*/
		typedef CExptCode<CProductionTestException> ECode;

		/** No error, operation was successful */
		static ECode ECode_Success;
		/** XML file can not be found */
		static ECode ECode_CanNotFoundXmlFile;
		/** XSD file can not be found */
		static ECode ECode_CanNotFoundXsdFile;
		/** XML file has wrong format */
		static ECode ECode_XmlFileHasWrongExtension;
		/** XSD file has wrong format */
		static ECode ECode_XsdFileHasWrongExtension;
		/** Error Parsing XML file, either the file is corrupted, or contains syntax errors */
		static ECode ECode_ErrorParsingXmlFile;
		/** Error XML value out of range,  or some value does not comply with xsd rules */
		static ECode ECode_XmlValueOutofRange;
		/** The data vector is greater than the RAM size */
		static ECode ECode_RamVectorOutofRange;
		/** COM Port timeout */
		static ECode ECode_ComPortTimeout;
		/** COM Port error */
		static ECode ECode_ComPortError;
		/** Package command error */
		static ECode ECode_PackageCommandError;
		/** Package frame number error */
		static ECode ECode_PackageFrameNumberError;
		/** Package response CRC error */
		static ECode ECode_PackageResponseCrcErrorDetected;
		/** Package received has CRC error  */
		static ECode ECode_PackageReceivedCrcErrorDetected;
		/** Invalid package received */
		static ECode ECode_InvalidPackageReceived;
		/** Boost exception triggered */
		static ECode ECode_BoostException;
		/** Std exception triggered */
		static ECode ECode_StdException;
		/** Unknown exception triggered */
		static ECode ECode_UnknownException;
		/** Target XML contains errors */
		static ECode ECode_TargetXmlSettingsIsNotValid;
		/** Requested Test Group does not exist */
		static ECode ECode_TestGroupNotFound;
		/** MMap failed */
		static ECode ECode_MmapFailed;
		/** MCT Error */
		static ECode ECode_McTError;
		/** MCT Error */
		static ECode ECode_FtdiError;
		/** FX3 Error */
		static ECode ECode_Fx3LibError;
		/** PowerGood error */
		static ECode ECode_PowerIssue;
		/** System monitor error */
		static ECode ECode_SysMonError;
		/** Module Detection error */
		static ECode ECode_ModuleDetectionError;
		/** Module Detection error */
		static ECode ECode_JtagCodeError;
		/** Error with other devices e.g. powersupply */
		static ECode ECode_FailedToSetupDevice;
		/** Programming the module is not allowed */
		static ECode ECode_NotAllowedToProgram;
		/** Module Detection error */
		static ECode ECode_NoFx3FoundError;

		static ECode ECode_FailedToAccessClimateChamber;

		static ECode ECode_TargetSetupFailed;

		static ECode ECode_NoModulesInBurnIn;

		//*************************************************************************
		// Construct / Destruct
		//*************************************************************************		
		/**
		* \brief Constructor
		*
		* \param info	Exception information to add to trace
		* \param error	Error number to be stored within the exception
		*/
		CProductionTestException(const std::string info,
			const ECode error);

		CProductionTestException(const std::string info,
			const ECode error,
			const int MctLibCode);

		/**
		* \brief Destructor
		*/
		virtual ~CProductionTestException();


		//*************************************************************************
		// Public Functions
		//*************************************************************************

		/**
		* \brief Rethrow exception
		*
		* If this function is used in a catch statement to rethrow the exception, the trace
		* is extended with file/function/line information and the passed exception information.
		*
		* \param info	Exception information to add to trace
		* \return		Updated exception
		*/
		CProductionTestException& Rethrow(const std::string info);

		/**
		* \brief Rethrow exception and change the error number containted
		*
		* If this function is used in a catch statement to rethrow the exception, the trace
		* is extended with file/function/line information and the passed exception information.\n
		* The function also allows it to change the error number for the case that it has to be
		* reinterpreted.
		*
		* \param info	Exception information to add to trace
		* \param newError	New error number to use
		* \return			Updated exception
		*/
		CProductionTestException& Rethrow(const std::string info,
			const en_uint32 newError);



	private:
		//*************************************************************************
		// Disable Standard Constructor
		//*************************************************************************
		/** Default Constructor (prohibited) */
		CProductionTestException();

		//*************************************************************************
		// Signleton Variables
		//*************************************************************************
		/** Number of the last memory allocation run executed for this class */
		static en_uint32 s_memAllocatedLast;

		//*************************************************************************
		// Private Functions
		//*************************************************************************
		virtual void SetMessages();
	};
}

