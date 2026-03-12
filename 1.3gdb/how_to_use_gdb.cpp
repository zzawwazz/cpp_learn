#include <iostream>
using namespace std;


void show (const char*name1,const char*name2, const char *message)
{
    cout << name1 << "开始向" << name2 << "表白\n";
    cout << name1 << ":" << message << endl;
}


int main(int argc, char *argv[], char *envp[]){

    if(argc != 4)
    {
        cout << "本表白神器程序的使用方法：./demo 追求者姓名 被追求者参数 表白内容\n";
        return -1;
    }

    cout << "表白前的准备工作1\n";
    cout << "表白前的准备工作2\n";
    cout << "表白前的准备工作3\n";
    cout << "表白前的准备工作4\n";
    cout << "表白前的准备工作5\n";

    show(argv[1], argv[2], argv[3]);

    cout << "表白完成" << endl;

    for(int ii = 0;ii < 10 ;ii++)
    {
        string str = "这是第"+ to_string(ii) + "个超人";
        cout << str << endl;
    }

    return 0;
}
//编译命令：g++ -o demo demo.cpp -g
//调试命令：gdb demo
//