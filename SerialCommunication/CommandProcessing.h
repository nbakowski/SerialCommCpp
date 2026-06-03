#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "SerialPort.h"

namespace CommandProcessing {const std::vector<std::string> CommandList = { "write", "change port", "change baud rate", "exit", "help" };

    enum CommandType {
        WRITE,
        CHANGE_NAME,
        CHANGE_BAUD_RATE,
        STOP,
        HELP
    };

    CommandType GetCommandType(const std::string& value);
    void ProcessCommands(SerialPort& port, bool& is_running, CommandType command, std::string& input);
}