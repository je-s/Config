/*
    Copyright 2019 Jan-Eric Schober

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef CONFIG_HPP
#define CONFIG_HPP

// Standard Libraries
#include <map> // std::map
#include <sstream> // std::istringstream
#include <fstream> // std::ifstream
#include <string> // std::string, std::getline, std::string::npos
#include <algorithm> // std::count

// Custom Exception Classes
#include "ConfigExceptions.hpp" // ConfigMalformedException, ConfigMissingException, ConfigKeyNotFoundException

class Config
{
private:
    // Constants
    static const char DELIMITER = '=';
    static const char COMMENT_DELIMITER = '#';

    // Variables
    char delimiter;
    char commentDelimiter;

    // Methods
    void setDelimiter( char delimiter );
    char getDelimiter();
    void setCommentDelimiter( char commentDelimiter );
    char getCommentDelimiter();
    bool fileExists( std::string fileName );
    bool isFormatValid( std::string fileName );
    bool elementExists( std::string key );
    std::string trimLine( std::string line );
    bool isComment( std::string line );
    void parseLine( std::string line );
    void parseData( std::string fileName );

public:
    // Variables
    std::map<std::string, std::string> data;

    // Constructors
    Config( std::string fileName, char delimiter = DELIMITER, char commentDelimiter = COMMENT_DELIMITER );

    // Operators
    std::string operator[]( std::string key );

    // Methods
    std::string getString( std::string key );
    bool getBool( std::string key );
    int getInteger( std::string key );
    unsigned int getUnsignedInteger( std::string key );
    long getLong( std::string key );
    unsigned long getUnsignedLong( std::string key );
    long long getLongLong( std::string key );
    unsigned long long getUnsignedLongLong( std::string key );
    float getFloat( std::string key );
    double getDouble( std::string key );
    long double getLongDouble( std::string key );
};

#endif // CONFIG_HPP