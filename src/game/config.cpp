#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "../logger.h"
#include "../platform.h"
#include "config.h"

std::vector<std::string> split_string_by_newline(const std::string& str);
static bool parse_point(const std::string& text, Point& outPoint);
static bool parse_config_ini(const std::string& iniText, Config& outConfig);

using namespace Gin;
using namespace Platform;

Config Config::load()
{
    Config defaultConfig;
    defaultConfig.windowDimensions = Point(360, 240);

    Config config;

    std::string iniText;
    if ( !Platform::read_file("config.ini", iniText) )
    {  
        Logger::log_warn(" open config file. Using default config.");
        return defaultConfig;
    }

    if ( !parse_config_ini(iniText, config) )
    {
        Logger::log_warn("Failed to parse config file. Using default config.");
        return defaultConfig;
    }

    return config;
}

// @TODO: Only checking for LFs. Check that this works on Windows. Does this need to be in the Platform?
std::vector<std::string> split_string_by_newline(const std::string& str)
{
    auto result = std::vector<std::string>{};
    auto ss = std::stringstream{str};

    for (std::string line; std::getline(ss, line, '\n');)
        result.push_back(line);

    return result;
}

static bool parse_point(const std::string& text, Point& outPoint)
{
    // Find the position of the 'x' char.
    size_t xIdx = text.find("x");
    if (xIdx == text.npos)
        return false;

    // Get the text before and after (but not including) the 'x' char.
    auto beforeX = text.substr(0, xIdx);
    auto afterX = text.substr(xIdx + 1);

    // Convert to x and y integers.
    int x = std::atoi(beforeX.c_str());
    int y = std::atoi(afterX.c_str());

    outPoint = Point(x, y);

    return true;
}

static bool parse_config_ini(const std::string& iniText, Config& outConfig)
{
    std::map<std::string, std::string> iniMap;
    
    // Iterate each line of the ini text. 
    for (const auto line : split_string_by_newline(iniText))
    {
        // Find the position of the '=' char.
        size_t equalsIdx = line.find('=');
        if (equalsIdx == line.npos)
            return false;

        // Get the text before and after (but not including) the '=' char.
        // Key and value are the text before and after the '=' char, respectively.
        std::string key = line.substr(0, equalsIdx);
        std::string value = line.substr(equalsIdx + 1);

        iniMap[key] = value;
    }

    // Parse window dimensions
    {
        auto text = iniMap["windowDimensions"].c_str();
        Point wndDims;
        if ( !parse_point(text, wndDims) )
            return false;

        outConfig.windowDimensions = wndDims;
    }

    return true;
}
