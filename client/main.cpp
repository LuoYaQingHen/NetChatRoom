//客户端程序入口
#include "chat_client.h"

int main()
{
    const std::string SERVER_IP = "127.0.0.1";
    const uint16_t SERVER_PORT = 8888;

    ChatClient client(SERVER_IP,SERVER_PORT);
    if(!client.connectServer())
        return -1;
    std::cout<<"请输入消息（输入q退出聊天室）："<<std::endl;
    client.startChat();
    return 0;
}