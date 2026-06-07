#include "SerialPort.h"
#include "CommandProcessing.h"
#include "SettingsReader.h"
#include <iostream>

int main()
{
    bool app_running = true;

    serial_port port;

    while (app_running)
    {
        std::string input;
        std::cout << "\nEnter the command: ";
        std::getline(std::cin, input);

        // Check if input is a valid command
        if (const auto command = command_processing::get_command_type(input))
        {
            command_processing::process_commands(port, app_running, *command, input);
        }
        else 
        {
            std::cout << "\n\033[31mInvalid command.\033[0m\r\n";
        }
    }
    return 0;
}