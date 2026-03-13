**一、time_t别名**
    ```time_t```表示时间类型，是一个long类型的别名。
    在<time.h>中定义，表示了从1970年1月1日的0点到现在的秒数
    ```time_t tt;```


**二、time()函数**
    用于获取当前时间，在<time.h>中定义
    声明：
        ```time_t time(time_t *tloc);```
    使用有两种方法：
        1：
        ```time_t now = time(0);```
        将空地址传入，用time_t变量接收返回的当下时间

        2：
        ```
        time_t now;
        time(&now);
        ```
        直接传入接收变量的地址


**三、tm结构体**
    time_t是一个长整型，不适合人类的思维习惯，所以要将其转化为tm结构体，tm结构体在time.h中声明如下：
        ```
        /* ISO C `broken-down time' structure.  */
        struct tm
        {
            int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
            int tm_min;			/* Minutes.	[0-59] */
            int tm_hour;			/* Hours.	[0-23] */
            int tm_mday;			/* Day.		[1-31] */
            int tm_mon;			/* Month.	[0-11] */
            int tm_year;			/* Year	- 1900.  */
            int tm_wday;			/* Day of week.	[0-6] 星期*/
            int tm_yday;			/* Days in year.[0-365]	一年的第几天*/
            int tm_isdst;			/* DST.		[-1/0/1]夏令时标识符，没啥用*/
        }
        ```



**四、localtime()函数**
    localtime()函数可以将time_t数据转化为tm结构体
    localtime()不是线程安全的，localtime_r()是线程安全的
    包含头文件 <time.h>
    函数声明：
        ```
        struct tm *localtime(const time_t *timep);
        struct tm *localtime_r(const time_t *timep, struct tm *result);
        ```


**五、mktime()函数**
    mktime()函数与localtime()函数正相反，用于将tm结构体解析成time_t时间。
    函数声明：
        ```time_t mktime(struct tm *tm)```
    函数主要用于时间的计算，例如将 2022-2-29 23:30:34加三十分钟
    涉及到闰年、零点的进位，同time_t算更方便


**六、gettimeofday()库函数**
    用于计算从1970年1月1日到现在过去了多少秒，和当前秒过去了多少微秒
    头文件：<sys/time.h>
    声明：
    ```int gettimeofday(struct timeval *tv, struct timezone *tz);```
    其中：
    struct timeval{
        time_t tv_sec;//秒
        susecond_t tv_usec;//微秒
    }

    struct timezone//时区信息不用管


**七、程序睡眠**
    如果你要将程序挂起一段时间，可以使用sleep()和usleep()两个库函数
    包含头文件<unistd.h>
    函数声明：
        ```unsigned int sleep(unsigned int seconds);```
        ```int usleep(usecond_t usec); ```
