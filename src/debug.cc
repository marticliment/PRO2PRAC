#ifndef DEBUG_HH
#define DEBUG_HH

#include "debug.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;


#ifdef DEBUG
const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string cyan("\033[0;36m");
const string magenta("\033[0;35m");
const string reset("\033[0m");
#endif

void Log(int number)
{
#ifdef DEBUG
    cout << yellow << number << reset << '\n';
#endif
    number++;
}

void Log(string message)
{
#ifdef DEBUG
    cout << yellow << message << reset << '\n';
#endif
    message = "";
}

void Error(int number)
{
#ifdef DEBUG
    cout << red << number << reset << '\n';
#endif
    number++;

}

void Error(string message)
{
#ifdef DEBUG
    cout << red << message << reset << '\n';
#endif
    message = "";
}

#endif