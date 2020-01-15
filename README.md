# Config
Config is a very minimalisc config class, which allows to parse simple Key-Value pairs from a text file. This values can then be accessed by their particular key via the subscript operator: `[<key>]`.

# Installation
After cloning, execute `git submodule update --init --recursive --remote` in the Repo to initialize and download all dependencies.

# Folder structure
* `dependencies` contains a git-submodule to the Exception-Baseclass.
* `src`  contains the source code (`Config` class and `ConfigExceptions` classes).
* `test` contains a test application and a test config-file. The latter can be edited to test the correct functionality.

# Including and compiling Config in a project
C++14 is required for compilation.

In order to use Config, `<path>/Config/src/Config.hpp` needs to be included.
In order to compile Config, following files need to be compiled and linked:
* `<path>/Config/dependencies/Exception/src/Exception.cpp`
* `<path>/Config/src/ConfigExceptions.cpp`
* `<path>/Config/src/Config.cpp`

# Usage
## Config format
* A config file is read line by line; each line representing one key-value pair.
* The key starts at the beginning of the line, and lasts until the first occurence of our delimiter.
    * The standard delimiter is `=`.
* The value starts after the delimiter and lasts until the end of the line, which is marked by any EOL character (`\n` or `\r`).
* All keys and values are trimmed off their leading and trailing spaces. Spaces in between are being preserved.
* A valid commment gets introduced whenever the first non-space character (after trimming) equals the comment delimiter.
    * The standard comment delimiter is `#`.
    * The line can either be a key-value pair, or a comment; comments after a value are not possible.

Example of a valid config file:
```
# This is a comment
string=test string # This is no comment and just gets appended to the rest of the string
int=2147483647
uint=4294967295
long=9223372036854775807
ulong=18446744073709551615
longlong=9223372036854775807
ulonglong=18446744073709551615
float=1.337
double=1.337
ldouble=-1.337
```

## Basic usage
1. Instantiate a new `Config`-Object with the path to the config file as parameter: `Config config( "./config.cfg" );`.
    1. The default delimiter is `=` and the default comment-delimiter is `#`.\
    This can optionally be changed in the constructor: `Config config( "<configPath>", '<delimiter>', '<commentDelimiter>' );`.
2. Access a value with one of the following functions (for example the subscript operator: `std::string value1 = config["value1"];`):
    1. `std::string getString( std::string key )` or `std::string operator[]( std::string key )`
    2. `int getInteger( std::string key )`
    3. `unsigned int getUnsignedInteger( std::string key )`
    4. `long getLong( std::string key )`
    5. `unsigned long getUnsignedLong( std::string key )`
    6. `long long getLongLong( std::string key )`
    7. `unsigned long long getUnsignedLongLong( std::string key )`
    8. `float getFloat( std::string key )`
    9. `double getDouble( std::string key )`
    10. `long double getLongDouble( std::string key )`
3. Catch the exceptions to handle possible errors while using Config:
    1. `ConfigMalformedException`
    2. `ConfigMissingException`
    3. `ConfigKeyNotFoundException`
    4. `NumericConfigValueMalformedException`

## Accessing the data container directly
All values are contained in a `std::map<std::string, std::string>`. The container can be accessed via the public variable `data`.

Example for iterating over all contained key-value pairs:
```
Config config( "./config.cfg" );

for ( std::map<std::string, std::string>::iterator it = config.data.begin(); it != config.data.end(); ++it )
{
	std::cout << it->first << " = " << it->second << std::endl;
}
```