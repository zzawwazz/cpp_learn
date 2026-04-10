/*
 *  程序名：demo10.cpp，此程序演示开发框架中删除字符串左、右、两边指定字符的使用方法。
 *  作者：吴从周
*/
#include <string>
#include <cstring>
#include <iostream>
using namespace std;



char * deletelchr(char * str, const int cc)
{
    if (str == nullptr) return nullptr;
    char* p = str;
    // while(true)
    // {
    //     if (*p == cc) p++;
    //     else break;
    // }
    while(*p == cc)
        p++;
    memmove(str, p,strlen(str)-(p-str) + 1);


    return str;


}




string& deletelchr(string &str, const int cc)
{
    auto p  = str.find_first_not_of(cc);
    if (p != 0) str.replace(0, p, "");

    return str;
}




char * deleterchr(char * str, const int cc)
{
    if (str == nullptr) return nullptr;
    char* p = str;
    char* pass = 0;

    while(*p != 0)
    {
        if(*p == cc && pass == 0) pass = p;
        if(*p != cc) pass = 0;
        p++;
    }
    if(pass != 0) *pass = 0;

    return str;

}


string& deleterchr(string &str, const int cc)
{
    auto p = str.find_last_not_of(cc);
    if (p != 0) str.erase(p+1, string::npos);

    return str;
}

char * deletelrchr(char* str,const int cc)
{
    str = deletelchr(str,cc);
    str = deleterchr(str,cc);
    return str;

}

string& deletelrchr(string & str,const int cc)
{
    str = deletelchr(str,cc);
    str = deleterchr(str,cc);
    return str;

}



int main()
{
    char str1[31];        // C风格的字符串。
    string str2;            // C++风格的字符串。

    strcpy(str1,"  西施  ");
    deletelchr(str1,' ');                // 删除str1左边的空格
    printf("str1=%s=\n",str1);    // 出输结果是str1=西施  =

    str2="  西施  ";
    deletelchr(str2,' ');
    cout << "str2=" << str2 << "=\n";

    strcpy(str1,"  西施  ");
    deleterchr(str1,' ');                // 删除str1左边的空格
    printf("str1=%s=\n",str1);    // 出输结果是str1=西施  =

    str2="  西施  ";
    deleterchr(str2,' ');
    cout << "str2=" << str2 << "=\n";

    strcpy(str1,"  西施  ");
    deletelrchr(str1,' ');               // 删除str1两边的空格
    printf("str1=%s=\n",str1);    // 出输结果是str1=西施=

    str2="  西施  ";
    deletelrchr(str2,' ');
    cout << "str2=" << str2 << "=\n";

}
