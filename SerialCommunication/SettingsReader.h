#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class SettingsReader
{
    nlohmann::json data;
    std::string& port_name;
    int32_t& baud_rate;
    int16_t& repeat_amount;

public:
    SettingsReader(std::string& port_name, int32_t& baud_rate, int16_t& repeat_amount);
    void GetSettings();
    void SetSettings();
    void UpdateSettingsFile();
};