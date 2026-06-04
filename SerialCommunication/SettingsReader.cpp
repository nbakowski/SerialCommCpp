#include "SettingsReader.h"
#include <iostream>

SettingsReader::SettingsReader(std::string& port_name, int32_t& baud_rate, int16_t& repeat_amount)
    : port_name(port_name), baud_rate(baud_rate), repeat_amount(repeat_amount) {}

void SettingsReader::UpdateSettingsFile()
{
    data = {
        {"port_name", port_name}, 
        {"baud_rate", baud_rate},
        {"repeat_amount", repeat_amount}
    };
    std::ofstream new_file("settings.json");
    if (!new_file)
    {
        std::cerr << "Failed to write settings.json\r\n";
        return;
    }
    new_file << data.dump(4);
}

void SettingsReader::GetSettings() {
    std::cout << "Enter the port name: "; std::cin >> port_name;
    std::cout << "Enter the baud rate: "; std::cin >> baud_rate;
    std::cout << "Enter the repeat amount: "; std::cin >> repeat_amount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    // Rebuild the file with new settings
    UpdateSettingsFile();
}

void SettingsReader::SetSettings()
{
    if (std::ifstream settings_file("settings.json"); settings_file)
    {
        try
        {
            data = nlohmann::json::parse(settings_file);
        }
        catch (const nlohmann::json::parse_error&)
        {
            std::cerr << "Parsing error. Enter settings manually.\r\n";
            GetSettings();
            return;
        }
    }
    else
    {
        GetSettings();
        return;
    }

    // Set values from settings.json
    try
    {
        const std::string temp_port_name     = data.at("port_name");
        const int32_t temp_baud_rate     = data.at("baud_rate");
        const int16_t temp_repeat_amount = data.at("repeat_amount");

        port_name     = temp_port_name;
        baud_rate     = temp_baud_rate;
        repeat_amount = temp_repeat_amount;
    }
    catch (nlohmann::json::out_of_range&)
    {
        std::cerr << "Settings file corrupted. Missing values. Enter settings manually.\r\n";
        GetSettings();
    }
}