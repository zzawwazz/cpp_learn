//信号量本质上是一个非负数的计数器
//用于给共享资源建立一个标志，表示该共享资源被占用的情况

/*
信号量的两种操作
1。P操作（wait）将信号量的值减1，如果信号量的值为0；将阻塞等待，知道信号量的值大于0
2.Vcaozuo（post）将信号量的值加1，任何时候都不会阻塞。*/

/*
信号量的使用场景：
如果约定信号量的取值只是0和1（0表示资源不可用，1表示资源可用），可以实现互斥锁
如果约定信号量的取值表示可用资源的数量，可以实现生产/消费者模型*/

//demo3.cpp 本程序演示用信号量给共享内存加锁

#include "_public.h"

struct stgirl
{
    int no;
    char name[51];
};



int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Using by ./demo No name\n";
        return -1;
    }
    int shmid = shmget(0x5005, sizeof(stgirl), 0640|IPC_CREAT);
    if ( shmid == -1)
    {
        //第1步：创建/获取共享内存，键值key为0x5005，也可以使用其他的值。也可以使用十进制，但是可读性差
        cout << "shmget(0x5005) failed.\n";
        return -1;
    }
    cout << "shmid=" << shmid << endl;

    //第二步：将共享内存连接到当前进程的地址空间
    stgirl *ptr = (stgirl*)shmat(shmid, 0, 0);
    if(ptr == (void *)-1)
    {
        cout << "shmat() failed. \n";
        return -1;
    }


    //这里准备对共享内存加锁
    // 创建、初始化二元信号量
    csemp mutex;
    if(mutex.init(0x5005) == false)
    {
        cout << "mutex.init(0x5005) failed.\n";
        return -1;
    }

    cout << "申请加锁...\n";
    mutex.wait(); //申请加锁
    cout << "申请加锁成功。\n";

    //第三步：使用共享内存，对共享内存进行读/写
    cout << "原值：no=" << ptr->no << ",name=" << ptr->name << endl;
    ptr->no = atoi(argv[1]);//atoi(argv[1]) 将这个字符串转换为整数（例如将 "123" → 123）
    strcpy(ptr->name,argv[2]);
    cout << "新值：no=" << ptr->no << ",name=" << ptr->name << endl;
    sleep(20);
    
    mutex.post(); // 解锁
    cout << "解锁。\n";

    //第四步：把共享内存从当前进程中分离
    shmdt(ptr);

    
}
