#include "zahlen.h"

zahlen::zahlen(size_t m, size_t n)
{
    this->dt.resize(n);
    for (size_t i = 0; i < this->dt.size(); i++)
    {
        this->dt[i] = (m % 10);
        m /= 10;
    }
}
void zahlen::print(size_t opt)
{
    std::string tmp;
    tmp.resize(this->dt.size());
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(print):length==0\n");
    }
    switch (opt)
    {
    case 0:
        for (int i = 0; 2 * i + 1 <= this->dt.size(); i++)
        {
            tmp[i] = this->dt[this->dt.size() - 1 - i] + '0';
            tmp[this->dt.size() - 1 - i] = this->dt[i] + '0';
        }
        // tmp[this->dt.size()] = 0;
        printf("(zahlen)<%llu _%s >", this->dt.size(), tmp.c_str());
        break;
    case 1:
        if (this->dt[this->dt.size() - 1] >= 5)
        {
            zahlen I = 1, c = ~(*this), b;
            b = c + I;
            for (int i = 0; 2 * i + 1 <= b.dt.size(); i++)
            {
                tmp[i] = b.dt[b.dt.size() - 1 - i] + '0';
                tmp[b.dt.size() - 1 - i] = b.dt[i] + '0';
            }
            // tmp[b.dt.size()] = 0;
            printf("(zahlen)<%llu -%s >", b.dt.size(), tmp.c_str());
            break;
        }
        else
        {
            for (int i = 0; 2 * i + 1 <= this->dt.size(); i++)
            {
                tmp[i] = this->dt[this->dt.size() - 1 - i] + '0';
                tmp[this->dt.size() - 1 - i] = this->dt[i] + '0';
            }
            // tmp[this->dt.size()] = 0;
            printf("(zahlen)<%llu +%s >", this->dt.size(), tmp.c_str());
        }
    }
}
int zahlen::fscan(FILE *f, size_t opt)
{
    int rt = 0, len;
    char sw;
    std::string tmp;
    fscanf(f, "%*[^(]");
    rt = fscanf(f, "(zahlen)<%llu %c", &len, &sw);
    this->dt.resize(len);
    tmp.resize(this->dt.size());
    rt = fscanf(f, "%s >", tmp.c_str());
    // printf("%s %c\n", tmp.c_str(), sw);

    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(print):length==0\n");
    }
    for (int i = 0; 2 * i + 1 <= this->dt.size(); i++)
    {
        this->dt[this->dt.size() - 1 - i] = tmp[i] - '0';
        this->dt[i] = tmp[this->dt.size() - 1 - i] - '0';
    }
    if (sw == '-')
    {
        // zahlen e = 1;
        *this = ~(*this) + 1;
    }
    return rt;
}
void zahlen::operator=(const size_t &y)
{
    if (this->dt.size() == 0)
    {
        printf("zahlen_warning(operator=):length==0\n");
        this->dt.resize(1);
    }
    switch (y)
    {
    case 1:
        this->dt[0] = 1;
        break;
    default:
        this->dt[0] = 0;
        break;
    }
}

zahlen operator~(const zahlen &a)
{
    zahlen c(0, a.dt.size());
    for (size_t i = 0; i < a.dt.size(); i++)
    {
        c.dt[i] = 9 - a.dt[i];
    }
    return c;
}
zahlen operator-(const zahlen &a)
{
    zahlen c(0, a.dt.size()), e = 1;
    //(~a).print();
    return (~a) + e;
}
zahlen operator+(const zahlen &a, const zahlen &b)
{
    if (a.dt.size() < b.dt.size())
    {
        return b + a;
    }
    zahlen c(0, a.dt.size()); // aa = a, bb = b;
    c.dt[0] = 0;
    for (int i = 0; i < b.dt.size(); i++)
    {
        if (i < a.dt.size())
        {
            c.dt[i + 1] = (((a.dt[i]) + (b.dt[i]) + (c.dt[i])) / 10);
        }
        c.dt[i] = (((a.dt[i]) + (b.dt[i]) + (c.dt[i])) % 10);
    }
    for (int i = b.dt.size(); i < a.dt.size(); i++)
    {
        if (i < a.dt.size())
        {
            c.dt[i + 1] = (((a.dt[i]) + (c.dt[i])) / 10);
        }
        c.dt[i] = (((a.dt[i]) + (c.dt[i])) % 10);
    }
    return c;
}
zahlen operator*(const zahlen &a, const zahlen &b)
{
    if (a.dt.size() < b.dt.size())
    {
        return b + a;
    }
    zahlen c(0, a.dt.size()); // aa = a, bb = b;
    for (int i = 0; i < b.dt.size(); i++)
    {
        for (int j = 0; j < a.dt.size() - i; j++)
        {
            if (i + j < a.dt.size())
            {
                c.dt[i + j + 1] += (c.dt[i + j] + (a.dt[j] * b.dt[i])) / 10;
            }
            c.dt[i + j] = (c.dt[i + j] + (a.dt[j] * b.dt[i])) % 10;
        }
    }
    return c;
}
