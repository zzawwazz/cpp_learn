// 这样写头文件是非常不专业的
// #include "/home/zzaw/cpp_project/lesson/tools/public.h"
// #include "/home/zzaw/cpp_project/lesson/api/myapi.h"

//应该这样
#include "public.h"
#include "myapi.h"
// 直接编译会报错
/*
demo.cpp:6:10: fatal error: public.h: No such file or directory
    6 | #include "public.h"
      |          ^~~~~~~~~~
compilation terminated.
*/
// 编译时加上\I参数，后接头文件的目录
// g++ -o demo demo.cpp -L/home/zzaw/cpp_project/lesson/tools -lpublic -L/home/zzaw/cpp_project/lesson/api -lmyapi -I/home/zzaw/cpp_project/lesson/tools -I/home/zzaw/cpp_project/lesson/api


using namespace std;

int main()
{
	cout << "Hello World!\n";
	func1();
	func(); // 调用通用函数

	AA a; // 用通用类声明对象
	BB b;
	a.show(); // 调用对象的方法
	b.show();
}
