#include "nta_execute.hpp"

void nta_execute_nothing(...)
{
	nta_report(NTAREP_WARN, "Your key's assigned function was not defined!");
}

void nta_parse_nothing(...)
{
	return;
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

void nta_parse(signed char function, string &action_to_parse)
{
	// is there any better way to do this? please?
	switch (function + nta_func_1_id)
	{
	case nta_func_1_id:
		nta_parse_func_1(action_to_parse);
		break;
	case nta_func_1_id + 1:
		nta_parse_func_2(action_to_parse);
		break;
	case nta_func_1_id + 2:
		nta_parse_func_3(action_to_parse);
		break;
	case nta_func_1_id + 3:
		nta_parse_func_4(action_to_parse);
		break;
	case nta_func_1_id + 4:
		nta_parse_func_5(action_to_parse);
		break;
	case nta_func_1_id + 5:
		nta_parse_func_6(action_to_parse);
		break;
	case nta_func_1_id + 6:
		nta_parse_func_7(action_to_parse);
		break;
	case nta_func_1_id + 7:
		nta_parse_func_8(action_to_parse);
		break;
	case nta_func_1_id + 8:
		nta_parse_func_9(action_to_parse);
		break;
	case nta_func_1_id + 9:
		nta_parse_func_10(action_to_parse);
		break;
	case nta_func_1_id + 10:
		nta_parse_func_11(action_to_parse);
		break;
	case nta_func_1_id + 11:
		nta_parse_func_12(action_to_parse);
		break;
	case nta_func_1_id + 12:
		nta_parse_func_13(action_to_parse);
		break;
	case nta_func_1_id + 13:
		nta_parse_func_14(action_to_parse);
		break;
	case nta_func_1_id + 14:
		nta_parse_func_15(action_to_parse);
		break;
	case nta_func_1_id + 15:
		nta_parse_func_16(action_to_parse);
		break;
	case nta_func_1_id + 16:
		nta_parse_func_17(action_to_parse);
		break;
	case nta_func_1_id + 17:
		nta_parse_func_18(action_to_parse);
		break;
	case nta_func_1_id + 18:
		nta_parse_func_19(action_to_parse);
		break;
	case nta_func_1_id + 19:
		nta_parse_func_20(action_to_parse);
		break;
	case nta_func_1_id + 20:
		nta_parse_func_21(action_to_parse);
		break;
	case nta_func_1_id + 21:
		nta_parse_func_22(action_to_parse);
		break;
	case nta_func_1_id + 22:
		nta_parse_func_23(action_to_parse);
		break;
	case nta_func_1_id + 23:
		nta_parse_func_24(action_to_parse);
		break;
	case nta_func_1_id + 24:
		nta_parse_func_25(action_to_parse);
		break;
	case nta_func_1_id + 25:
		nta_parse_func_26(action_to_parse);
		break;
	default:
		nta_parse_default(action_to_parse);
		break;
	}
}