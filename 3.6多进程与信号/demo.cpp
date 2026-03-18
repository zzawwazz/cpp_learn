#include <iostream>
#include <signal.h>
#include <unistd.h>
using namespace std;



void ChildEXIT(int sig);
void FathEXIT(int sig);

int main()
{
    // 忽略所有信号，防止被干扰
    for (int ii = 0 ;ii < 64; ii ++)
        signal(ii, SIG_IGN);
    
    signal(SIGTERM,FathEXIT); // SIGTERM 15
    signal(SIGINT,FathEXIT); // SIGINT 2

    while(true)
    {
        if(fork() > 0)
        {
            sleep(5); continue;
        }
        else
        {
            signal(SIGTERM, ChildEXIT);
            signal(SIGINT, SIG_IGN);

            while(true)
            {
                cout << "子进程正在运行中....pid = " << getpid() << endl;
                sleep(3);
                continue;
            }

        }
    }




}

void FathEXIT(int sig)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);

    cout << "父进程退出...   sig= " << sig << endl;
    kill(0,SIGTERM);
    // 释放资源代码...

    exit(0);

}


void ChildEXIT(int sig)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, SIG_IGN);

    cout << "子进程正在退出。。。pid = " << getpid() << endl;
    // 释放资源代码...

    exit(0);
}