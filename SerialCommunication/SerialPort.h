#pragma once

#include "SettingsReader.h"
#include <string>
#include <asio.hpp>

class SerialPort
{
	std::string port_name = "debug";
	int32_t baud_rate = 9600;
	int16_t repeat_amount = 10;
	asio::io_context io{};
	asio::serial_port serial;
	SettingsReader settings_reader;
	void RebuildPort();

public:
	SerialPort();
	~SerialPort() noexcept;

	// Prevent dangling references from move/copy
	SerialPort(const SerialPort&) = delete;
	SerialPort& operator = (const SerialPort&) = delete;
	SerialPort(SerialPort&&) = delete;
	SerialPort& operator=(SerialPort&&) = delete;

	void SetBaudRate(int new_baud_rate);
	void SetPortName(const std::string& new_port_name);
	void SetRepeatAmount(int16_t repeat_count);

	void WriteMessage(const std::string& message_to_send);
	void RepeatingWriteMessage(const std::string& message_to_send);
	void StopAndClose();
};

