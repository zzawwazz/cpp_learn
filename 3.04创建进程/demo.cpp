#include<iostream>
#include <unistd.h>
#include <fstream>

using namespace std;


int main()
{

#if 0
    //这是fork的第一种用法：父进程复制自己，然后分别执行不同的代码
    int bh = 8;
    string message = "你好鸟。";
    //fork后父子进程的执行顺序是不一定的
    pid_t  pid = fork(); // 创建一个新进程，创建的进程称为子进程
    //fork调用一次，返回两次。子进程返回0，父进程返回子进程id
    cout << "pid=" << pid << endl;
    if (pid > 0)
    {
        sleep(1);
        //父进程执行这一段
        cout << "嗷嗷父进程！！" << bh << "号，" << message << endl;
        // sleep(10);
        cout << "父进程程序结束" << endl;
    }
    else
    {
        //子进程与父进程共享数据空间，但是只是复制父进程的堆栈等，无法与父进程共享
        bh = 3; message = "一点也不好";
        //子进程执行这一段
        cout << "嗷嗷子进程！！" << bh << "号，" << message << endl;
        // sleep(10);
        cout << "子进程程序结束" << endl;
    }

#elif 0

    //fork的第二种用法：子进程执行另一个程序
    if(fork() > 0)
    {
        //父进程执行这一段
        while(true)
        {
            sleep(1);
            cout << "父进程执行中...\n";
        }
    }
    else{
        //子进程执行这一段
        cout << "子进程开始执行任务..." << endl;
        execl("/bin/ls", "/bin/ls", "It", "/tmp", 0);

    }


#elif 1

    ofstream fout;
    fout.open("/tmp/tmp.txt");//打开文件
    fork();//fork的一个特性是在父进程中打开的文件描述符都会被复制进子进程中，父进程和子进程共享同一个文件偏移量
    for (int ii = 0; ii < 1000000; ii++)
    {
        fout << "进程" << getpid() << "西西" << ii << "很漂亮" << "\n";
    }

    fout.close();

    //vfork()调用和返回和fork()相同，但是含义不同。
    //vfork()用于创建一个新进程，目的是exec一个新程序，不复制父进程的地址空间。
    //还有一个区别，vfork()保证子进程先运行，子进程调用exec或exit()之后父进程才恢复运行。


#endif


    return 0;


}
