#include<iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

#if 0

void func(int signum)
{
    cout << "收到了信号" << signum << endl;
    // signal(signum,SIG_DFL); // 恢复信号的处理方法为默认行为
}

void func1(int signum)
{
    cout << "闹钟响了，执行定时任务\n";
    alarm(5);
}

int main()
{
    signal(1,func);// 收到信号时回调func函数， 回调时将信号编号传递给func
    signal(15,func);
    signal(9,func); // 信号9无法被捕获与忽略，代号是AEF
    signal(2,SIG_IGN);// 忽略信号
    signal(14,func1); // 闹钟的回调函数


    alarm(5); // 闹钟（定时器），5s后像本程序发送14的信号

    while(1)
    {
        cout << "执行了一次命令\n";
        sleep(1);
    }

    return 0;
}


#elif 1

void EXIT(int signum)
{
    cout << "收到了信号：" << signum << endl;
    cout << "正在释放资源，程序将退出......\n";

    //...

    cout << "程序退出" << endl;
    exit(0);
}


int main(int argc, char *argv[])
{
    // 忽略全部信号，防止程序被意外终止
    for (int ii=1; ii <= 64; ii++)
    {
        signal(ii, SIG_IGN);
    }

    signal(2,EXIT);
    signal(15,EXIT);

    while(1)
    {
        cout << "执行了一次命令\n";
        sleep(1);
    }
}

#endif