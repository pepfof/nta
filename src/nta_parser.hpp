#ifndef NTAPARSE_HPP_ /* Include guard */
#define NTAPARSE_HPP_

#include <string>
#include <vector>
#include <fstream>
#include <stdio.h>
#include "nta_basics.hpp"
#include "nta_key.hpp"

using namespace std;

void nta_read_config_to_key(const string file, ntakey &key);

#endif