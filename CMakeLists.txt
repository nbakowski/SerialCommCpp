cmake_minimum_required(VERSION 4.2)
project(SerialCommCpp)

set(CMAKE_CXX_STANDARD 20)

include_directories(
        SerialCommunication
        /opt/homebrew/opt/boost/include
        /opt/homebrew/opt/nlohmann-json/include
)

add_executable(SerialCommCpp
        SerialCommunication/CommandProcessing.cpp
        SerialCommunication/CommandProcessing.h
        SerialCommunication/SerialCommunication.cpp
        SerialCommunication/SerialPort.cpp
        SerialCommunication/SerialPort.h
        SerialCommunication/SettingsReader.cpp)
