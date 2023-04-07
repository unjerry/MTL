#ifndef ZAHLEN_H
#define ZAHLEN_H

#include <stdio.h>
#include <vector>
#include <string>

class zahlen
{

public:
    std::vector<char> dt;
    zahlen(size_t m = 0, size_t n = 1);
    void print(size_t opt = 0);
    void fprint(FILE *f, size_t opt = 0);
    int scan(size_t opt = 0);
    int fscan(FILE *f, size_t opt = 0);
    void operator=(const size_t &y);
};
zahlen operator~(const zahlen &a);
zahlen operator-(const zahlen &a);
zahlen operator+(const zahlen &a, const zahlen &b);
zahlen operator*(const zahlen &a, const zahlen &b);

#endif
