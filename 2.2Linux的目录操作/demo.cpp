#include<iostream>
#include<dirent.h>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2) 
    {
        cout << "using as './demo 目录名称'\n";
        return -1;
    }

    DIR *dir;//定义目录指针
    
    if((dir = opendir(argv[1])) == 0) return -1;

    struct dirent *stdinfo = nullptr;

    while(1)
    {
        if ((stdinfo = readdir(dir)) == nullptr) break;

        cout << "文件名称" << stdinfo->d_name << "," << "文件类型" << (int)stdinfo->d_type << endl;
    }

    closedir(dir);

    return 0;



}