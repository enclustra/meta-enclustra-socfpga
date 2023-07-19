/**************************************************************************************************
**  Copyright (c) 2013 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

#ifndef _EnUtil_CGeneralException_h
#define _EnUtil_CGeneralException_h

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
	class CGeneralException : public CException
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
		typedef CExptCode<CGeneralException> ECode;

		/** No error, operation was successful */
		static ECode ECode_Success;
		/** This functionality is not yet implemented */
		static ECode ECode_NotYetImplemented;
		/** Unexpected null pointer */
		static ECode ECode_NullPointer;
		/** The argument combination passed is not allowed */
		static ECode ECode_IllegalArgumentCombination;
		/** An argument passed to a function was illegal */
		static ECode ECode_ArgumentOutOfRange;
		/** A function call led to an illegal internal state */
		static ECode ECode_LeadsToIllegalState;
		/** Index out of range */
		static ECode ECode_IndexOutOfRange;
		/** Memory could not be allocated due to out of memory */
		static ECode ECode_CouldNotAllocateMemory;
		/** File could not be accessed */
		static ECode ECode_FileAccessError;
		/** Wrong enum value passed */
		static ECode ECode_IllegalEnumValue;
		/** Wrong error code passed */
		static ECode ECode_IllegalErrorCode;
		/** Illegal user code was assigned to exception */
		static ECode ECode_IllegalUserErrorCode;

		//*************************************************************************
		// Construct / Destruct
		//*************************************************************************		
		/**
		* \brief Constructor
		*
		* \param info	Exception information to add to trace
		* \param error	Error number to be stored within the exception
		*/
		CGeneralException(const std::string info,
			const ECode error);

		/**
		* \brief Destructor
		*/
		virtual ~CGeneralException();


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
		CGeneralException& Rethrow(const std::string info);

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
		CGeneralException& Rethrow(const std::string info,
			const en_uint32 newError);



	private:
		//*************************************************************************
		// Disable Standard Constructor
		//*************************************************************************
		/** Default Constructor (prohibited) */
		CGeneralException();

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

#endif
