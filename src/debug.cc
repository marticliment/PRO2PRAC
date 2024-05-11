#ifndef DEBUG_HH
#define DEBUG_HH

#include "debug.hh"
#include <iostream>

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

#endif