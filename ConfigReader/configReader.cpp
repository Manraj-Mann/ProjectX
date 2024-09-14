#include "ConfigReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Error messages
const char* getErrorMessage(ConfigErrorCode code)
{
    switch (code)
    {
        case ConfigErrorCode::NONE:
            return "No error";
        case ConfigErrorCode::FILE_NOT_FOUND:
            return "Configuration file not found";
        case ConfigErrorCode::FILE_EMPTY:
            return "Configuration file is empty";
        case ConfigErrorCode::FILE_READ_ERROR:
            return "Error reading configuration file";
        case ConfigErrorCode::PARSE_ERROR:
            return "Error parsing configuration file";
        default:
            return "Unknown error";
    }
}

ConfigReader::ConfigReader() : lastError(ConfigErrorCode::NONE) {}

ConfigReader::ConfigReader(const std::string &fileName) : fileName(fileName), lastError(ConfigErrorCode::NONE)
{
    if (!parseAndLoadFile())
    {
        logError(lastError);
    }
}

void ConfigReader::logError(ConfigErrorCode code, const std::string &message)
{
    std::cerr << "Error: " << getErrorMessage(code);
    if (!message.empty())
    {
        std::cerr << ": " << message;
    }
    std::cerr << std::endl;
}

bool ConfigReader::parseAndLoadFile()
{
    if (!fileName.size())
    {
        std::cout<<"Return\n";
        lastError = ConfigErrorCode::FILE_EMPTY;
        return false;
    }
    
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        lastError = ConfigErrorCode::FILE_NOT_FOUND;
        return false;
    }

    std::string line;
    std::string currentBlock;

    while (std::getline(file, line))
    {
        // Remove leading and trailing whitespace
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        line.erase(line.find_last_not_of(" \t\n\r") + 1);

        if (line.empty())
            continue;

        // Check for block headers
        if (line.front() == '[' && line.back() == ']')
        {
            currentBlock = line.substr(1, line.size() - 2); // Extract block name
        }
        else if (line.front() == '#')
        {
            continue; // Ignore comments
        }
        else 
        {
            // Process parameters within a block
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos)
            {
                std::string paramName = line.substr(0, delimiterPos);
                std::string paramValue = line.substr(delimiterPos + 1);

                // Remove leading and trailing whitespace from parameter name and value
                paramName.erase(0, paramName.find_first_not_of(" \t\n\r"));
                paramName.erase(paramName.find_last_not_of(" \t\n\r") + 1);
                paramValue.erase(0, paramValue.find_first_not_of(" \t\n\r"));
                paramValue.erase(paramValue.find_last_not_of(" \t\n\r") + 1);

                if (!currentBlock.empty())
                {
                    configData[currentBlock][paramName] = paramValue;
                }
            }
            else
            {
                lastError = ConfigErrorCode::PARSE_ERROR;
                return false;
            }
        }
    }

    file.close();
    return true;
}

void ConfigReader::print()
{
    std::cout << "********************* CONFIGURATIONS *****************************" << std::endl;
    std::cout << "File name : " << fileName << std::endl;

    for (const auto &block : configData)
    {
        std::cout << "[" << block.first << "]" << std::endl;
        for (const auto &param : block.second)
        {
            std::cout << param.first << "=" << param.second << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "*****************************************************************" << std::endl;
}

ConfigErrorCode ConfigReader::getLastError() const
{
    return lastError;
}

template <typename T>
T ConfigReader::getKey(const std::string &block, const std::string &key) const
{
    // Check if the block and key exist
    auto blockIt = configData.find(block);
    if (blockIt == configData.end())
    {
        throw std::runtime_error("Block not found");
    }
    
    auto keyIt = blockIt->second.find(key);
    if (keyIt == blockIt->second.end())
    {
        throw std::runtime_error("Key not found");
    }

    std::string value = keyIt->second;

    // Perform the conversion based on the type
    std::istringstream iss(value);
    T result;

    if constexpr (std::is_same_v<T, int>)
    {
        if (!(iss >> result))
        {
            throw std::runtime_error("Conversion to int failed");
        }
    }
    else if constexpr (std::is_same_v<T, float>)
    {
        if (!(iss >> result))
        {
            throw std::runtime_error("Conversion to float failed");
        }
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        if (!(iss >> result))
        {
            throw std::runtime_error("Conversion to double failed");
        }
    }
    else if constexpr (std::is_same_v<T, bool>)
    {
        std::string lowerValue = value;
        std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), ::tolower);
        if (lowerValue == "true" || lowerValue == "1")
        {
            result = true;
        }
        else if (lowerValue == "false" || lowerValue == "0")
        {
            result = false;
        }
        else
        {
            throw std::runtime_error("Conversion to bool failed");
        }
    }
    else
    {
        static_assert(std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, double> || std::is_same_v<T, bool>,
                      "Unsupported type for conversion");
    }

    return result;
}

// Explicit instantiation
template int ConfigReader::getKey<int>(const std::string &, const std::string &) const;
template float ConfigReader::getKey<float>(const std::string &, const std::string &) const;
template double ConfigReader::getKey<double>(const std::string &, const std::string &) const;
template bool ConfigReader::getKey<bool>(const std::string &, const std::string &) const;
template bool ConfigReader::getKey<std::string>(const std::string &, const std::string &) const;