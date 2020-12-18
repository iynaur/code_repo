#include <iostream>
#include <iomanip>
using namespace std;

inline int test_float( void )
{
    const double value = 12.3456789;

    cout << value << endl; // 默认以6精度，所以输出为 12.3457
    cout << setprecision(4) << value << endl; // 改成4精度，所以输出为12.35
    cout << setprecision(8) << value << endl; // 改成8精度，所以输出为12.345679
    cout << fixed << setprecision(4) << value << endl; // 加了fixed意味着是固定点方式显示，所以这里的精度指的是小数位，输出为12.3457
    cout << value << endl; // fixed和setprecision的作用还在，依然显示12.3457
    cout.unsetf( ios::fixed ); // 去掉了fixed，所以精度恢复成整个数值的有效位数，显示为12.35
    cout << value << endl;
    cout.precision( 6 ); // 恢复成原来的样子，输出为12.3457
    cout << value << endl;
    cout<<fixed<<value<<endl;
    cout<<showpos<<value<<endl; //整数后面要加+号
    cout.unsetf( ios::showpos ); //取消
    cout<<scientific<<value<<endl;//科学计数法

    cout<<uppercase<<value<<endl;//使用大写字符
    cout.unsetf( ios::uppercase );//取消

}
