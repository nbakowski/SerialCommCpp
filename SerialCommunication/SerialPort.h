#pragma once

#include <string>
#include <iostream>
#include <asio.hpp>

class SerialPort
{
	std::string port_name;
	int32_t baud_rate;
	asio::io_context io{};
	asio::serial_port serial;
	int16_t repeat_amount = 10;
	void RebuildPort();

public:
	SerialPort(const std::string& port_name, int32_t baud_rate);
	~SerialPort() noexcept;

	const std::string& GetCurrentPortName() const
	{
		return port_name;
	}

	int32_t GetCurrentBaudRate() const
	{
		return baud_rate;
	}

	void SetBaudRate(int new_baud_rate);
	void SetPortName(const std::string& new_port_name);
	void SetRepeatAmount(int16_t repeat_count);

	void WriteMessage(const std::string& message_to_send);
	void RepeatingWriteMessage(const std::string& message_to_send);
	void StopAndClose();
};

