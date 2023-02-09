#ifndef NTABASICS_HPP_ /* Include guard */
#define NTABASICS_HPP_

#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

using namespace std;

#define NTA_HELPTEXT "Usage: nta [OPTION]\n"                                         \
                     "\n"                                                            \
                     "Application options :\n"                                       \
                     "   -h, --help Show this text\n"                                \
                     "   -f FILE Use keymap from FILE\n"                             \
                     "   -t, --test-mode Print commands instead of executing them\n" \
                     "\n"                                                            \
                     "Reporting options :\n"                                         \
                     "   --report-warn\n"                                            \
                     "   --report-info\n"                                            \
                     "   --report-expand\n"                                          \
                     "   --report-error \n"                                          \
                     "   --report-debug\n"                                           \
                     "   --report-verbose\n"                                         \
                     "   --report-nokeymap\n"                                        \
                     "   --report-noexpand\n";

void nta_print_help();

void nta_report_determine_levels(int argc, char *argv[], string keymap_file);

void nta_report(const int type, const string report);

#endif
