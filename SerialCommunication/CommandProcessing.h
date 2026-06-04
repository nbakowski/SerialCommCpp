#pragma once

#include <array>
#include <map>
#include <string>

#include "SerialPort.h"

namespace CommandProcessing {

    // Always keep the COMMAND_COUNT at the bottom, otherwise problems.
    enum class CommandType {
        WRITE_MESSAGE,
        CHANGE_NAME,
        CHANGE_BAUD_RATE,
        STOP,
        HELP,
        REPEAT_WRITE_MESSAGE,
        SET_REPEAT_AMOUNT,
        COMMAND_COUNT
    };

    constexpr int16_t command_count = static_cast<int16_t>(CommandType::COMMAND_COUNT);

    const std::array<std::string, command_count> CommandList = {
        "write message",
        "change port",
        "change baud rate",
        "exit",
        "help",
        "repeating write message",
        "set repeats"
    };

    CommandType GetCommandType(const std::string& value);
    void ProcessCommands(SerialPort& port, bool& is_running, CommandType command, std::string& input);
}