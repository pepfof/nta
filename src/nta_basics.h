#ifndef NTABASICS_H_   /* Include guard */
#define NTABASICS_H_

#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>


using namespace std;

bool nta_report_allowed_levels[6] = {0};

void nta_report_determine_levels(int argc, char *argv[]){
    for (int i=1; i< argc; i++) {
    if (strcmp(argv[i], "--warn") == 0) 
    {
			nta_report_allowed_levels[0]=1;
	}
    else if (strcmp(argv[i], "--error") == 0) 
    {
			nta_report_allowed_levels[1]=1;
	}
    else if (strcmp(argv[i], "--info") == 0) 
    {
			nta_report_allowed_levels[2]=1;
	}
    else if (strcmp(argv[i], "--expand") == 0) 
    {
			nta_report_allowed_levels[3]=1;
	}
    else if (strcmp(argv[i], "--debug") == 0) 
    {
			nta_report_allowed_levels[4]=1;
	}
    else if (strcmp(argv[i], "--formatting") == 0) 
    {
			nta_report_allowed_levels[5]=1;
	}
    else if (strcmp(argv[i], "--verbose") == 0) 
    {
			nta_report_allowed_levels[0]=1;
            nta_report_allowed_levels[1]=1;
            nta_report_allowed_levels[2]=1;
            nta_report_allowed_levels[3]=1;
            nta_report_allowed_levels[4]=1;
	}
    else if (strcmp(argv[i], "--noexpand") == 0) 
    {
            nta_report_allowed_levels[3]=0;
	}
    else printf("Help text\n");
 }
}

void nta_report(const int type, const string report){
    if(type<=5){
    if(nta_report_allowed_levels[type]){
    switch (type){
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
        default:
            break;
        }
    printf("%s\n", report.c_str());
    }
    }
};

#endif 