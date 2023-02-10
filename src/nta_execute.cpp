#include "nta_execute.hpp"

void nta_execute_nothing(...)
{
    nta_report(NTAREP_WARN, "Your key's assigned function was not defined!");
}

void nta_execute(signed char function, string expanded_action, vector<int> keylist, unsigned int depth)
{

    // is there any better way to do this? please?
    switch (function + nta_func_1_id)
    {
    case nta_func_1_id:
        nta_execute_func_1(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 1:
        nta_execute_func_2(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 2:
        nta_execute_func_3(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 3:
        nta_execute_func_4(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 4:
        nta_execute_func_5(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 5:
        nta_execute_func_6(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 6:
        nta_execute_func_7(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 7:
        nta_execute_func_8(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 8:
        nta_execute_func_9(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 9:
        nta_execute_func_10(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 10:
        nta_execute_func_11(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 11:
        nta_execute_func_12(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 12:
        nta_execute_func_13(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 13:
        nta_execute_func_14(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 14:
        nta_execute_func_15(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 15:
        nta_execute_func_16(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 16:
        nta_execute_func_17(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 17:
        nta_execute_func_18(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 18:
        nta_execute_func_19(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 19:
        nta_execute_func_20(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 20:
        nta_execute_func_21(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 21:
        nta_execute_func_22(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 22:
        nta_execute_func_23(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 23:
        nta_execute_func_24(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 24:
        nta_execute_func_25(function, expanded_action, keylist, depth);
        break;
    case nta_func_1_id + 25:
        nta_execute_func_26(function, expanded_action, keylist, depth);
        break;
    default:
        nta_execute_default(function, expanded_action, keylist, depth);
        break;
    }
}