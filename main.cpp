#include <iostream>
#include "public_function.h"
#include "size_distribution_map.h"
#include "point_map.h"


using namespace std;

int main()
{
    cout << "0:分布图    1:点图\n"
         << "输入序号: ";
    int type = 0;
    cin >> type;
    cout << endl;

    if (type == 0)
        analysis_size_map();
    else
        analysis_point_map();
}
