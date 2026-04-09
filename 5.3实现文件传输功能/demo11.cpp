/*
 * 程序名：demo11.cpp，此程序用于演示文件传输的客户端。
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
#include <fstream>
using namespace std;
 
class ctcpclient
{
public:
  int m_clientfd;// 客户端的socket，-1表示未连接或连接已断开；>=0表示有效的
  string m_ip;// 服务端的IP/域名。
  unsigned short m_port;// 通讯端口

  ctcpclient() : m_clientfd(-1) {}

  // 向服务端发起连接请求，成功返回true，失败返回false
  bool connect(const string &in_ip, const unsigned short in_port)
  {
    if (m_clientfd != -1) return false; // 如果socket已连接，直接返回失败
    
    m_ip = in_ip; m_port = in_port; //把服务端的IP和端口保存到成员变量中
      // 第1步：创建客户端的socket。  
    if((m_clientfd = socket(AF_INET,SOCK_STREAM,0)) == -1) return false;
  
    // 第2步：向服务器发起连接请求。 
    struct sockaddr_in servaddr;               // 用于存放协议、端口和IP地址的结构体。
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;             // ①协议族，固定填AF_INET。
    servaddr.sin_port = htons(m_port);  // ②指定服务端的通信端口。

    struct hostent* h;                         // 用于存放服务端IP地址(大端序)的结构体的指针。
    if ( (h = gethostbyname(m_ip.c_str())) == nullptr )  // 把域名/主机名/字符串格式的IP转换成结构体。
    { 
      close(); m_clientfd = -1; return false;
    }
    memcpy(&servaddr.sin_addr,h->h_addr,h->h_length); // ③指定服务端的IP(大端序)。
    
     // 向服务端发起连接清求。
     /*  error: no matching function for call to ‘ctcpclient::connect(int&, sockaddr*, long unsigned int)’
        解决方法：
        在前面加上::,即"::connect()"*/
    if (::connect(m_clientfd,(struct sockaddr *)&servaddr,sizeof(servaddr))==-1) 
    { 
      close(); m_clientfd = -1; return false;
    }
    return true;
  }

  // 向服务端发送请求报文成功返回true，失败返回false。
  bool send(const string &buffer) // buffer不要用const char *
  //const char *不支持c风格的string，而const string &buffer既支持char也支持string
  {
    if (m_clientfd == -1) return false;// 如果socket的状态是未连接，直接返回失败

    if ( (::send(m_clientfd,buffer.data(),buffer.size(),0))<=0) // buffer是string，用成员函数获取首地址
      return false;
    return true;
  }


  // 重写send，向服务端发送请求报文(二进制)成功返回true，失败返回false。
  bool send(const void *buffer, size_t size) 
  {
    if (m_clientfd == -1) return false;

    if ( (::send(m_clientfd,buffer,size,0))<=0) 
      return false;
    return true;
  }

  // 接收服务端的回应报文，如果服务端没有发送回应报文，recv()函数将阻塞等待。
  // buffer-存放接收到的报文的内容，maxlen-本次接收报文的最大长度
  bool recv(string &buffer, const size_t maxlen)
  {// 如果直接操作string对象的内存，必须保证：1)不能越界；2）操作后手动设置数据的大小。
    buffer.clear();         // 清空容器。
    buffer.resize(maxlen);  // 设置容器的大小为maxlen。
    int readn = ::recv(m_clientfd, &buffer[0], buffer.size(), 0 );  // 直接操作buffer的内存。
    if (readn <= 0) { buffer.clear(); return false;} // ::recv()返回-1失败0断开连接>0成功 
    buffer.resize(readn);   // 重置buffer的实际大小。

    return true;
  }

  bool close()
  {
    if (m_clientfd == -1) return -1;
     ::close(m_clientfd);
     m_clientfd = -1;
     return true;
  }



  bool sendfile(const string &filename, const size_t filesize)
  {
    ifstream fin(filename, ios::binary);
    if(fin.is_open() == false) {cout << "打开文件失败" << filename << "失败\n"; return false;}
    
    int onread; // 每次调用fin.read()时打算读取的字节数        本次应该搬多少砖头
    int totalbytes = 0; //  从文件中已读取的字节总数               已搬砖头
    char buffer[4096]; // 存放读取数据的buffer                一次搬7块砖头

    while(true)
    {
      memset(&buffer, 0, sizeof(buffer));
      // 计算本次应该读取的字节数，如果剩余的数据超过4096字节，就读4096字节。
      if((filesize-totalbytes) > 4096) {onread = 4096;}
      else onread = filesize - totalbytes;

      //从文件中读取数据
      fin.read(buffer, onread);

      //发送数据
      if(send(&buffer, onread) == false) {return false;}

      // 计算文件已读取的字节总数，如果文件已读完，跳出循环。
      totalbytes += onread;
      if (totalbytes == filesize) break;
    }

    return true;
  }

  ~ctcpclient() { close(); }


};


int main(int argc,char *argv[])
{
  if (argc!=5)
  {
    cout << "Using:./demo11 服务端的IP 服务端的端口 文件名 文件大小\n";
    cout << "Example:./demo11 0.0.0.0 5005 aaa.txt 70\n\n";
    return -1;
  }


  ctcpclient tcpclient;
  if (tcpclient.connect(argv[1], atoi(argv[2])) == false) 
  {
    perror("connect()");
    return -1;
  }
  
  //以下是发送文件的流程
  // 1)	把待传输文件名和文件的大小告诉服务端。
  struct st_fileinfo
  {
    char filename[256]; // 文件名
    int filesize;       // 文件大小
  }fileinfo;

  memset(&fileinfo, 0, sizeof(fileinfo));
  strcpy(fileinfo.filename,argv[3]);
  fileinfo.filesize = atoi(argv[4]);
  if (tcpclient.send(&fileinfo, sizeof(fileinfo)) == false)
  {
    perror("send"); return -1;
  }
  cout << "发送文件信息的结构体" << fileinfo.filename << "(" << fileinfo.filesize << ")\n";




  // 2)	等待服务端的确认报文(文件名和文件的大小的确认).	
  string buffer;
  if (tcpclient.recv(buffer, 2) == false) {perror("recv"); return -1;}
  if (buffer != "ok") {cout << "服务端没有返回ok\n"; return -1;}
  // 3)发送文件内容。


  if(tcpclient.sendfile(fileinfo.filename, fileinfo.filesize) == false)
  {
    perror("filesend()"); return -1;
  }

  // 4)等待服务端的确认报文(服务端已接收完文件).
  
  if (tcpclient.recv(buffer,2) == false) {perror("recv()"); return -1;}
  if (buffer != "ok") {cout << "发送文件失败！\n"; return -1;}


  cout << "发送文件成功！\n";




}
