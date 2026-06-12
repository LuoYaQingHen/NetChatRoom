#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

//Linux头
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//C++头
#include <iostream>
#include <string>
#include <thread>

//与服务端统一端口
constexpr uint16_t SERVER_PORT = 8888;
constexpr int BUF_SIZE = 1024;
constexpr const char* SERVER_IP = "127.0.0.1";
class ChatClient
{
public:
    ChatClient(std::string ip,uint16_t port);
    ~ChatClient();
    //连接服务端
    bool connectServer();
    //启动客户端：收发分离双线程
    void startChat();
private:
    int cli_fd;
    std::string m_server_ip;
    uint16_t m_server_port;
    //子线程：持续接受服务端消息
    void recvMsgLoop();
    //主线程：控制台输入发送消息
    void sendMsgLoop();
};
#endif