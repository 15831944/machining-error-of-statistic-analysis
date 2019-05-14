#include "size_distribution_map.h"
#include <iostream>
#include <cstdlib>
#include <public_function.h>

using namespace std;

void analysis_size_map()
{
    cout << "输入样本数: ";
    //样本数
    int t = 0;
    cin >> t;
    const int n = t;
    int real_data_amount = n;

    cout << "输入数据类型(0:偏差  1:零件尺寸): ";
    int data_type = 0;
    cin >> data_type;
    double avg = 0;
    //标准差
    double standard_deviation = 0;



    double num[n];
    if (data_type == 0)
    {
        cout << "输入基本尺寸: ";
        double standard_size = 0;
        cin >> standard_size;
        cout << endl << "输入数据:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
            num[i] /= 1000;
            num[i] += standard_size;
        }
    }
    else
    {
        cout << endl << "输入数据:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
        }
    }




    //循环足够次数排除异常数据
    for (int x = 0; x < 5; x++)
    {
        avg = Avg(num, n, real_data_amount);
        standard_deviation = Standard_deviation(num, n, avg, real_data_amount);
        for(int i = 0; i < n; ++i)
        {
            if (num[i] == 65535)
                continue;
            if(abs(num[i] - avg) > 3*standard_deviation)
            {
                num[i] = 65535;
                real_data_amount--;
            }
        }
    }
    cout << endl << avg << endl << standard_deviation << endl << endl;





    //组数
    int k = Groups_num(n);
    double max_num =Max_num(num, n);
    double min_num =Min_num(num, n);
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
            if (num[i] > breakpoint[x])
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
            cout << min_num << "-" << breakpoint[i] << "\t" << (breakpoint[i] + min_num) / 2 << "\t\t" << frequency[i] << endl;
        else if (i == k-1)
            cout << breakpoint[i-1] << "-" << max_num << "\t" << (breakpoint[i-1] + max_num) / 2 << "\t\t" << frequency[i] << endl;
        else
            cout << breakpoint[i-1] << "-" << breakpoint[i] << "\t" << (breakpoint[i-1] + breakpoint[i]) / 2 << "\t\t" << frequency[i] << endl;
    }

    cout << endl << "按回车键结束";
    getchar();
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

//-8 -2 -6 -6 -14 -17 -14 -16 -12 -77 -14 -4 7 6 6 6 6 6 -19 -9 -11 6 5 6 4 6 5 -16 -11 -11 7 7 8 6 6 1-10 -6 -8 -15 -15 -15 -16 -15 -14 -6 -6 -6 0 -1 -15 -5 -16 -17 -8 -7 -14 7 7 -16 7 4 2 -14 -3 -10 6 6 -1 6 4 -5 -20 -12 -2 -1 5 7 -1 4 4 3 4 5 6 6 2 4 4 6
//7.92 7.97 7.98 7.99 7.995 8.005 8.018 8.03 8.068 8.142 7.97 7.982 7.991 7.998 8.007 8.04 8.08 8.13 7.965 7.972 7.985 7.992 8 8.01 8.022 8.04 7.957 7.975 7.985 7.992 7.945 8 8.012 8.024 8.045 7.96 7.975 7.994 8.002 8.015 8.024 8.028 7.965 7.98 7.988 7.995 8.004 8.027 8.055 8.017
//6.992 6.998 6.994 6.994 6.986 6.983 6.986 6.984 6.988 6.923 6.986 6.996 7.007 7.006 7.006 7.006 7.006 7.006 6.981 6.991 6.989 7.006 7.005 7.006 7.004 7.006 7.005 6.984 6.989 6.989 7.007 7.007 7.008 7.006 7.006 7.001 6.99 6.994 6.992 6.985 6.985 6.985 6.984 6.985 6.986 6.994 6.994 6.994 7 6.999 6.985 6.995 6.984 6.983 6.992 6.993 6.986 7.007 7.007 6.984 7.007 7.004 7.002 6.986 6.997 6.99 7.006 7.006 6.999 7.006 7.004 6.995 6.98 6.988 6.998 6.999 7.005 7.007 6.999 7.004 7.004 7.003 7.004 7.005 7.006 7.006 7.002 7.004 7.004 7.006
