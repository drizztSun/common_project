#include <stdlib.h>
#include <stdio.h>
#include "func.h"


int greet(const char* name, int year, char *out) 
{
    int n;

    n = sprintf(out, "Greetings, %s from %d ! We come in pease", name, year);

    return n;
};

int greet_s(struct Greeter *g, char *out)
{
    int n;

    n = sprintf(out, "Greetings, %s from %d ! We come in pease", g->name, g->year);

    return n;
};