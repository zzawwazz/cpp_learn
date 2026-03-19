#include<unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#if 0
int main(int argc, char *argv[])
{
    //system新进程的进程编号与原进程不同
    cout << "demo的进程编号是：" << getpid() << endl;
    int ret = system("/home/zzaw/cpp_project/lesson/3.3调用可执行程序/demo3");
    cout << "ret=" << ret << endl;
    perror("system");
}

#elif 0
int main(int argc, char *argv[])
{
/*
    //execl新进程的进程编号与原进程相同，但是新进程取代了原进程的代码段、数据段和堆栈
    int ret = execl("/bin/ls", "/bin/ls", "-It", "/tmp", 0);//(路径，命令，可变参数，0表示参数已结束)
    cout << "ret=" << ret << endl;
    perror("excel");
*/
    //execl新进程的进程编号与原进程相同，但是新进程取代了原进程的代码段、数据段和堆栈,不会接着执行
    cout << "demo的进程编号是：" << getpid() << endl;  
    int ret = execl("/home/zzaw/cpp_project/lesson/3.3调用可执行程序/demo3", "/home/zzaw/cpp_project/lesson/3.3调用可执行程序/demo3", 0);    
    cout << "ret=" << ret << endl;
    perror("execl");




    return 0;
}


#elif 1
int main(int argc, char *argv[])
{
    char *args[10];
    args[0] = (char *)"/bin/ls";
    args[1] = (char *)"-It";
    args[2] = (char *)"/tmp";
    args[3] = 0; // 0不能省略
    int ret = execv("/bin/ls", args);
    cout << "ret=" << ret << endl;
    perror("execv");


}


#endif