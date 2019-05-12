#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

//数组求和
double Avg(double num[], int n, int real_number);
//平方和
double Standard_deviation(double num[], int n, double avg, int real_number);
//求分组数
int Groups_num(int n);
double Max_num(double num[], int n);
double Min_num(double num[], int n);

int main()
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
    double sum = 0;
    double avg = 0;
    //标准差
    double standard_deviation = 0;



    double num[n];
    if (data_type == 0)
    {
        cout << "输入基本尺寸: ";
        double standard_size = 0;
        cin >> standard_size;
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
            num[i] /= 1000;
            num[i] += standard_size;
        }
    }
    else
    {
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
    
    cout << "按回车键结束";
    getchar();
}

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
        if(num[i] == 65535)
            continue;
        if (min > num[i])
            min = num[i];
    }
    return min;
}
