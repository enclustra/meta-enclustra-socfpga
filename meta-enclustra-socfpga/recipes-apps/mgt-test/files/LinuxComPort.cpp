/** \file LinuxComPort.cpp
* Implementation file for the LinuxomPort class
* \author Matthias Frei
* \date 06.12.2017
*
* This is a wrapper class of boost serial port interface.
* Copyright (c) 2017 Enclustra GmbH, Switzerland.
* All rights reserved.
*/

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------

#include "LinuxComPort.h"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>


//-------------------------------------------------------------------------------------------------
// Directives, typedefs and constants
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Construction/destruction
//-------------------------------------------------------------------------------------------------

CLinuxComPort::CLinuxComPort()	:
	m_isOpen(false)
{

}

CLinuxComPort::~CLinuxComPort()
{

}

void CLinuxComPort::OpenPort(const std::string& port,
	const uint32_t baud_rate,
	const ECharacter_size_t char_size,
	const EParity_t parity,
	const EStop_bits_t stopBits,
	const EFlow_control_t flowControl,
	const uint32_t timeoutInMiliSec)
{

	struct termios SerialPortSettings;
	// All parameters are fixed on a per instance basis, so there are not configurable by sw
	m_fileDesc = open(port.c_str(), O_RDWR | O_NOCTTY);

	if (m_fileDesc >= 0){
		std::cout << "ComPort open" << std::endl;

        fcntl(m_fileDesc, F_SETFL, FNDELAY|FASYNC);
        fcntl(m_fileDesc, F_SETOWN, getpid());

		tcgetattr(m_fileDesc, &SerialPortSettings);

		// set speed for RX and TX
		cfsetispeed(&SerialPortSettings,baud_rate );
		cfsetospeed(&SerialPortSettings,baud_rate);


		SerialPortSettings.c_cflag &= ~CSIZE; /* Clears the Mask       */
		switch (char_size)
		{
		case ECharacter_size_t::eight:
			SerialPortSettings.c_cflag |=  CS8; break;
		case ECharacter_size_t::seven:
			SerialPortSettings.c_cflag |=  CS7;  break;
		}


		switch (parity)
		{
		case EParity_t::even:
			SerialPortSettings.c_cflag |=  PARENB; // enable parity
			SerialPortSettings.c_cflag &=  ~PARODD; // odd bit not set = even parity
			break;
		case EParity_t::none:
			SerialPortSettings.c_cflag &= ~PARENB;  break; // No Parity
		case EParity_t::odd:
			SerialPortSettings.c_cflag |=  PARENB; // enable parity
			SerialPortSettings.c_cflag |=  PARODD; // use odd parity
			break;
		}

		switch (stopBits)
		{
		case EStop_bits_t::one:
			SerialPortSettings.c_cflag &= ~CSTOPB; break; // not set = 1 stop bit
		case EStop_bits_t::onepointfive:
			std::cout << "ERROR 1,5 stop bit is not supported" << std::endl; break;
		case EStop_bits_t::two:
			SerialPortSettings.c_cflag |=  CSTOPB; break; // set = 2 stop bit
		}

		switch (flowControl)
		{
		case EFlow_control_t::none:
			SerialPortSettings.c_cflag &= ~CRTSCTS;//HW
			SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);//SW
			break;
		case EFlow_control_t::hardware:
			SerialPortSettings.c_cflag |=  CRTSCTS;
			SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
			break;
		case EFlow_control_t::software:
			SerialPortSettings.c_iflag |= (IXON | IXOFF | IXANY);
			break;
		}

		SerialPortSettings.c_iflag &= ~(INLCR | IGNCR | ICRNL | IGNBRK | BRKINT | IUTF8 | IUCLC | PARMRK | ISTRIP); // CR translation on input data disabled

		SerialPortSettings.c_oflag  &= ~(OCRNL | ONOCR | ONLCR | ONLRET | OPOST | OLCUC); // CR translation on output data disabled

		SerialPortSettings.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG | IEXTEN | NOFLSH); // disable cannonical mode
		SerialPortSettings.c_lflag &= ~(ECHOK | ECHOCTL | ECHOKE ); // disable further echo flags, was necessary on Arria 10
		// in linux type "man termios" for further information

		// turn on receiving
		SerialPortSettings.c_cflag |= CREAD | CLOCAL;
		SerialPortSettings.c_cc[VMIN]  = 1; /* Read 10 characters */
		SerialPortSettings.c_cc[VTIME] = 0;  /* Wait indefinitely   */


		// apply settings
		tcsetattr(m_fileDesc,TCSANOW,&SerialPortSettings);


		m_isOpen = true;	//TODO: there is no specific API for this one, using a variable to mimic
	}else{
		std::cout << "ComPort could not be opened " << m_fileDesc << std::endl;
	}


	// timeoutInMiliSec // TODO: timeoutInMiliSec is ignored for now
}

void CLinuxComPort::ClosePort()
{
	m_isOpen = false; 	//TODO: there is no specific API for this one, using a variable to mimic
	close(m_fileDesc);
}

void CLinuxComPort::SendData(const vector <uint8_t>& data)
{
	write(m_fileDesc, &data[0],data.size());
	//write(m_fileDesc, "\n",1);

}

bool CLinuxComPort::CheckDataIsAvailable()
{
;
}

uint32_t CLinuxComPort::ReceiveData(vector <uint8_t> &data, const uint32_t size)
{
	size_t ReceivedByteCounter = 0;
	size_t currentReceivedByteCounter = 0;

	data.clear();
	data.resize(size);


	/*while(ReceivedByteCounter < size){
		currentReceivedByteCounter = 0;
		currentReceivedByteCounter = read(m_fileDesc,&data[ReceivedByteCounter],(size-ReceivedByteCounter));
		if (currentReceivedByteCounter!=-1){
			ReceivedByteCounter += currentReceivedByteCounter;
		}else{
			std::cout << "error occured on comport" << std::endl;
		}
	}*/

	ReceivedByteCounter = read(m_fileDesc,&data[0],((size_t)size));


	return ReceivedByteCounter;
}

bool CLinuxComPort::IsOpen()
{
	return m_isOpen; 	//TODO: there is no specific API for this one, using a variable to mimic
}

void CLinuxComPort::DiscardData()
{
	tcflush( m_fileDesc, TCIFLUSH );
}

void CLinuxComPort::SetBootActive(bool active) {

}

string CLinuxComPort::GetBootlog(){
	return "";
}

