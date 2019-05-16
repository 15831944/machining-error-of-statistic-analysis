#include "point_map.h"
#include <iostream>
#include "public_function.h"

using namespace std;

void analysis_point_map()
{
    cout << "������: ";
    int q = 0;
    cin >> q;

    cout << "ÿ���ж�������: ";
    int n = 0;
    cin >> n;

    double size[q][n];

    cout << endl << "��������(һ����ȫ������):\n";

    for (int i = 0; i < q; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> size[i][j];
        }
        cout << endl;
    }

    //ÿ�����ݾ�ֵ
    double avg_of_q[q];
    //ÿ�����ݼ���
    double sub_max_min[q];
    for (int i = 0; i < q; i++)
    {
        double max = Max_num(size[i], n);
        double min = Min_num(size[i], n);
        sub_max_min[i] = max - min;
        avg_of_q[i] = Avg(size[i], n, n);
    }

    //��ֵ�ľ�ֵ
    double avg_of_avg = Avg(avg_of_q, q, q);
    //�����ֵ
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

    //��ֵͼ����
    double upper_of_total_avg_map = avg_of_avg + A2 * sub_avg;
    //��ֵͼ����
    double lower_of_total_avg_map = avg_of_avg - A2 * sub_avg;
    //����ͼ����
    double upper_of_sub_avg_map = sub_avg * (1 + 3 * d * an);
    //����ͼ����
    double lower_of_sub_avg_map = sub_avg * (1 - 3 * d * an);
    if (lower_of_sub_avg_map < 0)
        lower_of_sub_avg_map = 0;

    cout << "�������ݾ�ֵ�ľ�ֵ: " << avg_of_avg << endl
         << "����ƽ��ֵ: " << sub_avg << endl << endl
         << "��ֵͼ�Ͽ�����: " << upper_of_total_avg_map << endl
         << "��ֵͼ�¿�����: " << lower_of_total_avg_map << endl << endl
         << "����ͼ�Ͽ�����: " << upper_of_sub_avg_map << endl
         << "����ͼ�¿�����: " << lower_of_sub_avg_map << endl;

    cout << endl << "���س�������";
    getchar();
}

