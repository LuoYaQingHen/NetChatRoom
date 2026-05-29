//头文件：MsgType枚举，User类，Message类定义
#ifndef COMMON_H
#define COMMON_H

#include <string>

const int PORT = 8888;

struct ChatMsg
{
    std::string username;
    std::string content;
};

#endif
