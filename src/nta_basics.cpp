#include "nta_basics.hpp"

long int nta_report_global_allowed_levels = NTAREP_DEFAULT;
bool nta_global_noexecute = 0;

void nta_print_help()
{
	const char *usagetext = NTA_HELPTEXT;
	printf("%s", usagetext);
}

void nta_report_determine_levels(int argc, char *argv[], string &keymap_file)
{
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL)
	{
		homedir = getpwuid(getuid())->pw_dir;
	}

	keymap_file = homedir + keymap_file;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--report-warn") == 0)
		{
			nta_report_global_allowed_levels |= NTAREP_WARN;
		}
		else if (strcmp(argv[i], "--report-error") == 0)
		{
			nta_report_global_allowed_levels |= NTAREP_ERROR;
		}
		else if (strcmp(argv[i], "--report-info") == 0)
		{
			nta_report_global_allowed_levels |= NTAREP_INFO;
		}
		else if (strcmp(argv[i], "--report-expand") == 0)
		{
			nta_report_global_allowed_levels |= NTAREP_EXPAND;
		}
		else if (strcmp(argv[i], "--report-debug") == 0)
		{
			nta_report_global_allowed_levels |= NTAREP_DEBUG;
		}
		else if ((strcmp(argv[i], "-t") == 0) || (strcmp(argv[i], "--test-mode") == 0))
		{
			nta_global_noexecute = 1;
		}
		else if (strcmp(argv[i], "-f") == 0)
		{
			if (i + 1 < argc)
			{
				keymap_file = argv[i + 1];
			}
			else
			{
				printf("No file passed.\n");
				exit(66);
			}
			i++;
		}
		else if (strcmp(argv[i], "--report-verbose") == 0)
		{
			nta_report_global_allowed_levels |= NTAREP_VERBOSE;
		}
		else if (strcmp(argv[i], "--report-noexpand") == 0)
		{
			nta_report_global_allowed_levels &= !NTAREP_EXPAND;
		}
		else if (strcmp(argv[i], "--report-noparse") == 0)
		{
			nta_report_global_allowed_levels &= !NTAREP_PARSE;
		}
		else
		{
			nta_print_help();
			exit(64);
		}
	}
}

void nta_report(const long int type, const string report)
{
	if (nta_report_global_allowed_levels & type)
	{
		switch (nta_report_global_allowed_levels & type)
		{
		case NTAREP_WARN:
			printf("[WARN] ");
			break;
		case NTAREP_ERROR:
			printf("[ERROR] ");
			break;
		case NTAREP_INFO:
			printf("[INFO] ");
			break;
		case NTAREP_EXPAND:
			printf("[EXPAND] ");
			break;
		case NTAREP_DEBUG:
			printf("[DEBUG] ");
			break;
		case NTAREP_PARSE:
			printf("[PARSE] ");
			break;
		default:
			break;
		}
		printf("%s\n", report.c_str());
	}
};
