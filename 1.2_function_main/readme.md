main函数有三个参数，argc、argv和envp，它的标准写法如下:
int main(int argc,char *argv[],char *envp[])
{
    return O;
}


argc存放了程序参数的个数，包括程序本身。
argv字符串的数组，存放了每个参数的值，包括程序本身。
envp字符串的数组，存放了环境变量，数组的最后一个元素是空。
在程序中，如果不关心main()函数的参数，可以省略不写。




cpp中设置环境变量：#include <stdlib.h>
    int setenv(const char *name, const char *value, int overwrite);
    name    环境变量名。
    value   环境变量的值。
overwrite   0-如果环境不存在，增加新的环境变量，如果环境变量已存在，不替换其值;非0-如果环境不存在，增加新的环境变量，如果环境变量已存在，替换其值。
    返回值:0-成功;-1-失败(失败的情况极少见)。
    注意:此函数设置的环境变量只对本进  程有效，不会影响shell的环境变量。如果在运行程序时执行了setenv()函数，进程终止后再次运行该程序，上次的设置是无效的。

获取环境变量
char *getenv(const char *name);