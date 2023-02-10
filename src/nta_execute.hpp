#ifndef NTAEXECUTE_HPP_ /* Include guard */
#define NTAEXECUTE_HPP_

using namespace std;

#include <string>
#include <vector>
#include <stdio.h>
#include "nta_basics.hpp"
#include "./nta_execute_modules/nta_keyboard.hpp"
#include "./nta_execute_modules/nta_system.hpp"

#define nta_func_1_id 'A'
#define nta_func_default_id (nta_func_A_id - 1)

#define nta_execute_default(function, action, keylist, depth) nta_execute_system(action)
#define nta_execute_func_1(function, action, keylist, depth) nta_execute_keysig(action, keylist, depth)
#define nta_execute_func_2(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_3(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_4(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_5(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_6(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_7(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_8(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_9(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_10(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_11(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_12(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_13(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_14(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_15(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_16(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_17(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_18(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_19(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_20(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_21(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_22(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_23(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_24(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_25(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)
#define nta_execute_func_26(function, action, keylist, depth) nta_execute_nothing(function, action, keylist, depth)

void nta_execute_nothing(...);

void nta_execute(signed char function, string expanded_action, vector<int> keylist, unsigned int depth);

#endif

