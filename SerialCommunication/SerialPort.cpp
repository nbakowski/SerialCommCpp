#include "SerialPort.h"

void SerialPort::RebuildPort()
{
	StopAndClose();
	try
	{
		if (port_name.empty())
		{
			std::cout << "Serial port name is empty." << "\r\n";
			return;
		}
		serial.open(port_name);
		serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Failed to rebuild serial port '" << port_name << "': " << ex.what() << "\r\n";
	}
}

SerialPort::SerialPort(const std::string& port_name, const uint32_t baud_rate)
	: port_name(port_name), baud_rate(baud_rate), serial(io)
{
	serial.open(port_name);
	serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
}

void SerialPort::SetBaudRate(const int new_baud_rate)
{
	baud_rate = new_baud_rate;
	RebuildPort();

}

void SerialPort::SetPortName(const std::string& new_port_name)
{
	port_name = new_port_name;
	RebuildPort();
}

void SerialPort::WriteMessage(const std::string& message_to_send)
{
	asio::write(serial, asio::buffer(message_to_send));
	std::cout << "Sent message: " << message_to_send << "\r\n";
}

void SerialPort::StopAndClose()
{
	if (serial.is_open()) { serial.close(); }
}
