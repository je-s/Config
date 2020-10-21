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

#include <iostream>
#include <string>
#include "../src/Config.hpp"

int main()
{
    try
    {
        Config config( "./test.cfg" );

        // for ( std::map<std::string, std::string>::iterator it = config.data.begin(); it != config.data.end(); ++it )
        // {
        //     std::cout << it->first << " = " << it->second << std::endl;
        // }

        std::cout << "string = " << config[ "string" ] << std::endl;
        std::cout << "string = " << config.getString( "string" ) << std::endl;
        std::cout << "int1 = " << std::to_string( config.getInteger( "int1" ) ) << std::endl;
        std::cout << "int2 = " << std::to_string( config.getInteger( "int2" ) ) << std::endl;
        std::cout << "uint1 = " << std::to_string( config.getUnsignedInteger( "uint1" ) ) << std::endl;
        std::cout << "uint2 = " << std::to_string( config.getUnsignedInteger( "uint2" ) ) << std::endl;
        std::cout << "long1 = " << std::to_string( config.getLong( "long1" ) ) << std::endl;
        std::cout << "long2 = " << std::to_string( config.getLong( "long2" ) ) << std::endl;
        std::cout << "ulong1 = " << std::to_string( config.getUnsignedLong( "ulong1" ) ) << std::endl;
        std::cout << "ulong2 = " << std::to_string( config.getUnsignedLong( "ulong2" ) ) << std::endl;
        std::cout << "longlong1 = " << std::to_string( config.getLongLong( "longlong1" ) ) << std::endl;
        std::cout << "longlong2 = " << std::to_string( config.getLongLong( "longlong2" ) ) << std::endl;
        std::cout << "ulonglong1 = " << std::to_string( config.getUnsignedLongLong( "ulonglong1" ) ) << std::endl;
        std::cout << "ulonglong2 = " << std::to_string( config.getUnsignedLongLong( "ulonglong2" ) ) << std::endl;
        std::cout << "float1 = " << std::to_string( config.getFloat( "float1" ) ) << std::endl;
        std::cout << "float2 = " << std::to_string( config.getFloat( "float2" ) ) << std::endl;
        std::cout << "double1 = " << std::to_string( config.getDouble( "double1" ) ) << std::endl;
        std::cout << "double2 = " << std::to_string( config.getDouble( "double2" ) ) << std::endl;
        std::cout << "ldouble1 = " << std::to_string( config.getLongDouble( "ldouble1" ) ) << std::endl;
        std::cout << "ldouble2 = " << std::to_string( config.getLongDouble( "ldouble2" ) ) << std::endl;
        std::cout << "bool1 = " << std::to_string( config.getBool( "bool1" ) ) << std::endl;
        std::cout << "bool2 = " << std::to_string( config.getBool( "bool2" ) ) << std::endl;
        std::cout << "bool3 = " << std::to_string( config.getBool( "bool3" ) ) << std::endl;
    }
    catch ( ConfigMalformedException & e )
    {
        std::cerr << "ConfigMalformedException: " << e.what() << std::endl;
    }
    catch ( ConfigMissingException & e )
    {
        std::cerr << "ConfigMissingException: " << e.what() << std::endl;
    }
    catch ( ConfigKeyNotFoundException & e )
    {
        std::cerr << "ConfigKeyNotFoundException: " << e.what() << std::endl;
    }
    catch ( NumericConfigValueMalformedException & e )
    {
        std::cerr << "NumericConfigValueMalformedException: " << e.what() << std::endl;
    }
    catch ( Exception & e )
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
