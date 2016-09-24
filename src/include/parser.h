#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <map>

typedef struct {
	//map<char*, char*>


} Graph;

#define MAXMATCHES 5
#define MAXGROUPS 3

extern char *regexString;
extern regex_t regexCompiled;


void initParser();
bool hasMatch(char *str, regmatch_t *match);
void deriveOperation(char *str);
void clearParser();


#endif /* PARSER_H */