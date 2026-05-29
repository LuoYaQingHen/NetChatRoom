#include "chat_server.h"

void StartChatSever()
{
    //创建监听套接字
    int listen_fd = socket(AF_INET,SOCK_STREAM,0);
    if(listen_fd < 0)
    {
        std::cerr<<"socket创建失败"<<std::endl;
        return;
    }
}