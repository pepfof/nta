#pragma once

#ifndef NTAKEYBOARD_HPP_ /* Include guard */
#define NTAKEYBOARD_HPP_

#include "nta_basics.hpp"
#include <fstream>
#include <regex>
#include <linux/uinput.h>
#include <stdlib.h>
#include <fcntl.h>

#define WHITESPACE " \n\r\t\f\v"
#define KEYCODES_FILE "/usr/include/linux/input-event-codes.h"


#define NTAKEY_SCRIPT_FILE "~/nta/keyboard.sh"
#define NTAKEY_LOCK_FILE "/tmp/nta_keyboard.lock"
#define NTAKEY_DEVICE_NAME "NTA Virtual Keyboard"
#define NTAKEY_BUS_TYPE BUS_USB
#define NTAKEY_ID_VENDOR 1
#define NTAKEY_ID_PRODUCT 1

extern int ntakey_global_fd;

void nta_keyserver_start();

void nta_keyserver_end();

void nta_keyserver_emit(int type, int code, int val);

void nta_parse_keysig(string &action_to_parse);

void nta_execute_keysig(string action, vector<int> keylist, unsigned int depth);

#endif