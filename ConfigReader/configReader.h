#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>
#include <unordered_map>

enum class ConfigErrorCode
{
    NONE,
    FILE_NOT_FOUND,
    FILE_EMPTY,
    FILE_READ_ERROR,
    PARSE_ERROR
};

const char* getErrorMessage(ConfigErrorCode code);

class ConfigReader
{
    private:
    std::string fileName{};
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> configData;
    ConfigErrorCode lastError{};

    bool parseAndLoadFile();
    void logError(ConfigErrorCode code, const std::string &message = "");

    public:
    ConfigReader();
    explicit ConfigReader(const std::string &fileName);

    void print();

    ConfigErrorCode getLastError() const;

    // Template function to get and convert the key's value
    template <typename T>
    T getKey(const std::string &block, const std::string &key) const;
};

#endif // CONFIGREADER_H
