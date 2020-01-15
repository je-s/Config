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

#include "Config.hpp"

Config::Config( std::string fileName, char delimiter, char commentDelimiter )
{
    setDelimiter( delimiter );
    setCommentDelimiter( commentDelimiter );
    parseData( fileName );
}

void Config::setDelimiter( char delimiter )
{
    this->delimiter = delimiter;
}

char Config::getDelimiter()
{
    return this->delimiter;
}

void Config::setCommentDelimiter( char commentDelimiter )
{
    this->commentDelimiter = commentDelimiter;
}

char Config::getCommentDelimiter()
{
    return this->commentDelimiter;
}

bool Config::fileExists( std::string fileName )
{
    if ( std::ifstream( fileName ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Config::isFormatValid( std::string line )
{
    line = trimLine( line );

    if ( std::count( line.begin(), line.end(), getDelimiter() ) == 1 && line.find( getDelimiter() ) != 0 && line.find( getDelimiter() ) != ( line.length() - 1 ) )
    {
        return true;
    }
    else
    {
        return false;
    }   
}

bool Config::elementExists( std::string key )
{
    // If the key already exists.
    if ( data.find( key ) != data.end() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string Config::trimLine( std::string line )
{
    size_t firstChar = line.find_first_not_of(' ');

    if ( firstChar == std::string::npos )
    {
        return "";
    }

    size_t lastChar = line.find_last_not_of(' ');

    return line.substr( firstChar, ( lastChar - firstChar + 1 ) );
}

bool Config::isComment( std::string line )
{
    line = trimLine( line );

    if ( line[0] == getCommentDelimiter() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Config::parseLine( std::string line )
{
    if ( isComment( line ) )
    {
        return;
    }

    if ( isFormatValid( line ) )
    {
        std::string key, value;
        std::istringstream issLine( line );

        // Parse the line until we fetch our delimiter, and trim it.
        std::getline( issLine, key, getDelimiter() );
        key = trimLine( key );

        // Parse the rest of the line and trim it.
        std::getline( issLine, value );
        std::size_t lineEnd = value.find_first_of( "\r\n" );

        if ( lineEnd != std::string::npos )
        {
            value.substr( 0, lineEnd );
        }

        value = trimLine( value );
    
        // Add Value
        if ( !elementExists( key ) )
        {
            data[key] = value;
        }
        else
        {
            throw ConfigMalformedException( "\"" + key + "\" has multiple occurences" );
        }
    }
    else
    {
        throw ConfigMalformedException( "Line: " + line );
    }
}

void Config::parseData( std::string fileName )
{
    if ( !fileExists( fileName ) )
    {
        throw ConfigMissingException( fileName );
    }

    std::string line;
    std::ifstream fileStream;

    fileStream.open( fileName, std::ifstream::out | std::ifstream::app );

    while ( std::getline( fileStream, line ) )
    {
        parseLine( line );
    }

    fileStream.close();
}

std::string Config::operator[] ( std::string key )
{
    if ( !elementExists( key ) )
    {
        throw ConfigKeyNotFoundException( key );
    }

    std::string value = "";
    std::map<std::string, std::string>::iterator pos = data.find( key );

    if ( pos != data.end() )
    {
        value = pos->second;
    }

    return value;
}

std::string Config::getString( std::string key )
{
    return (*this)[key];
}

bool Config::getBool( std::string key )
{
    return getInteger( key );
}

int Config::getInteger( std::string key )
{
    int value;

    try
    {
        value = std::stoi( (*this)[key].c_str() );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

unsigned int Config::getUnsignedInteger( std::string key )
{
    unsigned int value;

    try
    {
        value = (unsigned int) std::stoul( (*this)[key].c_str(), 0, 10 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

long Config::getLong( std::string key )
{
    long value;

    try
    {
        value = std::stol( (*this)[key].c_str(), 0, 10 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

unsigned long Config::getUnsignedLong( std::string key )
{
    unsigned long value;

    try
    {
        value = std::stoul( (*this)[key].c_str(), 0, 10 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

long long Config::getLongLong( std::string key )
{
    long long value;

    try
    {
        value = std::stoll( (*this)[key].c_str(), 0, 10 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

unsigned long long Config::getUnsignedLongLong( std::string key )
{
    unsigned long long value;

    try
    {
        value = std::stoull( (*this)[key].c_str(), 0, 10 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

float Config::getFloat( std::string key )
{
    float value;

    try
    {
        value = std::stof( (*this)[key].c_str(), 0 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

double Config::getDouble( std::string key )
{
    double value;

    try
    {
        value = std::stod( (*this)[key].c_str(), 0 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}

long double Config::getLongDouble( std::string key )
{
    long double value;

    try
    {
        value = std::stold( (*this)[key].c_str(), 0 );
    }
    catch( const std::invalid_argument & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' can not be converted." );
    }
    catch( const std::out_of_range & e )
    {
        throw NumericConfigValueMalformedException( "Value for key '" + key + "' is out of range." );
    }
    
    return value;
}
