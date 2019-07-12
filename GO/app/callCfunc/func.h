#ifndef __FUNC__
#define __FUNC__

int greet(const char* name, int year, char *out);

struct Greeter {
    const char *name;
    int year;
};

int greet_s(struct Greeter *g, char *out);

#endif