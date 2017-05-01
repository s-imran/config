#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>
#include <fstream>
#include <assert.h>
#include <type_traits>
#include <algorithm>

#define LoadConfig(path) Config::CreateInstance().LoadConfigFile(path)
#define GetConfig(type, config) Config::CreateInstance().GetConfiguration<type>(config)

class Config
{
public:
    static Config& CreateInstance()
    {
        static Config i;
        return i;
    }

    void LoadConfigFile(const std::string& configFilePath)
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
                    std::string potentialConfigValue = readLine.substr(positionOfDelimeter + 1);
                    const size_t positionOfComment = potentialConfigValue.find("//");
                    if ( positionOfComment != std::string::npos )
                    {
                        potentialConfigValue = potentialConfigValue.substr( 0, positionOfComment );
                    }
                    potentialConfigValue.erase(std::remove(potentialConfigValue.begin(), potentialConfigValue.end(), ' '),
                                               potentialConfigValue.end());
                    m_config.insert(std::make_pair(configName, potentialConfigValue));
                }
            }
        }
    }

    Config(const Config&) = delete;
    Config(const Config&&) = delete;
    Config& operator=(const Config&) = delete;
    Config&& operator=(const Config&&) = delete;

    template<typename T>
    T GetConfiguration(const std::string&) const
    {
        static_assert(AlwaysFalse<T>::value, "Use template specialisation");
        return T();
    }

private:
    Config() = default;

    template <typename T>
    struct AlwaysFalse : std::false_type
    {
    };

    std::map<std::string, std::string> m_config;
};

template<>
float Config::GetConfiguration<float>(const std::string& config) const
{
    return std::stof(m_config.at(config));
}

template<>
int Config::GetConfiguration<int>(const std::string& config) const
{
    return std::stoi(m_config.at(config));
}

template<>
double Config::GetConfiguration<double>(const std::string& config) const
{
    return std::stod(m_config.at(config));
}

template<>
std::string Config::GetConfiguration<std::string>(const std::string& config) const
{
    return m_config.at(config);
}

template<>
bool Config::GetConfiguration<bool>(const std::string& config) const
{
    return m_config.at(config) == "true" ? true : false;
}

#endif
