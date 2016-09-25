
#include "include/parser.h"
#include "include/operations.h"

const char *regexString = "(_?\\w+)( (\\+|-|\\*|\\/|<|<=|>|>=|==|\\!=|&&|\\|\\||<<a|<<c)( )+(\\w+)( )+(\\w+))? *\n*";
regex_t regexCompiled;


void initParser()
{
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("Could not compile regular expression.\n");
        return;
    }
}


bool hasMatch(char *str, regmatch_t *matches)
{
    return regexec(&regexCompiled, str, MAXGROUPS, matches, 0) == 0;
}


bool hasGroup(regmatch_t *match)
{
    return match->rm_so != (size_t)-1;
}


void deriveOperation(char *str)
{
    regmatch_t matches[MAXGROUPS];

    if (!hasMatch(str, matches)) {
        return;
    }

    int g;
    vector<char*> list;
    for (g = 1; g < MAXGROUPS; g += 2) {
        if (!hasGroup(&matches[g])) {
            break;  // No more groups
        }

        size_t strln = matches[g].rm_eo - matches[g].rm_so + 1;
        char strMatch[strln];

        strncpy(strMatch, str + matches[g].rm_so, strln);
        strMatch[strln-1] = '\0';
        list.push_back(strMatch);
    }
}


Operation *createOperation(vector<char*> list)
{
    return newOperation(list[1], &list[2], list.size() - 2, list[0]);
    //char *op, char *inList[], size_t length, char *out)
}


void clearParser()
{
    regfree(&regexCompiled);
}