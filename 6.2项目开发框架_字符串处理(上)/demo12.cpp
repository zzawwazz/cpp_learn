/*
 *  程序名：demo12.cpp，此程序演示开发框架中字符串大小写转换函数的使用。
 *  作者：吴从周
*/
/*
A-Z 65-90
a-z 97-122
*/
#include <string.h>
#include <string>
#include <iostream>
using namespace std;
char* toupper(char * str)
{
    if(str == nullptr) return nullptr;
    char * p = str;
    while(*p != 0)
    {
        if (*p >='a' && *p <= 'z')
            *p -= 32;
        p++;
    }
    return str;
}


char* tolower(char * str)
{
    if(str == nullptr) return nullptr;
    char * p = str;
    while(*p != 0)
    {
        if (*p >='A' && *p <= 'Z')
            *p += 32;
        p++;
    }
    return str;
}

string& toupper(string & str)
{
    for(auto &cc:str)
        if (cc >='a' && cc <= 'z') cc -= 32;
    return str;
}

string& tolower(string & str)
{
    for(auto &cc:str)
        if (cc >='A' && cc <= 'Z') cc += 32;
    return str;
}




int main()
{
    char str1[31];   // C风格的字符串。

    strcpy(str1,"12abz45ABz8西施。");
    toupper(str1);                       // 把str1中的小写字母转换为大写。
    printf("str1=%s=\n",str1);    // 出输结果是str1=12ABZ45ABZ8西施。=

    strcpy(str1,"12abz45ABz8西施。");
    tolower(str1);                       // 把str1中的大写字母转换为小写。
    printf("str1=%s=\n",str1);    // 出输结果是str1=12abz45abz8西施。=

    string str2;    // C++风格的字符串。
  
    str2="12abz45ABz8西施。";
    toupper(str2);                                    // 把str2中的小写字母转换为大写。
    cout << "str2=" << str2 << "=\n";   // 出输结果是str2=12ABZ45ABZ8西施。=

    str2="12abz45ABz8西施。";
    tolower(str2);                                     // 把str2中的大写字母转换为小写。
    cout << "str2=" << str2 << "=\n";   // 出输结果是str1=12abz45abz8西施。=
}