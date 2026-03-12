#include "public.h"
using namespace std;
//通用函数实现
void func()
{
	cout << "升级了调用了func()函数。\n";
}

//通用类实现
void AA::show()
{
	cout << "升级了你好鸟！\n";
}

// 静态库的制作
//g++ -c -o libpublic.a public.cpp
//编译静态库指令
//-c：只编译链接
//-o：指定名称
// libpublic.a：命名：lib前缀，public库名，.a表示静态库

// 静态库的使用
//g++ -o demo demo.cpp -L/home/zzaw/cpp_project/lesson/tools/libpublic.a -lpublic
// -L 要链接的库的地址路径
// -l 要链接的库名，但是不要加lib，例如libpublic.a不要加lib

//动态库的制作
// g++ -fPIC -shared -o libpublic.so public.cpp
// -fPIC -shared代表制作动态库
// -o libpublic.so库名

// 动态库的使用
// g++ -o demo demo.cpp -L/home/zzaw/cpp_project/lesson/tools -lpublic
//！！！但是报错：./demo: error while loading shared libraries: libpublic.so: cannot open shared object file: No such file or directory
// 原因：系统去默认的目录找了，所以找不到。
// 解决办法：我们将新编写的动态库加入进环境变量中
// eg： export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/zzaw/cpp_project/lesson/tools
// 查看环境变量： echo $LD_LIBRARY_PATH
// 好处：1.运行时才链接2.多个进程共享避免空间浪费	3！！！！！.更新程序时不用全部重新编译，只要更新动态库就行了
// 静态库动态库同时存在，系统优先使用静态库