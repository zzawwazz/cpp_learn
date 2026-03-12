//假设本程序用于表白，程序运行需要三个参数：追求者姓名，被追求者参数，表白内容。
#include <iostream>
using namespace std;

int main(int argc, char *argv[], char *envp[]){

    cout << "一共有" << argc << "个参数。\n";

    if(argc != 4)
    {
        cout << "本程序的使用方法：./demo 追求者姓名 被追求者参数 表白内容\n";
        return -1;
    }

    if(argc == 4)
    {
        cout << argv[1] << "开始向" << argv[2] << "表白\n";
        cout << argv[3] << endl;
        cout << "表白结束\n";

        return 0;
    }

    //显示所有的参数
    for (int ii = 0; ii < argc ; ii++)
{
    cout << "第" << ii+1 << "个参数：" << argv[ii] << endl;
}


//显示全部的环境变量
//显示的效果与用env命令一样
    for (int ii = 0; envp[ii] != 0 ;ii++)
    {
        cout << envp[ii] << endl;
    }

    setenv("aaa", "123", 0);

    cout << "aaa=" << getenv("aaa") << endl;

    return 0;
}


/*
不管加多少参数都会传进去，其中运行命令本身（./demo）算一个参数
(base) zzaw@DESKTOP-H56O0VV:~/cpp_project/lesson/1.2_function_main$ /home/zzaw/cpp_project/lesson/1.2_function_main/demo aa bb
一共有3个参数。
第1个参数：/home/zzaw/cpp_project/lesson/1.2_function_main/demo
第2个参数：aa
第3个参数：bb
*/