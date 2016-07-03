#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <map>
#include <boost/lexical_cast.hpp>

#define LoadConfig(path) Config::CreateInstance().LoadConfigFile(path)
#define GetConfig(type, config) Config::CreateInstance().GetConfiguration<type>(config)

class Config
{
public:
    static Config& CreateInstance();
    void LoadConfigFile(const std::string& configFilePath);

    Config(const Config&) = delete;
    Config(const Config&&) = delete;
    Config& operator=(const Config&) = delete;

    template<typename T>
    T GetConfiguration(const std::string& config) const
    {
        return boost::lexical_cast<T>(m_config.at(config));
    }

private:
    Config() = default;

    std::map <std::string, std::string> m_config;
};
#endif
