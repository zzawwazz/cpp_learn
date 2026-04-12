/*
 *  程序名：demo16.cpp，此程序演示开发框架中picknumber函数的使用。
 *  作者：吴从周
*/

#include <string>
#include <iostream>
#include <cstring>
using namespace std;
string& picknumber(const string& src, string& dest,const bool bsigned,const bool bdot)
{

    string str;
    for (auto cc:src)
    {
        if((bsigned == true) && (cc == '+' || cc == '-'))
            {str.append(1,cc); continue;}

        if((bdot == true) && (cc == '.'))
            {str.append(1,cc); continue;}
        if(isdigit(cc)) str.append(1,cc); 
    }
    dest = str;
    return dest;
}

string picknumber(const string& src,const bool bsigned,const bool bdot)
{
    string dest;
    picknumber(src, dest, bsigned, bdot);
    return dest;
}


char * picknumber(const string &src, char* dest, const bool bsigned, const bool bdot)
{
    if (dest == nullptr) return nullptr;
    string str = picknumber(src,bsigned,bdot);
    str.copy(dest, str.length());
    dest[str.length()] = 0;
    return dest;
}


int main()
{
    char str1[30];   
    string str2;

    strcpy(str1,"iab+12.3xy");
    picknumber(str1,str1,false,false);
    printf("str1=%s=\n",str1);    // 出输结果是str1=123=

    str2="iab+12.3xy";
    picknumber(str2,str2,false,false);
    cout << "str2=" << str2 << "=\n";  // 出输结果是str2=123=

    strcpy(str1,"iab+12.3xy");
    picknumber(str1,str1,true,false);
    printf("str1=%s=\n",str1);         // 出输结果是str1=+123=

    str2="iab+12.3xy";
    picknumber(str2,str2,true,false);
    cout << "str2=" << str2 << "=\n";  // 出输结果是str2=+123=

    strcpy(str1,"iab+12.3xy");
    picknumber(str1,str1,true,true);
    printf("str1=%s=\n",str1);         // 出输结果是str1=+12.3=

    str2="iab+12.3xy";
    picknumber(str2,str2,true,true);
    cout << "str2=" << str2 << "=\n";  // 出输结果是str2=+12.3=
}

