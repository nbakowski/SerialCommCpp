#include <iostream>
#include <map>

#include "SerialPort.h"
#include "CommandProcessing.h"

int main()
{
    std::string port_name;
    int32_t baud_rate = 0;
    bool app_running = true;

    std::cout << "Enter the port name: "; std::cin >> port_name;
    std::cout << "Enter the baud rate: "; std::cin >> baud_rate;

    SerialPort port(port_name, baud_rate);

    while (app_running)
    {
        std::string input;
        std::cout << "\nEnter the command: ";
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