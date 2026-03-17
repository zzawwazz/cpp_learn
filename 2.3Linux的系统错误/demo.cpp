#if 0
#include<iostream>
#include<string.h>
using namespace std;

int main()
{
    int ii = 0;

    for ( ;ii < 150; ii++)
    {
        cout << ii << ":" << strerror(ii) << endl;
    }
    return 0;
}

#elif 0
#include <iostream>
#include <sys/stat.h>
#include<string.h>
using namespace std;

int main()
{

    int iret = mkdir("/tmp/aaa/bbb/ccc/ddd" , 0755);
    cout << "iret=" << iret << endl;
    cout << "error=" <<  strerror(errno) << endl;//errno是程序执行时就设置的全局变量

    return 0;
}

#elif 1
#include <iostream>
#include <sys/stat.h>
#include<cstring>
#include<cerrno>
using namespace std;

int main()
{
    int iret = mkdir("tmp/aaa/vv/dd/dd/ss", 0755);

    cout  << "iret=" << iret << endl;
    cout << errno << ":" << strerror(errno) << endl;
    perror("调用mkdir(tmp/aaa/vv/dd/dd/ss)失败");

    /*输出：
    iret=-1
    2:No such file or directory
    调用mkdir(tmp/aaa/vv/dd/dd/ss)失败: No such file or directory
    */
}


#endif