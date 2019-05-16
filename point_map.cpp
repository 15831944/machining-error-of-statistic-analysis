#include "point_map.h"
#include <iostream>
#include "public_function.h"

using namespace std;

void analysis_point_map()
{
    cout << "共几组: ";
    int q = 0;
    cin >> q;

    cout << "每组有多少数据: ";
    int n = 0;
    cin >> n;

    double size[q][n];

    cout << endl << "输入数据(一次性全部输入):\n";

    for (int i = 0; i < q; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> size[i][j];
        }
        cout << endl;
    }

    //每组数据均值
    double avg_of_q[q];
    //每组数据极差
    double sub_max_min[q];
    for (int i = 0; i < q; i++)
    {
        double max = Max_num(size[i], n);
        double min = Min_num(size[i], n);
        sub_max_min[i] = max - min;
        avg_of_q[i] = Avg(size[i], n, n);
    }

    //均值的均值
    double avg_of_avg = Avg(avg_of_q, q, q);
    //极差均值
    double sub_avg = Avg(sub_max_min, q, q);

    double A2 = 0;
    double d = 0;
    double an = 0;

    switch(n)
    {
    case 4:
    {
        d = 0.88;
        an = 0.486;
        A2 = 0.73;
        break;
    }
    case 5:
    {
        d = 0.864;
        an = 0.43;
        A2 = 0.58;
        break;
    }
    case 6:
    {
        d = 0.848;
        an = 0.395;
        A2 = 0.48;
        break;
    }
    }

    //均值图上限
    double upper_of_total_avg_map = avg_of_avg + A2 * sub_avg;
    //均值图下限
    double lower_of_total_avg_map = avg_of_avg - A2 * sub_avg;
    //极差图上限
    double upper_of_sub_avg_map = sub_avg * (1 + 3 * d * an);
    //极差图下限
    double lower_of_sub_avg_map = sub_avg * (1 - 3 * d * an);
    if (lower_of_sub_avg_map < 0)
        lower_of_sub_avg_map = 0;

    cout << "各组数据均值的均值: " << avg_of_avg << endl
         << "极差平均值: " << sub_avg << endl << endl
         << "均值图上控制限: " << upper_of_total_avg_map << endl
         << "均值图下控制限: " << lower_of_total_avg_map << endl << endl
         << "极差图上控制限: " << upper_of_sub_avg_map << endl
         << "极差图下控制限: " << lower_of_sub_avg_map << endl;

    cout << endl << "按回车键结束";
    getchar();
}

