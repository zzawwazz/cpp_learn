**获取当前目录**
```
#include<unistd.h>
char path1[256];//Linux系统定义的最大长度为256
getcwd(path1,256);

char* path2 = get_current_dir_name();//动态分配内存
cout...
free(path2);//因为是使用malloc创建的空间，要用free释放掉。new的才用delete
```


**切换工作目录**
```
#include<unistd.h>
int chdir(const char *path)；
```
返回0成功，其他失败


**创建目录**
```
#include<sys/stat.h>
int mkdir(const char *pathname,mode_t mode);
```
pathname 目录名
mode 权限：比如0755，不能省略0.
返回0成功其他失败，比如没有前置目录等等。。。


**删除目录**
```
#include<unistd.h>
int rmdir(const char *path);
```
成功返回0，失败其他


**demo中用的是对目录中文件的操作**