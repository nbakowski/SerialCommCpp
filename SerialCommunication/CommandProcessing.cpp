#include "CommandProcessing.h"

namespace CommandProcessing {

    using enum CommandType;

    CommandType GetCommandType(const std::string& value)
    {
        const std::map<std::string, CommandType> CommandMap = {
            { "write message",           WRITE_MESSAGE    },
            { "change port",             CHANGE_NAME      },
            { "change baud rate",        CHANGE_BAUD_RATE },
            { "exit",                    STOP             },
            { "help",                    HELP             },
            { "repeating write message", REPEAT_WRITE_MESSAGE},
            { "set repeats",             SET_REPEAT_AMOUNT}
        };

        if (const auto it = CommandMap.find(value); it != CommandMap.end())
        {
            return it->second;
        }

        throw std::invalid_argument("Unknown command: " + value);
    }

    void ProcessCommands(SerialPort& port, bool& is_running, const CommandType command, std::string& input)
    {
        switch (command)
        {
        case WRITE_MESSAGE:
            std::cout << "Enter the message: "; std::getline(std::cin, input);
            port.WriteMessage(input);
            break;

        case REPEAT_WRITE_MESSAGE:
            std::cout << "Enter the message: "; std::getline(std::cin, input);
            port.RepeatingWriteMessage(input);
            break;

        case CHANGE_NAME:
            std::cout << "Enter the new name: "; std::cin >> input;
            port.SetPortName(input);
            break;

        case CHANGE_BAUD_RATE: {
            int32_t new_baud_rate = 0;
            std::cout << "Enter the new baud rate: "; std::cin >> new_baud_rate;
            port.SetBaudRate(new_baud_rate);
            break;
        }

        case SET_REPEAT_AMOUNT: {
            int16_t amount = 0;
            std::cout << "Enter a new repeat amount: "; std::cin >> amount;
            port.SetRepeatAmount(amount);
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
        }
    }
}