#include "nta_system.hpp"

void nta_execute_system(string action)
{
    system(action.c_str());
}