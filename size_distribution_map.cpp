#include "size_distribution_map.h"
#include <iostream>
#include <cstdlib>
#include <public_function.h>

using namespace std;

void analysis_size_map()
{
    cout << "����������: ";
    //������
    int t = 0;
    cin >> t;
    const int n = t;
    int real_data_amount = n;

    cout << "������������(0:ƫ��  1:����ߴ�): ";
    int data_type = 0;
    cin >> data_type;
    double avg = 0;
    //��׼��
    double standard_deviation = 0;



    double num[n];
    if (data_type == 0)
    {
        cout << "��������ߴ�: ";
        double standard_size = 0;
        cin >> standard_size;
        cout << endl << "��������:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
            num[i] /= 1000;
            num[i] += standard_size;
        }
    }
    else
    {
        cout << endl << "��������:\n";
        for (int i = 0; i < n; i++)
        {
            cin >> num[i];
        }
    }




    //ѭ���㹻�����ų��쳣����
    for (int x = 0; x < 5; x++)
    {
        avg = Avg(num, n, real_data_amount);
        standard_deviation = Standard_deviation(num, n, avg, real_data_amount);
        for(int i = 0; i < n; ++i)
        {
            if (num[i] == -255)
                continue;
            if(abs(num[i] - avg) > 3*standard_deviation)
            {
                num[i] = -255;
                real_data_amount--;
            }
        }
    }
    cout << endl
         << "ƽ��ֵ: " << avg << endl
         << "��׼��: " << standard_deviation << endl << endl;





    //����
    int k = Groups_num(n);
    double max_num =Max_num(num, n);
    double min_num =Min_num(num, n);
    //��֮��ļ��
    double h = (max_num - min_num) / k;

    //���ֽ�ֵ
    double breakpoint[k-1];
    for (int i = 0; i < k-1; i++)
    {
        breakpoint[i] = min_num + (i + 1) * h;
    }
    //����Ƶ��
    int frequency[k];
    for (int i = 0; i < k; i++)
        frequency[i] = 0;


    //�������Ƶ��
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

    //�������Ƶ��
    for (int i = 0; i < k; i++)
    {
        if (i == 0)
            cout << min_num << "-" << breakpoint[i] << "\t" << (breakpoint[i] + min_num) / 2 << "\t\t" << frequency[i] << endl;
        else if (i == k-1)
            cout << breakpoint[i-1] << "-" << max_num << "\t" << (breakpoint[i-1] + max_num) / 2 << "\t\t" << frequency[i] << endl;
        else
            cout << breakpoint[i-1] << "-" << breakpoint[i] << "\t" << (breakpoint[i-1] + breakpoint[i]) / 2 << "\t\t" << frequency[i] << endl;
    }

    cout << endl << "���س�������";
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
