/** \file PackageHanlder.cpp
* Implementation file for the CPackageHandler class
* \author Tiago Gomes
* \date 08.11.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "PackageHandler.h"

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------
// byte index of each field (common to all packages)
const uint32_t IDENTIFIER_BYTE_INDEX = 0;
const uint32_t SIZE_BYTE_INDEX = 0;

// MEMORY MAPPED PKG: byte index of each field 
const uint32_t MM_FRAME_NR_BYTE_INDEX = 8;
const uint32_t MM_CMD_BYTE_INDEX = 10;
const uint32_t MM_ADDRESS_BYTE_INDEX = 12;
const uint32_t MM_PAYLOAD_BYTE_INDEX = 16;

// ASYNC PKG: byte index of each field
const uint32_t AS_TYPE_BYTE_INDEX = 8;
const uint32_t AS_PAYLOAD_BYTE_INDEX = 12;

// ERROR PKG: byte index of each field
const uint32_t ER_CODE_BYTE_INDEX = 8;
const uint32_t ER_PAYLOAD_BYTE_INDEX = 12;

// PRINT PKG: byte index of each field
const uint32_t PR_PAYLOAD_BYTE_INDEX = 8;

// Minimum value allowed for the SIZE field of each package
const uint32_t MM_SIZE_MIN_VALUE = 8;
const uint32_t AS_SIZE_MIN_VALUE = 4;
const uint32_t ER_SIZE_MIN_VALUE = 4;
//const uint32_t PR_SIZE_MIN_VALUE = 0; There is no minimum for Print package


//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------

CPackageHandler::CPackageHandler(ICommunicationInterface* CommunicationInterface_p, IAsyncType* Async_p, IAsyncType* Error_p, IAsyncType* Print_p) :
	m_CommunicationInterface_p(CommunicationInterface_p),
	m_Async_p(Async_p),
	m_Error_p(Error_p),
	m_Print_p(Print_p)
{
	m_CrcEngine = new Crc32(POLYNOMIAL, INITIAL_REMAINDER, FINAL_XOR_VALUE, REFLECT_DATA, REFLECT_REMAINDER);
}

CPackageHandler::~CPackageHandler()
{
	delete m_CrcEngine;
}

//-------------------------------------------------------------------------------------------------
// Method definitions
//-------------------------------------------------------------------------------------------------
string CPackageHandler::GetName()
{
	return m_name;
}

void CPackageHandler::SendPackage(CMemoryMappedPackage & MemoryMappedPackage)
{
	vector <uint32_t> Package;
	uint32_t Crc;
	// Fill a 32-bit vector with Package content
	Package.push_back(static_cast<uint32_t>(MemoryMappedPackage.m_identifier));
	Package.push_back(MemoryMappedPackage.m_size);
	Package.push_back(MemoryMappedPackage.m_command << 16 | MemoryMappedPackage.m_frameNumber);
	Package.push_back(MemoryMappedPackage.m_addressResponse);
	Package.insert(Package.end(), MemoryMappedPackage.m_payload.begin(), MemoryMappedPackage.m_payload.end());
	Crc = m_CrcEngine->Compute(Package.data(), Package.size() * sizeof(uint32_t));
	Package.push_back(Crc);
	// convert uint32_t vector to uint8_t vector
	vector <uint8_t>  Pkg;
	uint8_t * byte_p = (uint8_t *)Package.data();

	for (uint32_t i = 0; i < Package.size() * 4; i++)
		Pkg.push_back(*byte_p++);
	m_CommunicationInterface_p->SendData(Pkg);
}

void CPackageHandler::SendPackage(CAsyncPackage & AsyncPackage)
{
	vector <uint32_t> Package;
	uint32_t Crc;

	// Fill a 32-bit vector with Package content
	Package.push_back(static_cast<uint32_t>(AsyncPackage.m_identifier));
	Package.push_back(AsyncPackage.m_size);
	Package.push_back(static_cast<uint32_t>(AsyncPackage.m_type));
	Package.insert(Package.end(), AsyncPackage.m_payload.begin(), AsyncPackage.m_payload.end());
	Crc = m_CrcEngine->Compute(Package.data(), Package.size() * sizeof(uint32_t));
	Package.push_back(Crc);

	// convert uint32_t vector to uint8_t vector
	vector <uint8_t>  Pkg;
	uint8_t * byte_p = (uint8_t *)Package.data();

	for (uint32_t i = 0; i < Package.size() * 4; i++)
		Pkg.push_back(*byte_p++);

	m_CommunicationInterface_p->SendData(Pkg);
}

void CPackageHandler::SendPackage(CErrorPackage & ErrorPackage)
{
	/*vector <uint32_t> Package;
	uint32_t Crc;

	// Fill a 32-bit vector with Package content
	Package.push_back(static_cast<uint32_t>(ErrorPackage.m_identifier));
	Package.push_back(ErrorPackage.m_size);
	Package.push_back(static_cast<uint32_t>(ErrorPackage.m_code));
	Package.insert(Package.end(), ErrorPackage.m_payload.begin(), ErrorPackage.m_payload.end());
	Crc = m_CrcEngine->Compute(Package.data(), Package.size() * sizeof(uint32_t));
	Package.push_back(Crc);

	// convert uint32_t vector to uint8_t vector
	vector <uint8_t>  Pkg;
	uint8_t * byte_p = (uint8_t *)Package.data();

	for (uint32_t i = 0; i < Package.size() * 4; i++)
		Pkg.push_back(*byte_p++);

	m_CommunicationInterface_p->SendData(Pkg);*/

	vector <uint8_t> Package;
	uint32_t Crc;

	// copy identifier to vector<uint8_t>
	Package.push_back(static_cast<uint32_t>(ErrorPackage.m_identifier) >> 0 & 0xFF);
	Package.push_back(static_cast<uint32_t>(ErrorPackage.m_identifier) >> 8 & 0xFF);
	Package.push_back(static_cast<uint32_t>(ErrorPackage.m_identifier) >> 16 & 0xFF);
	Package.push_back(static_cast<uint32_t>(ErrorPackage.m_identifier) >> 24 & 0xFF);

	// copy size to vector<uint8_t>
	Package.push_back(ErrorPackage.m_size >> 0 & 0xFF);
	Package.push_back(ErrorPackage.m_size >> 8 & 0xFF);
	Package.push_back(ErrorPackage.m_size >> 16 & 0xFF);
	Package.push_back(ErrorPackage.m_size >> 24 & 0xFF);

	// copy ErrorCode to vector<uint8_t>
	Package.push_back(ErrorPackage.m_code >> 0 & 0xFF);
	Package.push_back(ErrorPackage.m_code >> 8 & 0xFF);
	Package.push_back(ErrorPackage.m_code >> 16 & 0xFF);
	Package.push_back(ErrorPackage.m_code >> 24 & 0xFF);

	// copy payload to vector<uint8_t>
	Package.insert(Package.end(), ErrorPackage.m_payload.begin(), ErrorPackage.m_payload.end());

	Crc = m_CrcEngine->Compute(Package.data(), Package.size());
	// copy crc to vector<uint8_t>
	Package.push_back(Crc >> 0 & 0xFF);
	Package.push_back(Crc >> 8 & 0xFF);
	Package.push_back(Crc >> 16 & 0xFF);
	Package.push_back(Crc >> 24 & 0xFF);

	m_CommunicationInterface_p->SendData(Package);
}

void CPackageHandler::SendPackage(CPrintPackage & PrintPackage)
{
	vector <uint8_t> Package;
	uint32_t Crc;

	// copy identifier to vector<uint8_t>
	Package.push_back(static_cast<uint32_t>(PrintPackage.m_identifier) >> 0 & 0xFF);
	Package.push_back(static_cast<uint32_t>(PrintPackage.m_identifier) >> 8 & 0xFF);
	Package.push_back(static_cast<uint32_t>(PrintPackage.m_identifier) >> 16 & 0xFF);
	Package.push_back(static_cast<uint32_t>(PrintPackage.m_identifier) >> 24 & 0xFF);

	// copy size to vector<uint8_t>
	Package.push_back(PrintPackage.m_size >> 0 & 0xFF);
	Package.push_back(PrintPackage.m_size >> 8 & 0xFF);
	Package.push_back(PrintPackage.m_size >> 16 & 0xFF);
	Package.push_back(PrintPackage.m_size >> 24 & 0xFF);

	// copy payload to vector<uint8_t>
	Package.insert(Package.end(), PrintPackage.m_payload.begin(), PrintPackage.m_payload.end());

	Crc = m_CrcEngine->Compute(Package.data(), Package.size());
	// copy crc to vector<uint8_t>
	Package.push_back(Crc >> 0 & 0xFF);
	Package.push_back(Crc >> 8 & 0xFF);
	Package.push_back(Crc >> 16 & 0xFF);
	Package.push_back(Crc >> 24 & 0xFF);
	m_CommunicationInterface_p->SendData(Package);
}


uint32_t CPackageHandler::ReceivePackage(CMemoryMappedPackage& ReceivedPackage)
{
	uint32_t CrcFromPackage;
	uint32_t CalculatedCrc;
	uint32_t Result = INVALID_PACKAGE;

	bool MemoryMappedPackageWasReceived = false;
	bool PackageIsInvalid = false;

	// loop until a memory mapped package is received OR Invalid package is detected OR a timeout happens:
	//	- if we receive another type of package, it will be forwarded to the corresponding class
	//  - if we receive a memory mapped package, we return from this function
	//  - if we receive an unknown package, we return INVALID_PACKAGE
	//  - if we don't receive any package at all, the communication interface should trigger an exception after some defined time
	vector <uint8_t> PackageHeader(4, 0);
	while (MemoryMappedPackageWasReceived == false && PackageIsInvalid == false)
	{

		vector <uint8_t> PackageSize;
		vector <uint8_t> PackageBody;
		vector <uint8_t> Package;
#if defined(_WIN32)
		clock_t startTime = clock();
#endif
		// READ identifier
		uint32_t Identifier;
		uint32_t Size = 0;
		Result = INVALID_PACKAGE;

		while (Result == INVALID_PACKAGE) {
			// GET Package Header
			vector <uint8_t> inputElement;
			int32_t numBytes = (int32_t)m_CommunicationInterface_p->ReceiveData(inputElement, 1);// in order to be sure to detect start of packet we need to check after every byte

			if (numBytes == 1) {
				PackageHeader.erase(PackageHeader.begin());
				PackageHeader.push_back(inputElement[0]);

				uint32_t completeHeader = PackageHeader[0] | (PackageHeader[1] << 8) | (PackageHeader[2] << 16) | (PackageHeader[3] << 24);
			}
			else if (numBytes == -1) {
				Result = NODATA_ERROR;
				break;
			}

			Identifier = GetInt32FromVector(PackageHeader, IDENTIFIER_BYTE_INDEX);
			switch (static_cast<EProductionTestUtilPackages_t>(Identifier))
			{
			case EProductionTestUtilPackages_t::MemoryMapped:
			case EProductionTestUtilPackages_t::Async:
			case EProductionTestUtilPackages_t::Error:
			case EProductionTestUtilPackages_t::Print:
				Result = VALID_HEADER;
				m_CommunicationInterface_p->ReceiveData(PackageSize, 4);
				break;
			default:
				//the package identifier was either corrupted during transmission or protocol was not followed, then we return an INVALID_PACKAGE
				Result = INVALID_PACKAGE;
#if defined(_WIN32) // Clock is not available on Microblaze, timeout is not required there anyway
				if (((((float)(clock() - startTime)) / CLOCKS_PER_SEC) > m_Timeout)) {
					return TIMEOUT;
				}
#endif
				break;
			}
		}
		if (Result == NODATA_ERROR) {
			break;
		}
		switch (static_cast<EProductionTestUtilPackages_t>(Identifier))
		{
		case EProductionTestUtilPackages_t::MemoryMapped:
		case EProductionTestUtilPackages_t::Async:
		case EProductionTestUtilPackages_t::Error:
		case EProductionTestUtilPackages_t::Print:
		{ // Valid Packet detected
			// READ size
			Size = GetInt32FromVector(PackageSize, SIZE_BYTE_INDEX);

			// GET Package Body
			uint32_t receivedBodySize = 0;

			while (receivedBodySize < (Size + 4)) {
				vector <uint8_t> immediateBuffer;
				// Size + 4 to receive the CRC
				uint32_t receivedNBytes = m_CommunicationInterface_p->ReceiveData(immediateBuffer, Size + 4 - receivedBodySize);
				if (receivedNBytes != -1) {
					immediateBuffer.resize(receivedNBytes);
					PackageBody.insert(PackageBody.end(), immediateBuffer.begin(), immediateBuffer.end());
					receivedBodySize += receivedNBytes;

				}
			}
			Package.insert(Package.end(), PackageHeader.begin(), PackageHeader.end());
			Package.insert(Package.end(), PackageSize.begin(), PackageSize.end());
			Package.insert(Package.end(), PackageBody.begin(), PackageBody.end());



			break;
		}
		default:
			//the package identifier was either corrupted during transmission or protocol was not followed, then we return an INVALID_PACKAGE
			Result = INVALID_PACKAGE;
			PackageIsInvalid = true;
			break;
		}
		switch (static_cast<EProductionTestUtilPackages_t>(Identifier))
		{
		case EProductionTestUtilPackages_t::MemoryMapped:
		{
			if (Size < MM_SIZE_MIN_VALUE)
			{
				// the 'size' field for a Memory Mapped Package was either corrupted during transmission or
				// protocol was not followed, then we return an INVALID_PACKAGE 
				Result = INVALID_PACKAGE;
				PackageIsInvalid = true;
				if (m_observer != nullptr)
					m_observer->Update(m_name, EObserverLevel_t::Warning, "Corrupted Memory Mapped Package received.");

			}
			else
			{
				ReceivedPackage.m_identifier = EProductionTestUtilPackages_t::MemoryMapped;
				ReceivedPackage.m_size = Size;
				ReceivedPackage.m_frameNumber = GetInt16FromVector(Package, MM_FRAME_NR_BYTE_INDEX);
				ReceivedPackage.m_command = GetInt16FromVector(Package, MM_CMD_BYTE_INDEX);
				ReceivedPackage.m_addressResponse = GetInt32FromVector(Package, MM_ADDRESS_BYTE_INDEX);
				ReceivedPackage.m_payload.clear();
				for (uint32_t byteIndex = 0; byteIndex < Size - 8; byteIndex = byteIndex + 4)
				{
					ReceivedPackage.m_payload.push_back(GetInt32FromVector(Package, MM_PAYLOAD_BYTE_INDEX + byteIndex));
				}

				CrcFromPackage = GetInt32FromVector(Package, MM_PAYLOAD_BYTE_INDEX + Size - 8);
				CalculatedCrc = m_CrcEngine->Compute(Package.data(), MM_PAYLOAD_BYTE_INDEX + Size - 8);

				Result = (CalculatedCrc != CrcFromPackage) ? CRC_ERROR : VALID_PACKAGE;
				MemoryMappedPackageWasReceived = true;
			}
			break;
		}
		case EProductionTestUtilPackages_t::Async:
		{
			if (Size < AS_SIZE_MIN_VALUE)
			{
				// the 'size' field for a Async Package was either corrupted during transmission or
				// protocol was not followed, then we return an INVALID_PACKAGE 
				Result = INVALID_PACKAGE;
				PackageIsInvalid = true;
				if (m_observer != nullptr)
					m_observer->Update(m_name, EObserverLevel_t::Warning, "Corrupted Async Package received.");
			}
			else
			{
				CrcFromPackage = GetInt32FromVector(Package, AS_PAYLOAD_BYTE_INDEX + Size - 4);
				CalculatedCrc = m_CrcEngine->Compute(Package.data(), AS_PAYLOAD_BYTE_INDEX + Size - 4);

				if (CalculatedCrc == CrcFromPackage)
				{
					Result = INVALID_PACKAGE;
					PackageBody.resize(PackageBody.size() - 4); // remove CRC value
					m_Async_p->ReceivedData(PackageBody);
				}
				else
				{
					Result = INVALID_PACKAGE;
					PackageIsInvalid = true;
					if (m_observer != nullptr)
						m_observer->Update(m_name, EObserverLevel_t::Warning, "Async Package received with wrong CRC.");
				}
			}

			break;
		}
		case EProductionTestUtilPackages_t::Error:
		{
			if (Size < ER_SIZE_MIN_VALUE)
			{
				// the 'size' field for a Error Package was either corrupted during transmission or
				// protocol was not followed, then we return an INVALID_PACKAGE 
				Result = INVALID_PACKAGE;
				PackageIsInvalid = true;
				if (m_observer != nullptr)
					m_observer->Update(m_name, EObserverLevel_t::Warning, "Corrupted Error Package received.");
			}
			else
			{
				CrcFromPackage = GetInt32FromVector(Package, ER_PAYLOAD_BYTE_INDEX + Size - 4);
				CalculatedCrc = m_CrcEngine->Compute(Package.data(), ER_PAYLOAD_BYTE_INDEX + Size - 4);

				if (CalculatedCrc == CrcFromPackage)
				{
					Result = INVALID_PACKAGE;
					PackageBody.resize(PackageBody.size() - 4); // remove CRC value
					m_Error_p->ReceivedData(PackageBody);
				}
				else
				{
					Result = INVALID_PACKAGE;
					PackageIsInvalid = true;
					if (m_observer != nullptr)
						m_observer->Update(m_name, EObserverLevel_t::Warning, "Error Package received with wrong CRC.");
				}
			}

			break;
		}
		case EProductionTestUtilPackages_t::Print:
		{
			CrcFromPackage = GetInt32FromVector(Package, PR_PAYLOAD_BYTE_INDEX + Size);
			CalculatedCrc = m_CrcEngine->Compute(Package.data(), PR_PAYLOAD_BYTE_INDEX + Size);

			if (CalculatedCrc == CrcFromPackage)
			{
				PackageBody.resize(PackageBody.size() - 4); // remove CRC value
				m_Print_p->ReceivedData(PackageBody);
				PackageIsInvalid = true;
				Result = INVALID_PACKAGE;
			}
			else
			{
				Result = INVALID_PACKAGE;
				PackageIsInvalid = true;
				if (m_observer != nullptr)
					m_observer->Update(m_name, EObserverLevel_t::Warning, "Print Package received with wrong CRC.");
			}

			break;
		}
		default:
			//the package identifier was either corrupted during transmission or protocol was not followed, then we return an INVALID_PACKAGE 
			Result = INVALID_PACKAGE;
			PackageIsInvalid = true;
			break;
		}
	}
	return Result;
}


uint32_t CPackageHandler::ReceivePackage(CAsyncPackage & ReceivedPackage)
{
	uint32_t CrcFromPackage;
	uint32_t CalculatedCrc;
	uint32_t Result = INVALID_PACKAGE;

	bool AsyncPackageWasReceived = false;
	bool PackageIsInvalid = false;

	// loop until a memory mapped package is received OR Invalid package is detected OR a timeout happens:
	//	- if we receive another type of package, it will be forwarded to the corresponding class
	//  - if we receive a memory mapped package, we return from this function
	//  - if we receive an unknown package, we return INVALID_PACKAGE
	//  - if we don't receive any package at all, the communication interface should trigger an exception after some defined time
	while (AsyncPackageWasReceived == false && PackageIsInvalid == false)
	{
		vector <uint8_t> PackageHeader(4, 0);
		vector <uint8_t> PackageSize;
		vector <uint8_t> PackageBody;
		vector <uint8_t> Package;
#if defined(_WIN32)
		clock_t startTime = clock();
#endif
		// READ identifier
		uint32_t Identifier;
		uint32_t Size = 0;
		Result = INVALID_PACKAGE;

		while (Result == INVALID_PACKAGE) {
			// GET Package Header
			vector <uint8_t> inputElement;
			m_CommunicationInterface_p->ReceiveData(inputElement, 1); // in order to be sure to detect start of packet we need to check after every byte
			PackageHeader.erase(PackageHeader.begin());
			PackageHeader.push_back(inputElement[0]);

			Identifier = GetInt32FromVector(PackageHeader, IDENTIFIER_BYTE_INDEX);
			switch (static_cast<EProductionTestUtilPackages_t>(Identifier))
			{
			case EProductionTestUtilPackages_t::Async:
				Result = 4;
				m_CommunicationInterface_p->ReceiveData(PackageSize, 4);
				break;
			default:
				//the package identifier was either corrupted during transmission or protocol was not followed, then we return an INVALID_PACKAGE
				Result = INVALID_PACKAGE;
#if defined(_WIN32)
				if (((((float)(clock() - startTime)) / CLOCKS_PER_SEC) > m_Timeout)) {
					return TIMEOUT;
				}
#endif
				break;
			}
		}


		switch (static_cast<EProductionTestUtilPackages_t>(Identifier))
		{
		case EProductionTestUtilPackages_t::Async:
		{ // Valid Packet detected
		  // READ size
			Size = GetInt32FromVector(PackageSize, SIZE_BYTE_INDEX);



			// GET Package Body
			m_CommunicationInterface_p->ReceiveData(PackageBody, Size + 4); // + 4 to receive the CRC



			Package.insert(Package.end(), PackageHeader.begin(), PackageHeader.end());
			Package.insert(Package.end(), PackageSize.begin(), PackageSize.end());
			Package.insert(Package.end(), PackageBody.begin(), PackageBody.end());



			break;
		}
		default:
			//the package identifier was either corrupted during transmission or protocol was not followed, then we return an INVALID_PACKAGE
			Result = INVALID_PACKAGE;
			PackageIsInvalid = true;
			break;
		}

		switch (static_cast<EProductionTestUtilPackages_t>(Identifier))
		{
		case EProductionTestUtilPackages_t::Async:
		{
			if (Size < AS_SIZE_MIN_VALUE)
			{
				// the 'size' field for a Async Package was either corrupted during transmission or
				// protocol was not followed, then we return an INVALID_PACKAGE 
				Result = INVALID_PACKAGE;
				PackageIsInvalid = true;
				if (m_observer != nullptr)
					m_observer->Update(m_name, EObserverLevel_t::Warning, "Corrupted Async Package received.");
			}
			else
			{
				CrcFromPackage = GetInt32FromVector(Package, AS_PAYLOAD_BYTE_INDEX + Size - 4);
				CalculatedCrc = m_CrcEngine->Compute(Package.data(), AS_PAYLOAD_BYTE_INDEX + Size - 4);

				if (CalculatedCrc == CrcFromPackage)
				{
					Result = VALID_PACKAGE;
					PackageBody.resize(PackageBody.size() - 4); // remove CRC value
					m_Async_p->ReceivedData(PackageBody);
					AsyncPackageWasReceived = true;
				}
				else
				{
					Result = INVALID_PACKAGE;
					PackageIsInvalid = true;
					if (m_observer != nullptr)
						m_observer->Update(m_name, EObserverLevel_t::Warning, "Async Package received with wrong CRC.");
				}
			}

			break;
		}
		default:
			//the package identifier was either corrupted during transmission or protocol was not followed, then we return an INVALID_PACKAGE 
			Result = INVALID_PACKAGE;
			PackageIsInvalid = true;
			break;
		}
	}
	return Result;
}



uint32_t CPackageHandler::GetInt32FromVector(const vector <uint8_t>& dataVector, uint32_t byteIndex)
{
	uint32_t result = 0;
	uint8_t byte;

	for (uint32_t b_index = byteIndex; b_index < byteIndex + 4; b_index++)
	{
		byte = dataVector.at(b_index);   	// read 1 byte
		result = result >> 8;				// make room for the new byte by shifting right
		result = result | (byte << 24);		// put byte on the most significant byte of the word
	}

	return result;
}

uint16_t CPackageHandler::GetInt16FromVector(const vector <uint8_t>& dataVector, uint32_t byteIndex)
{
	uint16_t result = 0;
	uint8_t byte;

	for (uint32_t b_index = byteIndex; b_index < byteIndex + 2; b_index++)
	{
		byte = dataVector.at(b_index);   	// read 1 byte
		result = result >> 8;				// make room for the new byte by shifting right
		result = result | (byte << 8);		// put byte on the most significant byte of the word
	}

	return result;
}

void CPackageHandler::DiscardData()
{
	m_CommunicationInterface_p->DiscardData();
}

void CPackageHandler::SetTimeout(uint32_t Timeout)
{
	m_Timeout = Timeout;
}

void CPackageHandler::AttachObserver(CObserver * observer)
{
	m_observer = observer;
}
