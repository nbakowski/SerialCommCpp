#include "SerialPort.h"

SerialPort::SerialPort(const std::string& port_name, const int32_t baud_rate)
	: port_name(port_name), baud_rate(baud_rate), serial(io)
{
	serial.open(port_name);
	serial.set_option(asio::serial_port_base::baud_rate(baud_rate));
}

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

void SerialPort::SetBaudRate(const int new_baud_rate)
{
	if (new_baud_rate > 0)
	{
		baud_rate = new_baud_rate;
		std::cout << std::format("Set baud rate to: \033[31m{}\033[0m\r\n", baud_rate);
		RebuildPort();
	}
	else {
		std::cout << std::format("Failed to set baud rate to: \033[31m{}\033[0m\r\n", new_baud_rate);
	}

}

void SerialPort::SetPortName(const std::string& new_port_name)
{
	if (!new_port_name.empty())
	{
		port_name = new_port_name;
		std::cout << std::format("Set port name to: \033[31m{}\033[0m\r\n", port_name);
		RebuildPort();
	}
	else
	{
		std::cout << "Port name cannot be empty.\r\n";
	}
}

void SerialPort::SetRepeatAmount(int16_t repeat_count)
{
	repeat_amount = repeat_count;
	std::cout << std::format("Set repeat amount to: \033[31m{}\033[0m\r\n", repeat_amount);
}

void SerialPort::WriteMessage(const std::string& message_to_send)
{
	asio::write(serial, asio::buffer(message_to_send));
	std::cout << "Sent message: " << message_to_send << "\r\n";
}

void SerialPort::RepeatingWriteMessage(const std::string& message_to_send)
{
	for (short i = 0; i < repeat_amount; i++)
	{
		asio::write(serial, asio::buffer(message_to_send));
	}
	std::cout << std::format(
		"Sent message: {} {} times.\r\n", 
		message_to_send, 
		repeat_amount
	);
}

void SerialPort::StopAndClose()
{
	if (serial.is_open()) { serial.close(); }
}
