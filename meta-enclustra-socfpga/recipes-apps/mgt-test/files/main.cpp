// ----------------------------------------------------------------------------------------------------
// Copyright (c) 2023 Enclustra GmbH, Switzerland (info@enclustra.com)
// ----------------------------------------------------------------------------------------------------
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <mutex>          // std::mutex
#include <arpa/inet.h>
#include <iostream>

#include "PackageHandler.h"
#include "LinuxComPort.h"
#include "LinuxRegisterInterface.h"

#include "LinuxIntelMgtTester.h"

CPackageHandler* PkgHandle_p;
CLinuxRegisterInterface *RegisterInterface_p;
uint PacketCounter = 0;

static void ReceiveHandler(int status)
{
    PacketCounter++;
}

static void ProcessPacket()
{
	CMemoryMappedPackage Rx_MM_Pkg;
	uint32_t error = PkgHandle_p->ReceivePackage(Rx_MM_Pkg); // wait for data

	if (error == VALID_PACKAGE)
	{
		switch(Rx_MM_Pkg.m_command)
		{
		case READ_CMD:
		{
			// process request
			vector <uint32_t> payload;
			uint32_t address = Rx_MM_Pkg.m_addressResponse;
			uint32_t numWordsToRead = Rx_MM_Pkg.m_payload.at(0)/4;

			for (uint32_t word = 0; word < numWordsToRead; word++, address+=4)
			{
				payload.push_back(RegisterInterface_p->Read(address));
			}

			// send response
			CMemoryMappedPackage Tx_MM_Pkg(READ_RESPONSE_CMD, Rx_MM_Pkg.m_frameNumber, RESPONSE_SUCCESS, payload);
			PkgHandle_p->SendPackage(Tx_MM_Pkg);
			break;
		}
		case WRITE_CMD:
		{
			// process request
			vector <uint32_t> payload;
			uint32_t address = Rx_MM_Pkg.m_addressResponse;
			uint32_t numWordsToWrite = Rx_MM_Pkg.m_payload.size();

			for (uint32_t word = 0; word < numWordsToWrite; word++, address+=4)
			{
				RegisterInterface_p->Write(address, Rx_MM_Pkg.m_payload.at(word));
			}

			// send response
			CMemoryMappedPackage Tx_MM_Pkg(WRITE_RESPONSE_CMD, Rx_MM_Pkg.m_frameNumber, RESPONSE_SUCCESS, payload);
			PkgHandle_p->SendPackage(Tx_MM_Pkg);
			break;
		}
		case SETBITS_CMD:
		{
			// process request
			vector <uint32_t> payload;
			uint32_t address = Rx_MM_Pkg.m_addressResponse;
			uint32_t numWordsToWrite = Rx_MM_Pkg.m_payload.size();

			for (uint32_t word = 0; word < numWordsToWrite; word++, address++)
			{
				RegisterInterface_p->SetBits(address, Rx_MM_Pkg.m_payload.at(word));
			}

			// send response
			CMemoryMappedPackage Tx_MM_Pkg(SETBITS_RESPONSE_CMD, Rx_MM_Pkg.m_frameNumber, RESPONSE_SUCCESS, payload);
			PkgHandle_p->SendPackage(Tx_MM_Pkg);
			break;
		}
		case CLEARBITS_CMD:
		{
			// process request
			vector <uint32_t> payload;
			uint32_t address = Rx_MM_Pkg.m_addressResponse;
			uint32_t numWordsToWrite = Rx_MM_Pkg.m_payload.size();

			for (uint32_t word = 0; word < numWordsToWrite; word++, address++)
			{
				RegisterInterface_p->ClearBits(address, Rx_MM_Pkg.m_payload.at(word));
			}

			// send response
			CMemoryMappedPackage Tx_MM_Pkg(CLEARBITS_RESPONSE_CMD, Rx_MM_Pkg.m_frameNumber, RESPONSE_SUCCESS, payload);
			PkgHandle_p->SendPackage(Tx_MM_Pkg);
			break;
		}
		default:
			CPrintPackage PrintPackage("Memory Mapped Package with unknown command received!");
			PkgHandle_p->SendPackage(PrintPackage);
			break;
		}
	}
	else if(error == CRC_ERROR)
	{
		CPrintPackage PrintPackage("A package arrived with wrong CRC!");
		PkgHandle_p->SendPackage(PrintPackage);
		uint32_t numWordsToRead = Rx_MM_Pkg.m_payload.size();
		std::cout << "invalid packet content " << numWordsToRead << std::endl;
		for (std::vector<PayloadUnit_t>::iterator it = Rx_MM_Pkg.m_payload.begin(); it != Rx_MM_Pkg.m_payload.end(); ++it)
					{
						std::cout << std::hex <<  *it << std::endl;
					}

		PkgHandle_p->DiscardData();
	}
	else if (error == INVALID_PACKAGE)
	{
		CPrintPackage PrintPackage("Invalid Package received!!");
		PkgHandle_p->SendPackage(PrintPackage);
		PkgHandle_p->DiscardData();
	}
}

int main()
{
	//prepare signal for receiving data
	struct sigaction saio;
	sigfillset(&saio.sa_mask);
	saio.sa_handler = ReceiveHandler;
	saio.sa_flags = 0;
	saio.sa_restorer = NULL;


	sigaction(SIGIO,&saio,NULL);

	CLinuxRegisterInterface RegisterInterface(0xFF250000, 0xE000);
	RegisterInterface_p = &RegisterInterface;
	CLinuxComPort myComPort;

	CPackageHandler * PkgHandle = new CPackageHandler(&myComPort, nullptr, nullptr, nullptr); // we never received async packages on MB

	PkgHandle_p = PkgHandle;

	std::string comPortIdentifier = "/dev/ttyS0";
	myComPort.OpenPort(comPortIdentifier,115200,
			ECharacter_size_t::eight,
			EParity_t::none,
			EStop_bits_t::one,
			EFlow_control_t::none,
			2000);


 	// create and run all the ps testers
 	std::vector<RunnableTest*> linuxTesters;

    LinuxIntelMgtTester test;
    test.Setup(RegisterInterface_p, 0xFF250000, 0xE000);
    linuxTesters.push_back(&test);

    //Run all linux testers
    for(std::vector<RunnableTest*>::iterator it = linuxTesters.begin(); it != linuxTesters.end(); ++it)
    {
        (*it)->Run();
    }

    CAsyncPackage AsyncPkg(EAsyncTypes_t::version, {28112016});
    PkgHandle->SendPackage(AsyncPkg);

    while(1)
    {
        if (PacketCounter != 0)
        {
            PacketCounter--;
            ProcessPacket();
        }
        usleep(1000);
    }

    return 0;
}
