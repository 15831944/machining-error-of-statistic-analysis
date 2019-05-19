#include "size_distribution_map.h"
#include <iostream>
#include <cstdlib>
#include "public_function.h"
#include <fstream>
#include <cmath>

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
    //组数
    int k = Groups_num(n);
    //组别分界值
    double breakpoint[k-1];
    //各组频数
    int frequency[k];
    for (int i = 0; i < k; i++)
        frequency[i] = 0;



    double num[n];
    if (data_type == 0)
    {
        cout << "输入基本尺寸: ";
        double standard_size = 0;
        cin >> standard_size;
        cout << endl << "输入数据,单位微米:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
            num[i] /= 1000;
            num[i] += standard_size;
        }
    }
    else
    {
        cout << endl << "输入数据,单位毫米:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
        }
    }

    ofstream data;
    data.open("分布图具体数据.txt");
    if (data)
    {
        data.setf(ios::fixed, ios::floatfield);
        data.precision(4);
        data << "零件尺寸:\n";
        for (int i = 0; i < n; i++)
        {
            data << num[i] << " ";
        }
        data << endl << endl;

        //循环足够次数排除异常数据
        for (int x = 0; x < 5; x++)
        {
            data << "第" << x+1 << "次:\n";
            avg = Avg(num, n, real_data_amount);
            data << "平均值: " << avg << endl;
            standard_deviation = Standard_deviation(num, n, avg, real_data_amount);
            data << "标准差: " << standard_deviation << endl << "异常数据: ";
            for(int i = 0; i < n; ++i)
            {
                if (num[i] == -255)
                    continue;
                if(abs(num[i] - avg) > 3*standard_deviation)
                {
                    data << i << " " << num[i] << "\t";
                    num[i] = -255;
                    real_data_amount--;
                }
            }
            data << endl << endl;
        }

        data << "最终平均值: " << avg << endl
             << "最终标准差: " << standard_deviation << endl << endl;





        double max_num =Max_num(num, n);
        double min_num =Min_num(num, n);
        //组之间的间距
        double h = (max_num - min_num) / k;

        for (int i = 0; i < k-1; i++)
        {
            breakpoint[i] = min_num + (i + 1) * h;
        }


        //计算各组频数
        for(int i = 0; i < n; i++)
        {
            if(num[i] == -255)
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
                data << min_num << "-" << breakpoint[i] << "\t" << (breakpoint[i] + min_num) / 2 << "\t\t" << frequency[i] << endl;
            else if (i == k-1)
                data << breakpoint[i-1] << "-" << max_num << "\t" << (breakpoint[i-1] + max_num) / 2 << "\t\t" << frequency[i] << endl;
            else
                data << breakpoint[i-1] << "-" << breakpoint[i] << "\t" << (breakpoint[i-1] + breakpoint[i]) / 2 << "\t\t" << frequency[i] << endl;
        }
    }
    data.close();




    double max_num =Max_num(num, n);
    double min_num =Min_num(num, n);
    ofstream fout;
    fout.open("size_map.dat");
    if (fout)
    {
        fout.setf(ios::fixed, ios::floatfield);
        fout.precision(4);
        //各组边界
        fout << min_num << " ";
        for (int i = 0; i < k-1; i++)
        {
            fout << breakpoint[i] << " ";
        }
        fout << max_num << endl;

        //y坐标
        for (int i = 0; i < k; i++)
            fout << frequency[i] << " ";

        // 平均值
        fout << endl << avg;
    }
    fout.close();
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
