#ifndef NTAPARSE_H_ /* Include guard */
#define NTAPARSE_H_

#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "nta_basics.hpp"
#include "nta_key.hpp"

using namespace std;

void nta_read_config_to_key(const string file, ntakey &key);

#endif