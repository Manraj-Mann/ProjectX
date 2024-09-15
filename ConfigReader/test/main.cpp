#include "../configReader.h"
#include <iostream>
#include <cassert>

int main()
{
    // Test the default constructor
    ConfigReader reader1;
    assert(reader1.getLastError() == ConfigErrorCode::NONE); // Ensure no error occurred with default construction

    // Test setting file name and loading file
    reader1.setFileName("file.config");
    bool loaded = reader1.parseAndLoadFile();
    assert(loaded && reader1.getLastError() == ConfigErrorCode::NONE); // Ensure file is loaded without errors

    // Print the configuration to verify content
    reader1.print();

    // Test the constructor with a file
    ConfigReader reader2("file.config");
    if (reader2.getLastError() == ConfigErrorCode::FILE_NOT_FOUND) {
        std::cerr << "Error: Configuration file 'file.config' not found.\n";
        return 1;
    } else if (reader2.getLastError() == ConfigErrorCode::FILE_EMPTY) {
        std::cerr << "Error: Configuration file 'file.config' is empty.\n";
        return 1;
    } else if (reader2.getLastError() == ConfigErrorCode::FILE_READ_ERROR) {
        std::cerr << "Error: Could not read configuration file 'file.config'.\n";
        return 1;
    } else if (reader2.getLastError() == ConfigErrorCode::PARSE_ERROR) {
        std::cerr << "Error: Parsing error occurred with configuration file 'file.config'.\n";
        return 1;
    } else {
        std::cout << "Configuration file 'file.config' loaded successfully.\n";
    }

    // Runtime assertions to check specific key values
    try {
        reader2.getKey<bool>("General", "main");
        assert(reader2.getLastError() == ConfigErrorCode::KEY_NOT_FOUND);

        reader2.getKey<bool>("Block-6", "main2");
        assert(reader2.getLastError() == ConfigErrorCode::BLOCK_NOT_FOUND);
        
        assert(reader2.getKey<std::string>("General" , "version") == "1.0.0");
        assert(reader2.getKey<double>("General" , "timeout") == 30.5);
        assert(reader2.getKey<float>("General" , "timeout") == 30.5);

        assert(reader2.getKey<bool>("Server" , "useSSL") == true);

        assert(reader2.getKey<int>("Logging" , "maxFileSize") == 10485760);

        std::cout<<"FI : "<<reader2.getKey<int>("Logging" , "maxFileSize")<<std::endl;

        std::cout << "All key values are as expected.\n";

    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Key not found. " << e.what() << '\n';
        return 1;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: Invalid argument. " << e.what() << '\n';
        return 1;
    }

    return 0;
}
