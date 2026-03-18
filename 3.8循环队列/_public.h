#include <iostream>
#include <string.h> 
using namespace std;
// 循环队列
template<class TT, int MaxLength>
class squeue
{
private:
    bool m_inited; //初始化标志，true已被初始化
    int m_data[MaxLength];
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