#include <iostream>

using namespace std;

void func1()
{
    cout <<"调用了func1\n";
    // exit(0); // 不会回到main函数
    return; // 会回到main函数  
}


void func2()
{
    cout <<"调用了func2\n";
    func1();
    cout << "回到了func2\n";
}



int main(int argc, char *argv[])
{
    // func2();
    // cout << "回到了main函数\n";

    atexit(func1);
    atexit(func2);// atexit用来登记终止函数（最多32个），最终在使用return或者exit时调用，但是_exit不会调用
    

    // return 1; // echo $?可以查看主函数的返回状态
    exit(0); // 不会调用局部对象的析构函数，只会调用全局对象的析构函数
    _exit(1); // 带下划线的两个函数不会执行任何清理工作
    _Exit(3); // 参数即为返回的状态
}