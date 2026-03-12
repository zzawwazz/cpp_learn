#include <cstring>
#include <string>
using namespace std;



void bb(const int bh,const string sa)
{
    char *ptr = nullptr;
    // *ptr = 3;//本行会发生内存泄漏
    strcpy(ptr,sa.c_str());//本行会发生内存泄漏
}

void aa(const int no,const string name)
{
    bb(3,"vv");
}

int main()
{
    aa(1,"11");
    return 0;
}