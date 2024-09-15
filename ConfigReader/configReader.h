#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>
#include <unordered_map>

/**
 * @enum ConfigErrorCode
 * @brief Enum representing possible error codes for configuration file operations.
 */
enum class ConfigErrorCode
{
    NONE,                ///< No error.
    FILE_NOT_FOUND,      ///< The configuration file was not found.
    FILE_EMPTY,          ///< The configuration file is empty.
    FILE_READ_ERROR,     ///< Error occurred while reading the configuration file.
    PARSE_ERROR,         ///< Error occurred while parsing the configuration file.
    KEY_NOT_FOUND,       ///< Error when key is not found
    BLOCK_NOT_FOUND      ///< Block Not Found
};

/**
 * @brief Returns a string representation of the error code.
 * @param code The error code to convert to a string.
 * @return A C-style string representing the error message.
 */
const char* getErrorMessage(ConfigErrorCode code);

/**
 * @class ConfigReader
 * @brief A class to handle reading and parsing a configuration file.
 *
 * The `ConfigReader` class reads a configuration file and provides methods to access
 * the configuration data. It supports error handling and logging for various issues
 * that might arise during file operations or parsing.
 */
class ConfigReader
{
private:
    std::string fileName;  ///< The name of the configuration file.
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> configData; ///< Parsed configuration data.
    ConfigErrorCode lastError;  ///< The last error encountered during operations.

    /**
     * @brief Logs an error with an optional message.
     * @param code The error code to log.
     * @param message An optional message to accompany the error code.
     */
    void logError(ConfigErrorCode code, const std::string &message = "");

public:

    /**
     * @brief Default constructor.
     */
    ConfigReader();

    /**
     * @brief Constructs a `ConfigReader` with the specified file name.
     * @param fileName The name of the configuration file to read.
     */
    explicit ConfigReader(const std::string &fileName);

    /**
     * @brief Prints the configuration data to the standard output.
     */
    void print();

    /**
     * @brief Parses and loads the configuration file.
     * @return True if the file was successfully parsed and loaded; otherwise, false.
     */
    bool parseAndLoadFile();

    /**
     * @brief Gets the last error code encountered.
     * @return The last error code.
     */
    ConfigErrorCode getLastError() const;

    /**
     * @brief Template function to retrieve and convert the value of a given key.
     * @tparam T The type to convert the key's value to.
     * @param block The block (section) of the configuration where the key is located.
     * @param key The key whose value is to be retrieved.
     * @return The value associated with the key, converted to type T.
     * @throw std::out_of_range If the key or block is not found.
     * @throw std::invalid_argument If the conversion to type T fails.
     */
    template <typename T>
    T getKey(const std::string &block, const std::string &key) ;

    /**
     * @brief Set fileName with the specified file name.
     * @param fileName The name of the configuration file to read.
     */
    void setFileName(const std::string &fileName);
};

#endif // CONFIGREADER_H
