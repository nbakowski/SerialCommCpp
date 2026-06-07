#include "SerialPort.h"
#include <iostream>

serial_port::serial_port() : serial_(io_)
{
	if (const auto sv = settings_reader_.set_settings())
	{
		port_name_ = sv->return_port_name;
		baud_rate_ = sv->return_baud_rate;
		repeat_amount_ = sv->return_repeat_amount;
	}

	try
	{
		serial_.open(port_name_);
		serial_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));
	}
	catch (const std::exception&)
	{
		std::cerr << std::format(
			"Failed to open the port: \033[31m{}\033[0m. Make sure the settings are correct.\r\n", 
			port_name_
		);
	}
}

void serial_port::rebuild_port()
{
	stop_and_close();

	try
	{
		if (port_name_.empty())
		{
			std::cout << "Serial port name is empty." << "\r\n";
			return;
		}
		serial_.open(port_name_);
		serial_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate_));
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Failed to rebuild serial port '" << port_name_ << "': " << ex.what() << "\r\n";
	}
	settings_reader_.update_settings_file(port_name_, baud_rate_, repeat_amount_);
}

void serial_port::set_baud_rate(const int new_baud_rate)
{
	if (new_baud_rate > 0)
	{
		baud_rate_ = new_baud_rate;
		std::cout << std::format("Set baud rate to: \033[31m{}\033[0m\r\n", baud_rate_);
		rebuild_port();
	}
	else {
		std::cout << std::format("Failed to set baud rate to: \033[31m{}\033[0m\r\n", new_baud_rate);
	}

}

void serial_port::set_port_name(const std::string& new_port_name)
{
	if (!new_port_name.empty())
	{
		port_name_ = new_port_name;
		std::cout << std::format("Set port name to: \033[31m{}\033[0m\r\n", port_name_);
		rebuild_port();
	}
	else
	{
		std::cout << "Port name cannot be empty.\r\n";
	}
}

void serial_port::set_repeat_amount(const int16_t repeat_count)
{
	repeat_amount_ = repeat_count;
	std::cout << std::format("Set repeat amount to: \033[31m{}\033[0m\r\n", repeat_amount_);
}

void serial_port::write_message(const std::string& message_to_send)
{
	try
	{
		boost::asio::write(serial_, boost::asio::buffer(message_to_send));
		std::cout << "Sent message: " << message_to_send << "\r\n";
	}
	catch (const std::exception& ex) 
	{
		std::cerr << "Write failed: " << ex.what() << "\r\n";
	}
}

void serial_port::repeating_write_message(const std::string& message_to_send)
{
	try
	{
		for (short i = 0; i < repeat_amount_; i++)
		{
			boost::asio::write(serial_, boost::asio::buffer(message_to_send));
		}
		std::cout << std::format(
			"Sent message: {} {} times.\r\n",
			message_to_send,
			repeat_amount_
		);
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Write failed: " << ex.what() << "\r\n";
	}
}

void serial_port::stop_and_close()
{
	if (serial_.is_open()) { serial_.close(); }
}
