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

#ifndef CONFIGEXCEPTIONS_HPP
#define CONFIGEXCEPTIONS_HPP

// Exception Class
#include "../dependencies/Exception/src/Exception.hpp"

class ConfigMalformedException : private Exception
{
public:
    using Exception::Exception;

    std::string what() throw();
};

class ConfigMissingException : private Exception
{
public:
    using Exception::Exception;

    std::string what() throw();
};

class ConfigKeyNotFoundException : private Exception
{
public:
    using Exception::Exception;

    std::string what() throw();
};

class NumericConfigValueMalformedException : private Exception
{
public:
    using Exception::Exception;

    std::string what() throw();
};

#endif // CONFIGEXCEPTIONS_HPP
