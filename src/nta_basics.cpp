#include "nta_basics.hpp"

bool nta_report_allowed_levels[7] = {0, 1, 0, 0, 0, 0, 1};
bool nta_noexecute = 0;

void nta_print_help()
{
    const char *usagetext = NTA_HELPTEXT;
    printf("%s", usagetext);
}

void nta_report_determine_levels(int argc, char *argv[], string keymap_file)
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
            nta_report_allowed_levels[0] = 1;
        }
        else if (strcmp(argv[i], "--report-error") == 0)
        {
            nta_report_allowed_levels[1] = 1;
        }
        else if (strcmp(argv[i], "--report-info") == 0)
        {
            nta_report_allowed_levels[2] = 1;
        }
        else if (strcmp(argv[i], "--report-expand") == 0)
        {
            nta_report_allowed_levels[3] = 1;
        }
        else if (strcmp(argv[i], "--report-debug") == 0)
        {
            nta_report_allowed_levels[4] = 1;
        }
        else if (strcmp(argv[i], "--formatting") == 0)
        {
            nta_report_allowed_levels[5] = 1;
        }
        else if ((strcmp(argv[i], "-t") == 0) || (strcmp(argv[i], "--test-mode") == 0))
        {
            nta_noexecute = 1;
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
            nta_report_allowed_levels[0] = 1;
            nta_report_allowed_levels[1] = 1;
            nta_report_allowed_levels[2] = 1;
            nta_report_allowed_levels[3] = 1;
            nta_report_allowed_levels[4] = 1;
        }
        else if (strcmp(argv[i], "--report-noexpand") == 0)
        {
            nta_report_allowed_levels[3] = 0;
        }
        else if (strcmp(argv[i], "--report-nokeymap") == 0)
        {
            nta_report_allowed_levels[6] = 0;
        }
        else
        {
            nta_print_help();
            exit(64);
        }
    }
}

void nta_report(const int type, const string report)
{
    if (type <= 5)
    {
        if (nta_report_allowed_levels[type])
        {
            switch (type)
            {
            case 0:
                printf("[WARN] ");
                break;
            case 1:
                printf("[ERROR] ");
                break;
            case 2:
                printf("[INFO] ");
                break;
            case 3:
                printf("[NTA_EXPAND] ");
                break;
            case 4:
                printf("[DEBUG] ");
                break;
            case 6:
                printf("[KEYMAP] ");
                break;
            default:
                break;
            }
            printf("%s\n", report.c_str());
        }
    }
};
