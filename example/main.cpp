#include <iostream>

#include "Config.hpp"

int main()
{
    std::string testFilePath("test_config");
    LoadConfig(testFilePath);

    std::cout << std::is_same<int, decltype(GetConfig(int, "int"))>::value << std::endl;
    std::cout << std::is_same<float, decltype(GetConfig(float, "float"))>::value << std::endl;
    std::cout << std::is_same<bool, decltype(GetConfig(bool, "bool"))>::value << std::endl;
    std::cout << std::is_same<float, decltype(GetConfig(int, "int"))>::value << std::endl;

    return 1;
}
