#ifndef NTABASICS_HPP_ /* Include guard */
#define NTABASICS_HPP_

#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>

using namespace std;

#define NTA_HELPTEXT "Usage: nta [OPTION]\n"                                         \
					 "\n"                                                            \
					 "Application options :\n"                                       \
					 "   -h --help			Show this text\n"                               \
					 "   -i FILE			Use this file as input\n"                         \
					 "   -f FILE			Use keymap from FILE\n"                           \
					 "   -t	--test-mode 	Print commands instead of executing them\n" \
					 "\n"                                                            \
					 "Reporting options :\n"                                         \
					 "   --report-warn\n"                                            \
					 "   --report-info\n"                                            \
					 "   --report-expand\n"                                          \
					 "   --report-error \n"                                          \
					 "   --report-debug\n"                                           \
					 "   --report-verbose\n"                                         \
					 "   --report-noparse\n"                                         \
					 "   --report-noexpand\n";

#define NTAREP_WARN 0b1L
#define NTAREP_ERROR 0b10L
#define NTAREP_INFO 0b100L
#define NTAREP_EXPAND 0b1000L
#define NTAREP_DEBUG 0b10000L
#define NTAREP_PARSE 0b100000L

#define NTAREP_DEFAULT (NTAREP_ERROR | NTAREP_PARSE)
#define NTAREP_VERBOSE (NTAREP_WARN | NTAREP_ERROR | NTAREP_INFO | NTAREP_EXPAND | NTAREP_DEBUG | NTAREP_PARSE)

void nta_print_help();

void nta_report_determine_levels(int argc, char *argv[], string &keymap_file);

void nta_report(const long int type, const string report);

#endif
