#pragma once

#include "SerialPort.h"
#include <array>
#include <string>

namespace command_processing 
{
    // Always keep the COMMAND_COUNT at the bottom, otherwise problems.
    enum class command_type : uint8_t
    {
        WRITE_MESSAGE,
        CHANGE_PORT,
        CHANGE_BAUD_RATE,
        STOP,
        HELP,
        REPEAT_WRITE_MESSAGE,
        SET_REPEAT_AMOUNT,
        COMMAND_COUNT
    };

    constexpr int16_t command_count = static_cast<int16_t>(command_type::COMMAND_COUNT);

    static constexpr std::array<std::string_view, command_count> command_list = {
        "write message",
        "change port",
        "change baud rate",
        "exit",
        "help",
        "repeating write message",
        "set repeats"
    };

    std::optional<command_type> get_command_type(const std::string& value);
    void process_commands(serial_port& port, bool& is_running, command_type command, std::string& input);
}