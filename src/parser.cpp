
#include "include/parser.h"

char *regexString = "\\w+";
regex_t regexCompiled;


void initParser()
{
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return;
    }
}

bool hasMatch(char *str, regmatch_t *match)
{
    return regexec(&regexCompiled, str, 1, match, 0) == 0;
}

void deriveOperation(char *str)
{
    printf("line: %s", str);
    
    regmatch_t match;
    char *cursor = str;

    for(unsigned m = 0; m < MAXMATCHES; m++) {

        if(!hasMatch(cursor, &match)) 
            return;

        if (match.rm_so == (size_t)-1){
            continue;
        }

        unsigned int offset = match.rm_eo;
        size_t strln = match.rm_eo - match.rm_so + 1;

        
        char strMatch[strln];
        strncpy(strMatch, cursor + match.rm_so, strln);

        strMatch[strln-1] = '\0';
        printf("Match %u: %s\n", m, strMatch);

        cursor += offset;   
    }

}

void clearParser()
{
    regfree(&regexCompiled);
}