/*
 * 程序名：demo12.cpp，此程序用于演示文件传输的服务端。
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fstream>
using namespace std;




class ctcpserver
{
private:
int m_listenfd;
int m_clientfd;
string m_clientip;
string client_ip;
unsigned short m_port;

public:

  ctcpserver() : m_listenfd(-1),m_clientfd(-1) {}

  bool initserver(const unsigned short in_port)
  {
    if(m_listenfd != -1) return false;

    m_port = in_port;

      // 第1步：创建服务端的socket。 
    if((m_listenfd = socket(AF_INET,SOCK_STREAM,0)) == -1) return false;

    
    // 第2步：把服务端用于通信的IP和端口绑定到socket上。 
    struct sockaddr_in servaddr;                // 用于存放协议、端口和IP地址的结构体。
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;                // ①协议族，固定填AF_INET。
    servaddr.sin_port=htons(m_port);     // ②指定服务端的通信端口。
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY); // ③如果操作系统有多个IP，全部的IP都可以用于通讯。
    //servaddr.sin_addr.s_addr=inet_addr("192.168.101.138"); // ③指定服务端用于通讯的IP(大端序)。
    // 绑定服务端的IP和端口。
    if (bind(m_listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1)
    { 
      close(m_listenfd); return false; 
    }
  
    // 第3步：把socket设置为可连接（监听）的状态。
    if (::listen(m_listenfd,5) == -1 ) 
    { 
      close(m_listenfd); m_listenfd = -1;return false; 
    }

    return true;
  }

  bool accept()
  {
    struct sockaddr_in caddr; // 客户端的地址信息
    socklen_t addrlen = sizeof(caddr);// struct sockaddr_in的大小
    // 第4步：受理客户端的连接请求，如果没有客户端连上来，accept()函数将阻塞等待。
    if((m_clientfd=::accept(m_listenfd,(sockaddr *)&caddr,&addrlen)) == -1) return false; 

    m_clientip = inet_ntoa(caddr.sin_addr); //// 把大端序IP转换成字符串格式的IP，用于在服务端程序中解析客户端的IP地址

    cout << "客户端已连接。（" << clientip() << "）\n";

    return true;
  }

  //获取客户端的IP括号(字符串格式)
  const string & clientip() const
  {
    return m_clientip;
  }

  bool recv(string &buffer, const size_t maxlen)
  {

    buffer.clear();
    buffer.resize(maxlen);
    // 接收客户端的请求报文，如果客户端没有发送请求报文，recv()函数将阻塞等待。
    // 如果客户端已断开连接，recv()函数将返回0。
    int readn = ::recv(m_clientfd,&buffer[0],buffer.size(),0);
    if (readn<=0) 
    {
      buffer.clear(); return false;
    }

    buffer.resize(readn);
  
    cout << "接收：" << buffer << endl;

    return true;
  }


  // 重写recv函数,接收客户端的请求报文，如果客户端没有发送请求报文，recv()函数将阻塞等待。
  bool recv(void *buffer,const size_t size)
  {
    // 如果客户端已断开连接，recv()函数将返回0。
    if(::recv(m_clientfd,buffer,size,0) == -1)
      return false;
    return true;
  }

  bool send(const string &buffer)
  {
        if(m_clientfd == -1) return false;
    // 向客户端发送回应报文。
    if ( (::send(m_clientfd,buffer.data(),buffer.size(),0))<=0) 
    { 
       return false; 
    }
    
    cout << "发送：" << buffer << endl;

    return true;
  }

  bool closeclient()
  {
    if (m_clientfd==-1) return false;
    ::close(m_clientfd);
    m_clientfd = -1;
    return true;
  }

  bool closelisten()
  {
    if (m_listenfd==-1) return false;
    ::close(m_listenfd);
    m_listenfd = -1;
    return true;
  }

  bool recvfiles(const string &filename, const size_t filesize)
  {
    ofstream fout;
    fout.open(filename, ios::binary);
    if (fout.is_open() == false) {cout << "打开文件" << filename << "失败。\n"; return false;}

    int totalbytes = 0;
    int nread;
    char buffer[7];

    while(true)
    {
      
      if (filesize - totalbytes > 7) nread = 7;
      else nread = filesize - totalbytes;

      if (recv(buffer,nread) == false) return false;

      fout.write(buffer,nread);

      totalbytes += nread;
      if (totalbytes == filesize) break;

    }
    return true;



  }

  ~ctcpserver() 
  {
    // 第6步：关闭socket，释放资源。
    closelisten();   // 关闭客户端连上来的socket。
    closeclient();   // 关闭服务端用于监听的socket。
  }
};

void FathEXIT(int sig);  // 父进程的信号处理函数。
void ChldEXIT(int sig);  // 子进程的信号处理函数。

ctcpserver tcpserver;

 
int main(int argc,char *argv[])
{
  if (argc!=3)
  {
    cout << "Using:./demo12 通讯端口 文件存放的目录\n";
    cout << "Example:./demo12 5005 /tmp\n\n";
    cout << "注意：运行服务端程序的Linux系统的防火墙必须要开通5005端口。\n";
    cout << "      如果是云服务器，还要开通云平台的访问策略。\n\n";
    return -1;
  }


  // 忽略全部的信号，不希望被打扰。
  for (int ii=1;ii<=64;ii++) signal(ii,SIG_IGN);

  // 设置信号,在shell状态下可用 "kill 进程号" 或 "Ctrl+c" 正常终止些进程
  // 但请不要用 "kill -9 +进程号" 强行终止
  signal(SIGTERM,FathEXIT); signal(SIGINT,FathEXIT);  // SIGTERM 15 SIGINT 2




  if(tcpserver.initserver(atoi(argv[1])) == false) 
  {
    perror("initserver"); return -1;
  }



  while(true)
  {

    
    if (tcpserver.accept() == false) 
    {
      perror("accept()");return -1;
    }

    int pid = fork();
    if (pid == -1) {perror("fork()"); return -1;}
    // 父进程只负责与客户端连接，子进程只负责与客户端通信
    // 父进程不需要clientfd，子进程不需要listenfd
    if (pid > 0) 
    {
      //父进程流程
      tcpserver.closeclient();
      continue;
    }

    //子进程流程
    tcpserver.closelisten();

      // 子进程需要重新设置信号。
    signal(SIGTERM,ChldEXIT);   // 子进程的退出函数与父进程不一样。
    signal(SIGINT ,SIG_IGN);    // 子进程不需要捕获SIGINT信号。

    //以下是接收文件的流程
    //1)接收文件名和文件大小信息。
    struct st_fileinfo
      {
        char filename[256]; // 文件名
        int filesize;       // 文件大小
      }fileinfo;

    memset(&fileinfo, 0, sizeof(fileinfo));

    if(tcpserver.recv(&fileinfo, sizeof(fileinfo)) == false) {perror("send"); return -1;}
    cout << "文件信息的结构体" << fileinfo.filename << "(" << fileinfo.filesize << ")\n";




    //2)给客户端回复确认报文，表示客户端可以发送文件了。
    if (tcpserver.send("ok") == false) {perror("send"); return -1;}

    //3)接收文件内容。
    /*
    demo12.cpp: In function ‘int main(int, char**)’:
demo12.cpp:265:36: error: invalid operands of types ‘char*’ and ‘const char [2]’ to binary ‘operator+’
  265 |     if( tcpserver.recvfiles(argv[2]+"/"+fileinfo.filename, fileinfo.filesize) == false)
      |                             ~~~~~~~^~~~
      |                                   | |
      |                                   | const char [2]
      |                                   char*
make: *** [makefile:9: demo12] Error 1

原因：char * + const char * + char * 导致报错
只有string可以使用 +
所以将其中一个修改为string就可以了
    */
    if( tcpserver.recvfiles(string(argv[2])+"/"+fileinfo.filename, fileinfo.filesize) == false)
      cout << "接受文件失败！\n";
    cout << "接受文件成功！\n";


    //4)给客户端回复确认报文，表示文件已接收成功。
    tcpserver.send("ok");


    
    
    return 0; // 子进程一定要退出,否则又会回到accept()的位置
  }
    
}

// 父进程的信号处理函数。
void FathEXIT(int sig)
{
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

  cout << "父进程退出，sig=" << sig << endl;

  kill(0,SIGTERM);     // 向全部的子进程发送15的信号，通知它们退出。

  // 在这里增加释放资源的代码（全局的资源）。

  tcpserver.closelisten();

  

  exit(0);
}

// 子进程的信号处理函数。
void ChldEXIT(int sig)
{
  // 以下代码是为了防止信号处理函数在执行的过程中再次被信号中断。
  signal(SIGINT,SIG_IGN); signal(SIGTERM,SIG_IGN);

  cout << "子进程" << getpid() << "退出，sig=" << sig << endl;

  // 在这里增加释放资源的代码（只释放子进程的资源）。

  tcpserver.closeclient();

  exit(0);
}

  