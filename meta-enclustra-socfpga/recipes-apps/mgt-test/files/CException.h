/**************************************************************************************************
**  Copyright (c) 2015 by Enclustra, Switzerland
**  All rights reserved.
**************************************************************************************************/

#ifndef _EnUtil_CException_h
#define _EnUtil_CException_h

//*****************************************************************************
// Includes
//*****************************************************************************
#include "EnTypes.h"
#include "Conversions.h"
#include <string>
#include <map>
#include <iostream>
#include <string.h>
using std::string;

//*****************************************************************************
// Macros
//*****************************************************************************
#define EN_EXPT_ENABLE_TRACE true

#define EN_EXPT_SHORT_FILE (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define EN_EXPT_INFO std::string(std::string("  file: ") + std::string(EN_EXPT_SHORT_FILE) + std::string("  func: ") + std::string(__FUNCTION__) + std::string("()") + std::string("  line: ") + EnUtil::Conversions::ConvertInt(__LINE__))
#define EN_EXPT_RETHROW(exception) {throw exception.Rethrow(EN_EXPT_INFO);}
#define EN_EXPT_REINTERPRET(exception, newError) {throw exception.Rethrow(EN_EXPT_INFO,newError);}
#define EN_EXPT_PRINT_TRACE(ex) {std::cout << ex.GetTrace();}
#define EN_EXPT_CPPUTEST_START bool excptoccurred=false;try{
#define EN_EXPT_CPPUTEST_END }catch(CException &ex){EN_EXPT_PRINT_TRACE(ex);FAIL("Unexpected Exception");}
#define EN_EXPT_CPPUTEST_EXPEXTED(exp) EN_EXPT_CPPUTEST_EXPEXTED_TYPE(CException, exp)
#define EN_EXPT_CPPUTEST_EXPEXTED_TYPE(type,exp) }catch(type &ex){if (exp != ex.GetCode()){FAIL("Wrong Exception Code");}excptoccurred=true;}catch(...){FAIL("Wrong Exception Type");}if(!excptoccurred){FAIL("No Exception occurred");}


//*****************************************************************************
// Forward Definitions
//*****************************************************************************
namespace EnUtil {

	//*****************************************************************************
	// Definitions
	//*****************************************************************************
	/**
	* \brief	Enclustra library exception base class. All exceptions must be implemented
	*			as child class of this exception.\n
	*			The easiest way to do so is to copy CGeneralException.h and CGeneralException.cpp,
	*			Rename the class everywhere required and chagne the exception codes as well as the
	*			corresponding messages.\n
	*			Do not change anything else than the things mentioned above and do not add any
	*			additional variables if you don't udnerstand the concept completely. It works but
	*			it is quite sensitive to changes.\n
	*			For examples how to throw, rethrow, catch and test exceptions, refer to the
	*			test code (TCException.cpp) as well as the bit BitManipulation code (implementation
	*			and test code).\n
	*			It is recommended to add try/catch within every function which could potentially
	*			get exceptions from callees. If exceptions cannot be handled, they should be rethrown
	*			using the EN_EXPT_RETHROW macro within the catch claus. This leads to the trace within
	*			the exception being updated correctly.
	*
	* \author Oliver Bruendler
	*/
	class CException
	{
	public:

		//*************************************************************************
		// Exception Type ID
		//*************************************************************************
		/** ID of this exception class*/
		static en_uint32 ID;

		//*************************************************************************
		// User Error Codes
		//*************************************************************************
		/** No error */
		static const en_uint32 USER_ERROR_NO_ERROR = 0;
		/** Internal error, see trace */
		static const en_uint32 USER_ERROR_INTERNAL_ERROR = 1;

		//*************************************************************************
		// Construct / Destruct
		//*************************************************************************		
		/**
		* \brief Constructor
		*
		* \param info	Exception information to add to trace
		* \param error	Error number to be stored within the exception
		*/
		CException(const std::string info,
			const en_uint32 error);

		/**
		* \brief Destructor
		*/
		virtual ~CException();

		//*************************************************************************
		// Public Functions
		//*************************************************************************		

		/**
		* \brief Assign user error code
		*
		* This function can be used to pass project specific error numbers to the user.
		*
		* \param code	Error code to assign
		* \note			Do not use the codes 0 (reserved for success) or 1 (internal error, to be investigated by looking at the trace)
		*/
		void AssignUserCode(const en_uint32 code);

		/**
		* \brief Get user error code
		*
		* \return Error code assigned by AssignUserCode()
		*/
		const en_uint32 GetUserCode();

		/**
		* \brief Get exception type ID
		*
		* This function can be used to find out the type of the exception initially thrown.
		*
		* \return Exception type ID
		*/
		const en_uint32 GetTypeId();

		/**
		* \brief Get error code
		*
		* Note that the error codes can change. Only compare the error code to
		* static codes defined in the exception classes.
		*
		* \return Error code
		*/
		const en_uint32 GetCode() const;

		/**
		* \brief Append additional information to trace
		*/
		void AppendInfo(std::string info);

		/**
		* \brief Get trace
		*
		* This function allows to get the error trace string which can be used for debugging.
		*
		* \return Error trace
		*/
		const std::string GetTrace() const;

		/**
		* \brief Get error message
		*
		* \return		Message
		*/
		std::string GetMessage_() const; // GetMessage is redefined in windows.h (which is included by boost) and then causes conflit with this method

		/**
		* \brief Rethrow exception
		*
		* If this function is used in a catch statement to rethrow the exception, the trace
		* is extended with file/function/line information and the passed exception information.
		*
		* \param info	Exception information to add to trace
		* \return		Updated exception
		*/
		CException& Rethrow(const std::string info);

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
		CException& Rethrow(const std::string info,
			const en_uint32 newError);

		/**
		* \brief	Free all memory (static memory too)
		*/
		static void FreeMemory();


	protected:
		//*************************************************************************
		// Child Exceptions
		//*************************************************************************
		/**
		* \brief Child exception constructor
		*
		* \param id		ID of the child exception class
		*/
		CException(const en_uint32 id);

		//*************************************************************************
		// Protected Functions
		//*************************************************************************

		/**
		* \brief Set error code
		*
		* \param error	Error code to set
		*/
		void SetCode(const en_uint32 error);

		/**
		* \brief Get next free exception type ID
		*
		* This function MUST be used by all child classes to get their ID. The ID can be used
		* to find out which exception type was orignially thrown.
		*
		* \return Next free exception type ID
		*/
		static en_uint32 GetNextFreeTypeId();

		/**
		* \brief	Get memory allocation trun
		*
		* The memory allocation run coutner is incremented every time, the static memory
		* must be allocated again (i.e. after every call of FreeMemory()).
		*
		* \return Memory allocation run
		*/
		static en_uint32 GetMemAllocRun();

		/** Error codes */
		static std::map<en_uint32, std::string> s_messages;

	private:
		//*************************************************************************
		// Disable Standard Constructor
		//*************************************************************************
		/** Default Constructor  (prohibited)*/
		CException();

		//*************************************************************************
		// Signleton Variables
		//*************************************************************************		
		/** Memory allocation run (see GetMemAllocRun()) */
		static en_uint32 s_memAllocRun;
		/** Number of the last memory allocation run executed for this class */
		static en_uint32 s_memAllocatedLast;

		//*************************************************************************
		// Static Variables
		//*************************************************************************
		/** Next free error number counter */
		static en_uint32 s_nextErrorNumber;
		/** Next free type number counter */
		static en_uint32 s_nextTypeNumber;

		//*************************************************************************
		// Private Functions
		//*************************************************************************
		/**
		* \brief Set error messges for this class
		*/
		virtual void SetMessages() {};

		/**
		* \brief Get next free error code
		*
		* This function is used by friend class CExptCode to assign error codes.
		*
		* \return	Next free error code
		*/
		static en_uint32 GetNextFreeCode();

		//*************************************************************************
		// variables
		//*************************************************************************
		/** Exception trace */
		std::string m_trace;

		/** Error number */
		en_uint32 m_code;

		/** User error code */
		en_uint32 m_userCode;

		/** Exception type ID */
		en_uint32 m_id;

	protected:
		//*************************************************************************
		// Exception Code Class Definition
		//*************************************************************************
		/**
		* \brief	This class is used to do strong type checking for an en_uint32 which
		*			is required to prevent error codes from one Exception classe being passed
		*			to the constructor of another exception class.
		*/
		template<typename T>
		class CExptCode
		{
		public:
			/**
			* \brief Default constructor
			*
			* Creates a new exception code with a uniuqe number
			*/
			CExptCode() : m_code(CException::GetNextFreeCode()) {}

			/**
			* Conversion to en_uint32
			*
			* \return	generated Exception code
			*/
			operator en_uint32() const { return m_code; }

			/**
			* Assignment to en_uint32
			*
			* \param code	Exception code to conver to en_uint32
			* \return		Generated en_uint32
			*/
			en_uint32 operator=(CExptCode code) { return m_code; }

			/**
			* Assignment from en_uint32
			*
			* \param code	en_uint32 to conver to Exception code
			* \return		Exception code generated
			*/
			CExptCode operator=(en_uint32 code) { return CExptCode(code); }
		private:

			/** Error code */
			en_uint32 m_code;
		};
	};
}

#endif
