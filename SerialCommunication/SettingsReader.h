#pragma once

#include <nlohmann/json.hpp>

class settings_reader
{
    nlohmann::json data_;
    struct settings_values
    {
        std::string return_port_name;
        int32_t return_baud_rate;
        int16_t return_repeat_amount;
    };

public:
    settings_reader();
    settings_values get_settings();
    std::optional<settings_values> set_settings();
    void update_settings_file(
        const std::string& port_name_string, 
        int32_t baud_rate,
        int16_t repeat_amount
    );
};