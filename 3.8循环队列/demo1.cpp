/*
共享内存不能自动扩展，只能采用c++内置的数据类型
共享内存不能采用STL容器，也不能使用移动语义
如果要实现多进程的生产\消费者模型，只能采用循环队列
*/


//本程序演示循环队列的使用
#include "_public.h"


int main()
{
    using ElemType = int;

    squeue<ElemType,5> QQ;

    ElemType ee; //创建一个数据元素

    cout << "元素 1 、 2 、 3 入队\n";
    ee = 1; QQ.push(ee);
    ee = 2; QQ.push(ee);
    ee = 3; QQ.push(ee);

    cout << "队列的长度为：" << QQ.size() << endl;
    QQ.printqueue();
    
    ee = QQ.front(); QQ.pop(); cout << "出队的元素值为：" << ee << endl;
    ee = QQ.front(); QQ.pop(); cout << "出队的元素值为：" << ee << endl;
    
    cout << "队列的长度是" << QQ.size() << endl;
    
    ee = 11; QQ.push(ee);
    ee = 12; QQ.push(ee);
    ee = 13; QQ.push(ee);
    ee = 14; QQ.push(ee);
    ee = 15; QQ.push(ee);

    
    cout << "队列的长度是" << QQ.size() << endl;
    QQ.printqueue();

    return 0;

}