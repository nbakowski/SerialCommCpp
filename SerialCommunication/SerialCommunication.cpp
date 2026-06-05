#include "SerialPort.h"
#include "CommandProcessing.h"
#include "SettingsReader.h"
#include <iostream>

int main()
{
    bool app_running = true;

    SerialPort port;

    while (app_running)
    {
        std::string input;
        std::cout << "\nEnter the command: ";
        std::getline(std::cin, input);

        // Check if input is a valid command
        if (auto command = CommandProcessing::GetCommandType(input))
        {
            CommandProcessing::ProcessCommands(port, app_running, *command, input);
        }
        else 
        {
            std::cout << "\n\033[31mInvalid command.\033[0m\r\n";
        }
    }
    return 0;
}