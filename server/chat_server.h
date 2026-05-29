//对Linux
#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H


#include <iostream>
#include <cstring>

//Linux网络系统头
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

//常量定义
constexpr unsigned short SERVER_PORT = 8888;
constexpr int BUF_SIZE = 1024;
//启动TCP服务端
void StartChatSever();
#endif //CHAT_SEVER_H