#include "chat_server.h"
constexpr int BUF_SIZE = 1024;
ChatServer::ChatServer(uint16_t port)
    :m_port(port),m_listen_fd(-1){}
ChatServer::~ChatServer()
{
    if(m_listen_fd > 0)
        close(m_listen_fd);
}

bool ChatServer::start()
{
    //创建监听套接字
    m_listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if(m_listen_fd < 0)
    {
        std::cerr<<"socket创建失败"<<std::endl;
        return false;
    }
    //配制服务端地址结构
    sockaddr_in server_addr{};//列表初始化
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    //绑定地址和端口
    if(bind(m_listen_fd,reinterpret_cast<sockaddr*>(&server_addr),sizeof(server_addr)) < 0)
    {
        std::cerr<<"bind绑定失败"<<std::endl;
        close(m_listen_fd);
        m_listen_fd = -1;
        return false;
    }
    //开启监听
    if(listen(m_listen_fd,10) < 0)
    {
        std::cerr<<"listen监听失败"<<std::endl;
        close(m_listen_fd);
        m_listen_fd = -1;
        return false;
    }
    std::cout<<"聊天服务端启动成功，端口："<<m_port<<std::endl;
    //循环接受客户端连接
    while (true)
    {
        sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);
        int connfd = accept(m_listen_fd,reinterpret_cast<sockaddr*>(&client_addr),&len);
        if(connfd < 0)
            continue;
        std::cout<<"新客户端连接："<<inet_ntoa(client_addr.sin_addr)<<"："<<ntohs(client_addr.sin_port)<<std::endl;
        //为每个客户端创建线程，长线程处理
        std::thread(&ChatServer::handleClient,this,connfd).detach();
    }
    return true;
}
 //单个客户端循环处理
void ChatServer::handleClient(int connfd)
{
    char buf[BUF_SIZE]{};
    while (true)
    {
        memset(buf,0,BUF_SIZE);
        int len = recv(connfd,buf,BUF_SIZE - 1,0);
        if(len <= 0)
        {
            std::cout<<"客户端断开连接，fd:"<<connfd<<std::endl;
            close(connfd);
            break;
        }
        std::cout<<"收到消息："<<buf<<std::endl;
        //消息传回客户端
        send(connfd,buf,len,0);
    }
}   
    