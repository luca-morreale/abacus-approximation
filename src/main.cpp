
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "include/parser.h"

#define PARAMETERS 4
#define FLAG_FILE "-f"
#define FLAG_TYPE "-d"




int main(int argc, char *argv[])
{
	if(argc < PARAMETERS + 1) {
		printf("Usage: -f benchmark_filename -t data_type");
		return 0;
	}

	char benchmark[90];
	char type[10];
	int i;
	for(i = 1; i < argc; i++) {
		char flag[3];

		if(strcmp(FLAG_TYPE, argv[i]) == 0) {
			strcpy(type, argv[++i]);
		} else if(strcmp(FLAG_FILE, argv[i]) == 0) {
			strcpy(benchmark, argv[++i]);
		}
	}

	FILE *inFid;
	inFid = fopen(benchmark, "r");
    if (inFid == 0) {
        printf("Couldn't open %s, path or file invalid", benchmark);
        return 1;
    }

    initParser();

   	char buf[256];
  	while(fgets(buf, sizeof(buf), inFid) != NULL) {

    	deriveOperation(buf);
  	}


  	clearParser();

    fclose(inFid);


	return 0;
}