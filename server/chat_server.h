//对Linux
#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H


#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include<thread>
//Linux网络系统头
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class ChatServer
{
public:
    explicit ChatServer(uint16_t);
    ~ChatServer();
    bool start();
private:
    uint16_t m_port;
    int m_listen_fd;
    void handleClient(int connfd);
};
#endif //CHAT_SEVER_H