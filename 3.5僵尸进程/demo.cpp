#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

void func(int sig) // 子进程退出的信号处理函数
{
    int sts;
    pid_t pid = wait(&sts); // 子进程退出前阻塞父进程，需要一个整数地址。返回子进程的pid 

    if(WIFEXITED(sts)) // 判断是否正常退出
    {
        cout << "子进程正常退出，退出状态是："  << WEXITSTATUS(sts) << endl; // WEXITSTATUS(sts)获取其退出状态
    }
    else
    {
        cout << "子进程异常退出，终止信号是：" << WTERMSIG(sts) << endl; // 获取其终止信号
    }
}


int main()
{

    #if 0
    if( fork() > 0)
    {
        sleep(20);
        cout << "父进程将退出" << endl;
        return 0;
    }
    else
    {
        for (int ii = 0; ii < 100; ii++)
        {
            cout << "子进程运行中...\n";
            sleep(1);
        }
    }
#elif 0
    if(fork() > 0) return 0; // 父进程比子进程先退出，子进程将被1号进程托管（一种后台运行的办法）

    while(true)
    {
        cout << "服务运行中...\n";
        sleep(1);
    }

#elif 0

    signal(SIGCHLD,SIG_IGN); // 避免僵尸进程1：提前处理内核发来的子进程退出信号。这里采用忽略，意思是我对子进程退出不感兴趣，内核将直接释放子进程的资源.可以通过ps -ef |grep demo查看
    if(fork() == 0) return 0; // 僵尸进程：子进程比父进程先退出，父进程没有处理子进程推出的信息，那么子进程将会成为僵尸进程。

    while(true)
    {
        cout << "父进程运行中...\n";
        sleep(1);
    }

#elif 0

    if(fork() > 0)
    {
        //父进程流程
        int sts;
        // 避免僵尸进程2：使用wait(),传入一个整型地址，用来记录子进程的状态
        pid_t pid = wait(&sts); // 子进程退出前阻塞父进程，需要一个整数地址。返回子进程的pid 

        cout << "已经终止的子进程的编号是：" << pid << endl;
        cout << "sts=" << sts << endl;

        if(WIFEXITED(sts)) // 判断是否正常退出
        {
            cout << "子进程正常退出，退出状态是："  << WEXITSTATUS(sts) << endl; // WEXITSTATUS(sts)获取其退出状态
        }
        else
        {
            cout << "子进程异常退出，终止信号是：" << WTERMSIG(sts) << endl; // 获取其终止信号
        }
    }
    else
    {
        // 子进程流程、
        // sleep(1);
        int *p = 0; *p = 10;
        exit(0);
    }

#elif 1
    signal(SIGCHLD,func); // 避免僵尸进程3：接收处理子进程推出的信号，去回调函数中处理

    if(fork() > 0)
    {
        //父进程的流程
        while(true)
        {
            cout << "父进程忙着执行任务。\n";
            sleep(1);
        }
    }
    else
    {
        //子进程的流程
        sleep(5);
        int *p = 0; *p = 10;
        exit(1);
    }

    #endif
}