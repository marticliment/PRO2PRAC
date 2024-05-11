#include <iostream>

using namespace std;


#ifdef DEBUG
const std::string red("\033[0;31m");
const std::string green("\033[1;32m");
const std::string yellow("\033[1;33m");
const std::string cyan("\033[0;36m");
const std::string magenta("\033[0;35m");
const std::string reset("\033[0m");
#endif

void Log(int number)
{
#ifdef DEBUG
    cout << yellow << number << reset << endl;
#endif
    number++;
}

void Log(string message)
{
#ifdef DEBUG
    cout << yellow << message << reset << endl;
#endif
    message = "";
}

void Error(int number)
{
#ifdef DEBUG
    cout << red << number << reset << endl;
#endif
    number++;

}

void Error(string message)
{
#ifdef DEBUG
    cout << red << message << reset << endl;
#endif
    message = "";
}