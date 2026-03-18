//共享内存：允许多个进程访问同一块地址空间，但是没有锁机制。如果要加锁，可以使用    信号量
// ipcs -m可以查看系统中的共享内存
// ipcrm -m 1 可以手动删除共享内存
#include <iostream>
#include <sys/shm.h>
#include <string.h>

using namespace std;





struct stgirl
{
    int no;//编号
    char name[51];//姓名，注意不能用string,因为string会动态分配内存，再分配的不属于共享内存

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

    //第三步：使用共享内存，对共享内存进行读/写
    cout << "原值：no=" << ptr->no << ",name=" << ptr->name << endl;
    ptr->no = atoi(argv[1]);//atoi(argv[1]) 将这个字符串转换为整数（例如将 "123" → 123）
    strcpy(ptr->name,argv[2]);
    cout << "新值：no=" << ptr->no << ",name=" << ptr->name << endl;
    

    //第四步：把共享内存从当前进程中分离
    shmdt(ptr);

    //第五步：删除共享内存
    if(shmctl(shmid,IPC_RMID,0) != 0)
    {
        cout << "stmctl(" << shmid << "):failed.\n";
    }
    else
    {
        cout << "已经删除共享内存，id=" << shmid << endl;
    }
}
