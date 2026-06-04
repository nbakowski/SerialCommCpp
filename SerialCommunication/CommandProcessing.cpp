#include "CommandProcessing.h"
#include <iostream>
#include <map>

namespace CommandProcessing {
    using enum CommandType;

    std::optional<CommandType> GetCommandType(const std::string& value)
    {
        static const std::unordered_map<std::string_view, CommandType> CommandMap = {
            { "write message",           WRITE_MESSAGE    },
            { "change port",             CHANGE_PORT      },
            { "change baud rate",        CHANGE_BAUD_RATE },
            { "exit",                    STOP             },
            { "help",                    HELP             },
            { "repeating write message", REPEAT_WRITE_MESSAGE},
            { "set repeats",             SET_REPEAT_AMOUNT}
        };

        if (const auto it = CommandMap.find(value); it != CommandMap.end()) {
            return it->second;
        }
        return std::nullopt;
    }

    void ProcessCommands(SerialPort& port, bool& is_running, const CommandType command, std::string& input)
    {
        switch (command)
        {
            case WRITE_MESSAGE:
                std::cout << "Enter the message: ";
                std::getline(std::cin >> std::ws, input);
                port.WriteMessage(input);
                break;

            case REPEAT_WRITE_MESSAGE:
                std::cout << "Enter the message: ";
                std::getline(std::cin >> std::ws, input);
                port.RepeatingWriteMessage(input);
                break;

            case CHANGE_PORT:
                std::cout << "Enter the new name: ";
                std::getline(std::cin >> std::ws, input);
                port.SetPortName(input);
                break;

            case CHANGE_BAUD_RATE: {
                std::string line;
                std::cout << "Enter the new baud rate: ";
                std::getline(std::cin >> std::ws, line);
                try {
                    const int32_t new_baud_rate = std::stoi(line);
                    port.SetBaudRate(new_baud_rate);
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
                    port.SetRepeatAmount(amount);
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
                for (const std::string& cmd : CommandList)
                {
                    std::cout << cmd << "\r\n";
                }
                std::cout << "\r\n";
                break;

            default: break;
        }
    }
}