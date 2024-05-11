#include "NavigationDecisions.hh"

using namespace std;

string NavigationDecisionAsString(NavigationDecision decision)
{
    switch(decision)
    {
        case NavigationDecision::Left:
            return "left";
            break;
        
        case NavigationDecision::Right:
            return "right";
            break;

        case NavigationDecision::Top:
            return "top";
            break;

        default:
            return "Invalid NavigationDecision value";
            break;
    }
}