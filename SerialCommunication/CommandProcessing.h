#pragma once

#include <vector>
#include <map>
#include <string>

#include "SerialPort.h"

namespace CommandProcessing {
    const std::vector<std::string> CommandList = {
    "write message",
    "change port",
    "change baud rate",
    "exit",
    "help",
    "repeating write message",
    "set repeats"
};

    enum CommandType {
        WRITE_MESSAGE,
        CHANGE_NAME,
        CHANGE_BAUD_RATE,
        STOP,
        HELP,
        REPEAT_WRITE_MESSAGE,
        SET_REPEAT_AMOUNT
    };

    CommandType GetCommandType(const std::string& value);
    void ProcessCommands(SerialPort& port, bool& is_running, CommandType command, std::string& input);
}