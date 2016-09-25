
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "include/parser.h"

#define PARAMETERS 4
#define FLAG_FILE "-f"
#define FLAG_TYPE "-d"


void extractFlags(int argc, char *argv[], char *benchmark, char *type);
void extractGraph(FILE *in);

int main(int argc, char *argv[])
{
	if(argc < PARAMETERS + 1) {
		printf("Usage: -f benchmark_filename -t data_type");
		return 0;
	}

	char benchmark[90];
	char type[10];
    extractFlags(argc, argv, benchmark, type);
	

	FILE *inFid = fopen(benchmark, "r");
    if (inFid == 0) {
        printf("Couldn't open %s, path or file invalid", benchmark);
        return 1;
    }

    initParser();

   	extractGraph(inFid);

  	clearParser();
    fclose(inFid);


	return 0;
}

void extractFlags(int argc, char *argv[], char *benchmark, char *type)
{
    int i;
    for(i = 1; i < argc; i++) {
        if(strcmp(FLAG_TYPE, argv[i]) == 0) {
            strcpy(type, argv[++i]);
        } else if(strcmp(FLAG_FILE, argv[i]) == 0) {
            strcpy(benchmark, argv[++i]);
        }
    }
}

void extractGraph(FILE *inFid)
{
    char buf[256];
    while(fgets(buf, sizeof(buf), inFid) != NULL) {
        deriveOperation(buf);
    }
}