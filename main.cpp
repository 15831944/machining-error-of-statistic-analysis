#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

//数组求和
double Sum(double num[], int n, double standard_size);
//平方和
double Sum_of_squares(double num[], int n);
//求分组数
int Groups_num(int n);
double Max_num(double num[], int n);
double Min_num(double num[], int n);

int main()
{
    //工件的标准长度
    double standard_size = 7;
    //样本数
    int n = 0;
    cin >> n;
    double sum = 0;
    double avg = 0;
    double sum_of_squares = 0;
    //标准差
    double standard_deviation = 0;



    double num[n];
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        num[i] /= 1000;
    }




    //循环足够次数排除异常数据
    for (int x = 0; x < 5; x++)
    {
        sum = Sum(num, n, standard_size);
        avg = sum / n;
        sum_of_squares = Sum_of_squares(num, n);
        standard_deviation = sqrt(sum_of_squares / n);
        for(int i = 0; i < n; ++i)
        {
            if (num[i] == 65535)
                continue;
            if(abs(num[i]) > 3*standard_deviation)
            {
                num[i] = 65535;
                n--;
            }
        }
    }
    cout << endl << avg << endl << standard_deviation << endl << endl;





    //组数
    int k = Groups_num(n);
    double max_num = standard_size + Max_num(num, n);
    double min_num = standard_size + Min_num(num, n);
    //组之间的间距
    double h = (max_num - min_num) / k;

    //组别分界值
    double breakpoint[k-1];
    for (int i = 0; i < k-1; i++)
    {
        breakpoint[i] = min_num + (i + 1) * h;
    }
    //各组频数
    int frequency[k];
    for (int i = 0; i < k; i++)
        frequency[i] = 0;


    //计算各组频数
    for(int i = 0; i < n; i++)
    {
        if(num[i] == 65535)
            continue;
        for (int x = k-2; x >= 0; x--)
        {
            if ((standard_size + num[i]) > breakpoint[x])
            {
                frequency[x+1]++;
                break;
            }
            if (x == 0)
                frequency[0]++;
        }
    }

    //输出各组频数
    for (int i = 0; i < k; i++)
    {
        if (i == 0)
            cout << min_num << "-" << breakpoint[i] << ": " << frequency[i] << endl;
        else if (i == k-1)
            cout << breakpoint[i-1] << "-" << max_num << ": " << frequency[i] << endl;
        else
            cout << breakpoint[i-1] << "-" << breakpoint[i] << ": " << frequency[i] << endl;
    }
}

double Sum(double num[], int n, double standard_size)
{
    double r = 0;
    for (int i = 0; i < n; ++i)
    {
        if(num[i] == 65535)
            continue;
        r += (standard_size + num[i]);
    }
    return r;
}

double Sum_of_squares(double num[], int n)
{
    double r = 0;
    for (int i = 0; i < n; ++i)
    {
        if(num[i] == 65535)
            continue;
        r += num[i]*num[i];
    }
    return r;
}

int Groups_num(int n)
{
    if (n > 630)
        return 15;
    else if (n > 400)
        return 14;
    else if (n > 250)
        return 13;
    else if (n > 160)
        return 12;
    else if (n > 100)
        return 11;
    else if (n == 100)
        return 10;
    else if (n > 60)
        return 8;
    else if (n > 40)
        return 7;
    else
        return 6;
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
        if (min > num[i])
            min = num[i];
    }
    return min;
}


//-8 -2 -6 -6 -14 -17 -14 -16 -12 -77 -14 -4 7 6 6 6 6 6 -19 -9 -11 6 5 6 4 6 5 -16 -11 -11 7 7 8 6 6 1-10 -6 -8 -15 -15 -15 -16 -15 -14 -6 -6 -6 0 -1 -15 -5 -16 -17 -8 -7 -14 7 7 -16 7 4 2 -14 -3 -10 6 6 -1 6 4 -5 -20 -12 -2 -1 5 7 -1 4 4 3 4 5 6 6 2 4 4 6
