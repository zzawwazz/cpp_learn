#include <cstring>
#include <string>
#include <unistd.h>
#include <iostream>
using namespace std;



void bb(const int bh,const string sa)
{
    for(int ii=0;ii < 1000000; ii++)
    {
        sleep(1);
        cout << "ii=" << ii << endl;
    }
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