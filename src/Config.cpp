#include <fstream>
#include "Config.hpp"
#include "Log.hpp"

Config& Config::CreateInstance()
{
    static Config i;
    return i;
}

void Config::LoadConfigFile(const std::string& configFilePath)
{
    std::ifstream file(configFilePath);
    while (file.is_open() and !file.eof())
    {
        std::string readLine;
        std::getline(file, readLine);
        if (!readLine.empty())
        {
            const size_t positionOfDelimeter = readLine.find(":");
            if (positionOfDelimeter != std::string::npos)
            {
                const std::string& configName = readLine.substr(0, positionOfDelimeter);
                const std::string& configValue = readLine.substr(positionOfDelimeter + 1);
                m_config.insert(std::make_pair(configName, configValue));
            }
        }
    }
}
