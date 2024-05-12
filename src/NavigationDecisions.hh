#ifndef NAVIGATION_DECISIONS_HH
#define NAVIGATION_DECISIONS_HH


#include <string>

using namespace std;

/// @brief Represents the decision a ship can take when navigating a Valley
enum class NavigationDecision
{
    Left,
    Right,
    Top
};

/// @brief Converts a NavigationDecision value to a human-readable string
/// @param decision The NavigationDecision to convert to a string
/// @return a string representing the NavigationDecision value
string NavigationDecisionAsString(NavigationDecision decision);

#endif