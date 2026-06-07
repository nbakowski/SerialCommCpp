#pragma once

#include "SettingsReader.h"
#include <string>
#include <boost/asio.hpp>

class serial_port
{
	std::string port_name_ = "debug";
	int32_t baud_rate_ = 9600;
	int16_t repeat_amount_ = 10;
	boost::asio::io_context io_;
	boost::asio::serial_port serial_;
	settings_reader settings_reader_;
	void rebuild_port();

public:
	serial_port();

	void set_baud_rate(int new_baud_rate);
	void set_port_name(const std::string& new_port_name);
	void set_repeat_amount(int16_t repeat_count);

	void write_message(const std::string& message_to_send);
	void repeating_write_message(const std::string& message_to_send);
	void stop_and_close();
};

