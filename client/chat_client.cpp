#include "chat_client.h"
#include <cerrno>
#include <cstring>

ChatClient::ChatClient(std::string ip,uint16_t port)
    : m_server_ip(std::move(ip)),m_server_port(port),cli_fd(-1) {}
ChatClient::~ChatClient()
{
    if(cli_fd > 0)
        close(cli_fd);
}

bool ChatClient::connectServer()
{
    // 创建socket
    cli_fd = socket(AF_INET,SOCK_STREAM,0);
    if(cli_fd < 0)
    {
        std::cerr<<"客户端socket创建失败:"<<strerror(errno)<<std::endl;
        return false;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(m_server_port);
    server_addr.sin_addr.s_addr = inet_addr(m_server_ip.c_str());
    //连接服务端
    int ret = connect(cli_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(ret < 0)
    {
        std::cerr<<"连接服务端失败："<<strerror(errno)<<std::endl;
        close(cli_fd);
        cli_fd = -1;
        return false;
    }
    std::cout<<"✅成功连接聊天服务端（"<<SERVER_IP<<":"<<SERVER_PORT<<"），开始聊天"<<std::endl;
    return true;
}
//子线程循环接收服务端发来的数据
void ChatClient::recvMsgLoop()
{
    char buf[1024] = {0};
    while(true)
    {
        memset(buf,0,sizeof(buf));
        int len = recv(cli_fd,buf,sizeof(buf) - 1,0);
        if(len > 0)
        {
            std::cout<<"\n【收到】："<<buf<<std::endl;
            std::cout<<">";
            std::cout.flush();
        }
        else if(len == 0)
        {
            std::cout<<"\n❌服务端断开连接，客户端退出"<<std::endl;
            close(cli_fd);
            exit(0);
        }
        else
        {
            std::cerr<<"\n❌接收消息失败"<<std::endl;
            close(cli_fd);
            exit(1);
        }
    }
}
//主线程读取控制台输入，发送消息
void ChatClient::sendMsgLoop()
{
    std::string input;
    while(true)
    {
        std::cout<<">";
        std::getline(std::cin,input);
        if(input == "q")
        {
            std::cout<<"客户端主动退出"<<std::endl;
            close(cli_fd);
            exit(0);
        }
        send(cli_fd,input.c_str(),input.length(),0);
    }
}

void ChatClient::startChat()
{
    //新线程收消息，主线程发消息
    std::thread recvThread(&ChatClient::recvMsgLoop,this);
    recvThread.detach();
    sendMsgLoop();
}