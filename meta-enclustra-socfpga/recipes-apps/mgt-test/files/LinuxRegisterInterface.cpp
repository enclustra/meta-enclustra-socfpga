/** \file RegisterInterface.cpp
* Implementation file for the RegisterInterface class
* \author Tiago Gomes
* \date 12.07.2016
*
* Copyright (c) 2016 Enclustra GmbH, Switzerland.
* All rights reserved.
*/


//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "LinuxRegisterInterface.h"
#include "CProductionTestException.h"

using namespace std;
using namespace EnUtil;

//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------

CLinuxRegisterInterface::CLinuxRegisterInterface(off_t offset, size_t length)
{
	// Truncate offset to a multiple of the page size, or mmap will fail.
	size_t pagesize = sysconf(_SC_PAGE_SIZE);
	off_t page_base = (offset / pagesize) * pagesize;
	off_t page_offset = offset - page_base;

	// open dev mem, use mmap to map the memory
	m_fd = open("/dev/mem", O_RDWR|O_SYNC);
	m_mem = static_cast<uint32_t*>(mmap(NULL, page_offset + length, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, page_base));
	if (m_mem == MAP_FAILED) {
		throw CProductionTestException(EN_EXPT_INFO,CProductionTestException::ECode_MmapFailed);
	}

	m_page_base = page_base;
}

CLinuxRegisterInterface::~CLinuxRegisterInterface()
{

}

string CLinuxRegisterInterface::GetName()
{
	return m_name;
}

uint32_t CLinuxRegisterInterface::Read(uint32_t address)
{
	return m_mem[(address - m_page_base) / sizeof(uint32_t)];
}


void CLinuxRegisterInterface::ReadBlock(std::uint32_t address, std::uint32_t size, std::vector<uint32_t>& data)
{
	if (size % 4 != 0)  // check if size is not multiple of DWORD
	{
		size = ((size - 1) / 4 + 1) * 4; // round-up to a multiple of 4
	}
	data.clear();
	for (uint32_t dwordIndex = 0; dwordIndex < size / 4; dwordIndex++, address += 4)
	{
		data.push_back(Read(address));
		//data.push_back(m_mem[(address - m_page_base) / sizeof(uint32_t)]);
	}
}

void CLinuxRegisterInterface::Write(uint32_t address, uint32_t data)
{
	uint32_t addr = (address - m_page_base) / sizeof(uint32_t);
	m_mem[addr] = data;
}

void CLinuxRegisterInterface::WriteBlock(std::uint32_t address, const std::vector<uint32_t>& data)
{
	for (uint32_t dwordIndex = 0; dwordIndex < data.size(); dwordIndex++)
	{
		this->Write(address, data.at(dwordIndex));
		address += 4;
	}
}

void CLinuxRegisterInterface::SetBits(uint32_t address, uint32_t data)
{
	Write(address, Read(address) | data);
	//m_mem[(address - m_page_base) / sizeof(uint32_t)] = m_mem[(address - m_page_base) / sizeof(uint32_t)] | (data);
}

void CLinuxRegisterInterface::ClearBits(uint32_t address, uint32_t data)
{
	Write(address, Read(address) & (~data));
	//m_mem[(address - m_page_base) / sizeof(uint32_t)] = m_mem[(address - m_page_base) / sizeof(uint32_t)] & (~data);
}

