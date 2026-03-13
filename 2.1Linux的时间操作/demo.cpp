#include <iostream>
#include <sys/time.h>
#include <unistd.h>

using namespace std;

#if 0

int main()
{
    time_t now1;
    long now2;

    now1 = time(0);
    time(&now2);

    cout << "now1=" << now1 << endl;
    cout << "now2=" << now2 << endl;

    return 0;
}
#elif 0

int main()
{
    time_t now = time(0);
    cout << "now=" << now << endl;

    tm tmnow;
    localtime_r(&now, &tmnow);

    string stime = to_string(tmnow.tm_year + 1900) + "-" + to_string(tmnow.tm_mon + 1) + "-" + to_string(tmnow.tm_mday) + " 周" + to_string(tmnow.tm_wday) + " " + to_string(tmnow.tm_hour) + ":" + to_string(tmnow.tm_min) + ":" + to_string(tmnow.tm_sec) ;

    cout << "当前时间为：" << stime << endl;

    return 0;
}

#elif 1

int main()
{
    timeval start,end;
    gettimeofday(&start,0);//开始计时

    for (int ii= 0; ii < 999999; ii++);
    sleep(4);
    gettimeofday(&end,0);// 计时结束

    timeval tv;
    tv.tv_sec = end.tv_sec-start.tv_sec;
    tv.tv_usec = end.tv_usec-start.tv_usec;
    
    if(tv.tv_usec < 0)
    {
        tv.tv_usec = 1000000 - tv.tv_usec;
        tv.tv_sec--;
    }

    cout << "耗时" << tv.tv_sec << "秒和" << tv.tv_usec << "微秒。" << endl;




}


#endif

