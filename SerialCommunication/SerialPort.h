#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <asio.hpp>

class SerialPort
{
	std::string port_name;
	uint32_t baud_rate;
	asio::io_service io{};
	asio::serial_port serial;
	void RebuildPort();

public:
	SerialPort(const std::string& port_name, uint32_t baud_rate);

	const std::string& GetCurrentPortName() const
	{
		return port_name;
	}

	uint32_t GetCurrentBaudRate() const
	{
		return baud_rate;
	}

	void SetBaudRate(int new_baud_rate);
	void SetPortName(const std::string& new_port_name);

	void WriteMessage(const std::string& message_to_send);
	void StopAndClose();
};

