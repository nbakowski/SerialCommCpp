#include "SettingsReader.h"
#include <iostream>
#include <fstream>

settings_reader::settings_reader() = default;

void settings_reader::update_settings_file(
    const std::string& port_name_string, 
    const int32_t baud_rate, 
    const int16_t repeat_amount
)
{
    data_ = {
        {"port_name", port_name_string}, 
        {"baud_rate", baud_rate},
        {"repeat_amount", repeat_amount}
    };
    std::ofstream new_file("settings.json");
    if (!new_file)
    {
        std::cerr << "Failed to write settings.json\r\n";
        return;
    }
    new_file << data_.dump(4);
}

settings_reader::settings_values settings_reader::get_settings()
{

    settings_values sv;

    std::cout << "Enter the port name: "; std::cin >> sv.return_port_name;
    std::cout << "Enter the baud rate: "; std::cin >> sv.return_baud_rate;
    std::cout << "Enter the repeat amount: "; std::cin >> sv.return_repeat_amount;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
    // Rebuild the file with new settings
    update_settings_file(sv.return_port_name, sv.return_baud_rate, sv.return_repeat_amount);
    return sv;
}

std::optional<settings_reader::settings_values> settings_reader::set_settings()
{
    if (std::ifstream settings_file("settings.json"); settings_file)
    {
        try
        {
            data_ = nlohmann::json::parse(settings_file);
        }
        catch (const nlohmann::json::parse_error&)
        {
            std::cerr << "Parsing error. Enter settings manually.\r\n";
            return get_settings();
        }
    }
    else
    {
        return get_settings();
    }

    // Set values from settings.json
    try
    {
        const std::string temp_port_name = data_.at("port_name");
        const int32_t temp_baud_rate     = data_.at("baud_rate");
        const int16_t temp_repeat_amount = data_.at("repeat_amount");

        settings_values sv;

    	sv.return_port_name     = temp_port_name;
        sv.return_baud_rate     = temp_baud_rate;
        sv.return_repeat_amount = temp_repeat_amount;

        std::cout << std::format(
            "Current settings: \r\n - Port name: {} \r\n - Baud rate: {} \r\n - Repeat amount: {}\r\n",
            sv.return_port_name,
            sv.return_baud_rate,
            sv.return_repeat_amount
        );
        return sv;
    }
    catch (nlohmann::json::out_of_range&)
    {
        std::cerr << "Settings file corrupted. Missing values. Enter settings manually.\r\n";
        return get_settings();
    }
}