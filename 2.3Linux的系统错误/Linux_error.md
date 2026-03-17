**strerror库函数**
strerror在<string.h>中声明，用于获取对应代码相应的错误信息
```
char* error(int errnum);        //线程不安全
int error_r(int errnum, char *buf, size_t buflen);  //线程安全
```
gcc8.3.1一共有*133个错误代码*



s