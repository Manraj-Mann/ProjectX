# ConfigReader

`ConfigReader` is a C++ class designed for reading and parsing configuration files. It supports extracting and converting configuration values from a file into different data types. This class is useful for applications that need to read configuration settings from a text file.

## Overview

The `ConfigReader` class can:

- Load and parse configuration files in a simple format.
- Store configuration data in a structured way.
- Provide error reporting for various file and parsing issues.
- Retrieve configuration values and convert them to various types.

## Configuration File Format

The configuration file should follow this format:

```ini
[BlockName]
key1=value1
key2=value2

[AnotherBlock]
keyA=valueA
keyB=valueB
