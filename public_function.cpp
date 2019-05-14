#include "public_function.h"
#include <cmath>

double Avg(double num[], int n, int real_number)
{
    double r = 0;
    for (int i = 0; i < n; ++i)
    {
        if(num[i] == 65535)
            continue;
        r += num[i];
    }
    return r/real_number;
}

double Standard_deviation(double num[], int n, double avg, int real_number)
{
    double r = 0;
    for (int i = 0; i < n; ++i)
    {
        if(num[i] == 65535)
            continue;
        r += (num[i] - avg) * (num[i] - avg);
    }
    return sqrt(r/real_number);
}

double Max_num(double num[], int n)
{
    double max = num[0];
    for (int i = 1; i < n; i++)
    {
        if(num[i] == 65535)
            continue;
        if (max < num[i])
            max = num[i];
    }
    return max;
}

double Min_num(double num[], int n)
{
    double min = num[0];
    for (int i = 1; i < n; i++)
    {
        if(num[i] == 65535)
            continue;
        if (min > num[i])
            min = num[i];
    }
    return min;
}
