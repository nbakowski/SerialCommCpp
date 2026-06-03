#include "CommandProcessing.h"

namespace CommandProcessing {

    CommandType GetCommandType(const std::string& value)
    {
        const std::map<std::string, CommandType> CommandMap = {
            { "write",           WRITE           },
            { "change port",     CHANGE_NAME     },
            { "change baud rate",CHANGE_BAUD_RATE},
            { "exit",            STOP            },
            { "help",            HELP            }
        };

        const auto it = CommandMap.find(value);
        if (it != CommandMap.end())
        {
            return it->second;
        }

        throw std::invalid_argument("Unknown command: " + value);
    }

    void ProcessCommands(SerialPort& port, bool& is_running, const CommandType command, std::string& input)
    {
        switch (command)
        {
        case WRITE:
            std::cout << "Enter the message: \r\n"; std::getline(std::cin, input);
            port.WriteMessage(input);
            break;

        case CHANGE_NAME:
            std::cout << "Enter the new name: \r\n"; std::cin >> input;
            port.SetPortName(input);
            break;

        case CHANGE_BAUD_RATE: {
            int new_baud_rate = 0;
            std::cout << "Enter the new baud rate: \r\n"; std::cin >> new_baud_rate;
            port.SetBaudRate(new_baud_rate);
            break;
        }

        case STOP:
            is_running = false;
            break;

        case HELP:
            std::cout << "Available commands: \r\n";
            std::cout << "\r\n";
            for (const std::string& cmd : CommandList)
            {
                std::cout << cmd << "\r\n";
            }
            std::cout << "\r\n";
            break;
        }
    }
}