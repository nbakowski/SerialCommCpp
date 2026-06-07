#include "CommandProcessing.h"
#include <iostream>
#include <optional>
#include <unordered_map>

namespace command_processing {
    using enum command_type;

    std::optional<command_type> get_command_type(const std::string& value)
    {
        static const std::unordered_map<std::string_view, command_type> command_map = {
            { "write message",           WRITE_MESSAGE    },
            { "change port",             CHANGE_PORT      },
            { "change baud rate",        CHANGE_BAUD_RATE },
            { "exit",                    STOP             },
            { "help",                    HELP             },
            { "repeating write message", REPEAT_WRITE_MESSAGE},
            { "set repeats",             SET_REPEAT_AMOUNT}
        };

        if (const auto it = command_map.find(value); it != command_map.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    void process_commands(serial_port& port, bool& is_running, const command_type command, std::string& input)
    {
        switch (command)
        {
            case WRITE_MESSAGE:
                std::cout << "Enter the message: ";
                std::getline(std::cin >> std::ws, input);
                port.write_message(input);
                break;

            case REPEAT_WRITE_MESSAGE:
                std::cout << "Enter the message: ";
                std::getline(std::cin >> std::ws, input);
                port.repeating_write_message(input);
                break;

            case CHANGE_PORT:
                std::cout << "Enter the new name: ";
                std::getline(std::cin >> std::ws, input);
                port.set_port_name(input);
                break;

            case CHANGE_BAUD_RATE: {
                std::string line;
                std::cout << "Enter the new baud rate: ";
                std::getline(std::cin >> std::ws, line);
                try {
                    const int32_t new_baud_rate = std::stoi(line);
                    port.set_baud_rate(new_baud_rate);
                }
                catch (const std::exception& ex) {
                    std::cerr << std::format("Invalid baud rate: {}\r\n", ex.what());
                }
                break;
            }

            case SET_REPEAT_AMOUNT: {
                std::string line;
                std::cout << "Enter a new repeat amount: ";
                std::getline(std::cin >> std::ws, line);
                try {
                    const auto amount = static_cast<int16_t>(std::stoi(line));
                    port.set_repeat_amount(amount);
                }
                catch (const std::exception& ex) {
                    std::cerr << std::format("Invalid repeat amount: {}\r\n", ex.what());
                }
                break;
            }

            case STOP:
                is_running = false;
                break;

            case HELP:
                std::cout << "\r\nAvailable commands: \r\n\n";
                for (const std::string_view& cmd : command_list)
                {
                    std::cout << cmd << "\r\n";
                }
                std::cout << "\r\n";
                break;

            case COMMAND_COUNT: break;
        }
    }
}