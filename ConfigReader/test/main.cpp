#include "../configReader.h"
#include <iostream>

int main()
{
    ConfigReader reader1;
    ConfigReader reader2("file.config");
    ConfigReader reader3("../file.config");

    reader1.print();
    if (reader1.getLastError() != ConfigErrorCode::NONE)
    {
        std::cerr << "Reader1 encountered an error: " << getErrorMessage(reader1.getLastError()) << std::endl;
    }

    reader2.print();
    if (reader2.getLastError() != ConfigErrorCode::NONE)
    {
        std::cerr << "Reader2 encountered an error: " << getErrorMessage(reader2.getLastError()) << std::endl;
    }

    reader3.print();
    if (reader3.getLastError() != ConfigErrorCode::NONE)
    {
        std::cerr << "Reader3 encountered an error: " << getErrorMessage(reader3.getLastError()) << std::endl;
    }


    std::cout<<"Value : "<<reader2.getKey<std::string>("name" , "name")<<std::endl;
    std::cout<<"Value : "<<reader2.getKey<bool>("name" , "kill")<<std::endl;
    std::cout<<"Value : "<<reader3.getKey<int>("Block-1" , "key")<<std::endl;


    return 0;
}
