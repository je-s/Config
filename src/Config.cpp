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
    parseFile( fileName );
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

    return false;
}

bool Config::isFormatValid( std::string line )
{
    line = trimLine( line );

    if ( line.find( getDelimiter() ) != 0 )
    {
        return true;
    }

    return false;
}

bool Config::elementExists( std::string key )
{
    // If the key already exists.
    if ( data.find( key ) != data.end() )
    {
        return true;
    }

    return false;
}

std::string Config::trimLine( std::string line )
{
    size_t firstChar = line.find_first_not_of( ' ' );

    if ( firstChar == std::string::npos )
    {
        return "";
    }

    size_t lastChar = line.find_last_not_of( ' ' );

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
        std::istringstream stringstreamLine( line );

        // Parse the line until we fetch our delimiter, and trim it.
        std::getline( stringstreamLine, key, getDelimiter() );
        key = trimLine( key );

        // Parse the rest of the line and trim it.
        std::getline( stringstreamLine, value );
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

void Config::parseFile( std::string fileName )
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

template <class T>
T Config::getNumericValue( std::string key )
{
    T value;

    try
    {
        if ( typeid( int ) == typeid( T ) )
        {
            value = std::stoi( (*this)[key] );
        }
        else if ( typeid( unsigned int ) == typeid( T ) )
        {
            value = (unsigned int) std::stoul( (*this)[key], 0, 10 );
        }
        else if ( typeid( long ) == typeid( T ) )
        {
            value = std::stol( (*this)[key], 0, 10 );
        }
        else if ( typeid( unsigned long ) == typeid( T ) )
        {
            value = std::stoul( (*this)[key], 0, 10 );
        }
        else if ( typeid( long long ) == typeid( T ) )
        {
            value = std::stoll( (*this)[key], 0, 10 );
        }
        else if ( typeid( unsigned long long ) == typeid( T ) )
        {
            value = std::stoull( (*this)[key], 0, 10 );
        }
        else if ( typeid( float ) == typeid( T ) )
        {
            value = std::stof( (*this)[key], 0 );
        }
        else if ( typeid( double ) == typeid( T ) )
        {
            value = std::stod( (*this)[key], 0 );
        }
        else if ( typeid( long double ) == typeid( T ) )
        {
            value = std::stold( (*this)[key], 0 );
        }
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

int Config::getInteger( std::string key )
{
    return getNumericValue<int>( key );
}

unsigned int Config::getUnsignedInteger( std::string key )
{
    return getNumericValue<unsigned int>( key );
}

long Config::getLong( std::string key )
{
    return getNumericValue<long>( key );
}

unsigned long Config::getUnsignedLong( std::string key )
{
    return getNumericValue<unsigned long>( key );
}

long long Config::getLongLong( std::string key )
{
    return getNumericValue<long long>( key );
}

unsigned long long Config::getUnsignedLongLong( std::string key )
{
    return getNumericValue<unsigned long long>( key );
}

float Config::getFloat( std::string key )
{
    return getNumericValue<float>( key );
}

double Config::getDouble( std::string key )
{
    return getNumericValue<double>( key );
}

long double Config::getLongDouble( std::string key )
{
    return getNumericValue<long double>( key );
}

bool Config::getBool( std::string key )
{
    return getInteger( key );
}
