#include "nta_keyboard.hpp"

void nta_execute_keysig(string action, vector<int> keylist, unsigned int depth)
{
    printf("the key \"%s\" is doing action %d\n", action.c_str(), keylist[depth + 1]);
}