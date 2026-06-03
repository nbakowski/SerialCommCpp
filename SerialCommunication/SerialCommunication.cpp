#include <iostream>
#include <map>
#include <windows.h>

#include "SerialPort.h"
#include "CommandProcessing.h"

int main()
{
    std::string port_name;
    int baud_rate = 0;
    bool app_running = true;

    std::cout << "Enter the port name: "; std::cin >> port_name; std::cout << std::endl;
    std::cout << "Enter the baud rate: "; std::cin >> baud_rate; std::cout << std::endl;

    SerialPort port(port_name, baud_rate);

    while (app_running)
    {
        std::string input;
        std::cout << "Enter the command: \r\n";
        std::getline(std::cin, input);

        // Check if input is a valid command
        if (count(CommandProcessing::CommandList.begin(), CommandProcessing::CommandList.end(), input) > 0)
        {
            const CommandProcessing::CommandType command = CommandProcessing::GetCommandType(input);
            ProcessCommands(port, app_running, command, input);
        }
    }

    port.StopAndClose();

    return 0;
}