#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <vector>


#define MAXMATCHES 1
#define MAXGROUPS 10

extern const char *regexString;
extern regex_t regexCompiled;


void initParser();
bool hasMatch(char *str, regmatch_t *match);
void deriveOperation(char *str);
void clearParser();


#endif /* PARSER_H */