#ifndef __PUBLIC_HH
#define __PUBLIC_HH 1

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
using namespace std;


// 循环队列
template<class TT, int MaxLength>
class squeue
{
private:
    bool m_inited; //初始化标志，true已被初始化
    TT m_data[MaxLength];
    int m_head;
    int m_tail;
    int m_length;
    squeue(const squeue &) = delete;
    squeue &operator=(const squeue &) = delete;

public:
    squeue() {init();}

    // 对循环队列进行初始化操作
    // 注：如果用于共享内存的队列，不会调用构造函数，必须调用此函数初始化
    void init()
    {
        if (m_inited != true)
        {
            m_head = 0;
            m_tail = MaxLength - 1;
            m_length = 0;
            memset(m_data, 0, sizeof(m_data));
            m_inited = true;
        }
    }

    // 元素入队，返回值：false失败，true成功
    bool push(const TT &ee)
    {
        if (full() == true)
        {
            cout << "循环队列已满，入队失败\n";
            return false;
        }

        m_tail = (m_tail + 1) % MaxLength;
        m_data[m_tail] = ee;
        m_length++;

        return true;
    }

    // 求循环队列的长度，返回值：>=0-队列中元素的个数
    int size()
    {
        return m_length;
    }

    //判断循环是否为空
    int empty()
    {
        if(m_length == 0) return true;
        return false;
    }

    // 判断循环队列是否已满，返回值：true已满
    bool full()
    {
        if (m_length == MaxLength) return true;
        return false;
    }

    // 查看队头元素的值
    TT& front()
    {
        return m_data[m_head];
    }

    //元素出队，false失败
    bool pop()
    {
        if(empty() == true) 
        {
            cout << "循环队列为空，出队失败！\n";
            return false;
        }
        m_head = (m_head + 1) % MaxLength;
        m_length--;

        return true;
    }

    //显示循环队列中全部的元素
    //这是一个临时的用于调试的函数，队列中元素的数据类型支持cout输出才可用
    void printqueue()
    {
        for (int ii = 0;ii < size(); ii++)
        { 
            cout << "m_data[" << (m_head+ii) % MaxLength << "],value=" \
            << m_data[(m_head+ii) % MaxLength]  << endl;
        }
    }
};

// 信号量
class csemp
{
private:
    union semun // 用于信号量操作的共同体
    {
        int val;
        struct semid_ds *buf;
        unsigned short *arry;
    };

    int   m_semid; // 信号量id(描述符)

    /*
    如果把sem_flg设置为SEM_UNDO，操作系统将跟踪进程对信号量的修改情况，
    在全部修改过信号量的进程(正常或异常)终止后，操作系统将把信号量恢
    复为初始值(就像撤消了全部进程对信号的操作)。
    如果信号量用于互斥锁，设置为SEM_UNDO。
    如果信号量用于生产消费者模型，设置为0。*/
    short m_sem_flg;

    csemp(const csemp &) = delete; // 禁用拷贝构造函数
    csemp &operator = (const csemp &) = delete; // 禁用赋值函数
public:
    csemp():m_semid(-1) {} // 初始化semid为-1，如果为-1说明之前不存在，存在则id >= 0
    // 如果信号量已存在，获取信号量；如果信号量不存在，则创建它并初始化值为value。
    // 如果用于互斥锁，value填1，sem_flg填SEM_UNDO。
    // 如果用于生产消费者模型，value填0，sem_flg填0。
    bool init(key_t key, unsigned short value=1, short sem_flg=SEM_UNDO);
    bool wait(short sem_op=-1);    // 信号量的P操作。信号量的值-value。信号量的值大于0，wait立即返回。信号量的值小于0，立即阻塞等待
    bool post(short sem_op=1);    // 信号量的V操作。信号量的值+value
    int getvalue();    // 获取信号量的值，成功返回信号量的值，失败返回-1。
    bool destroy();    // 销毁信号量。
    ~csemp();
    
};


#endif