#include <fstream>
#include "Config.hpp"

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
                const std::string potentialconfigValue = readLine.substr(positionOfDelimeter + 1);

		const size_t positionOfComment = poentialConfigValue.find("//");

		if ( positionOfComment != std::string::npos )
		{
			potentialConfigValue = potentialConfigValue.substr( 0, positionOfComment );
		}

		potentialConfigValue.erase(
			std::remove (potentialConfigValue.begin(), potentialConfigValue.end(), ' '),
			potentialConfigValue.end());
                m_config.insert(std::make_pair(configName, configValue));
            }
        }
    }
}
