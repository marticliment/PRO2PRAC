#ifndef DEBUG_HH
#define DEBUG_HH

#include <iostream>

using namespace std;

/**
 * @brief Prints a number in yellow.
 * 
 * @param message The number to display only if the DEBUG flag is set
 * @pre None.
 * @post None.
 */
void Log(int number);

/**
 * @brief Prints a message in yellow only if the DEBUG flag is set
 * 
 * @param message The error message to display.
 * @pre None.
 * @post None.
 */void Log(string message);

/**
 * @brief Prints a number in red only if the DEBUG flag is set
 * 
 * @param message The number to display.
 * @pre None.
 * @post None.
 */
void Error(int number);

/**
 * @brief Prints a message in red only if the DEBUG flag is set
 * 
 * @param message The error message to display.
 * @pre None.
 * @post None.
 */
void Error(string message);

#endif