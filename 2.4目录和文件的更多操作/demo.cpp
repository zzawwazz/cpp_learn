#include<iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include<stdio.h>

using namespace std;



int main(int argc, char *argv[])
{
#if 0
    if (argc != 2) 
    {
        cout << "using by ./demo 文件或目录名\n";
        return -1;
    }

    struct stat st;

    if(stat(argv[1], &st) != 0)
    {
        cout << "stat(" << argv[1] << "):" << strerror(errno) << endl;
        return -1;
    }

    if(S_ISREG(st.st_mode))
    {
        cout << argv[1] << "是一个文件(" << "mtime=" << st.st_mtime << ",size=" << st.st_size << ")\n"; 
    }

    if(S_ISDIR(st.st_mode))
    {
        cout << argv[1] << "是一个目录(" << "mtime=" << st.st_mtime << ",size=" << st.st_size << ")\n"; 
    }
    
#elif 0
    if (argc != 3) 
    {
        cout << "using by ./demo 源文件或目录名 目标文件或目录名\n";
        return -1;
    }
    if(rename(argv[1], argv[2]) != 0)
    {
        struct stat st;

        if(stat(argv[1], &st) != 0)
        {
            cout << "rename(" << argv[1] << "):" << strerror(errno) << endl;
            return -1;
        }

        if(stat(argv[2], &st) != 0)
        {
            cout << "rename(" << argv[2] << "):" << strerror(errno) << endl;
            return -1;
        }

        cout << "rename(" << argv[1] << "):" << strerror(errno) << endl;
        return -1;
    }

#elif 1
    if (argc != 2) 
    {
        cout << "using by ./demo 文件或目录名\n";
        return -1;
    }
    if(remove(argv[1]) != 0)
    {
        cout << "remove(" << argv[1] << "):" << strerror(errno) << endl;
        return -1;
    }


#endif
    return 0;

}