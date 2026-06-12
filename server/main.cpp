//服务端程序入口
#include "chat_server.h"

int main()
{
    constexpr uint16_t SERVER_PORT = 8888;
    ChatServer server(SERVER_PORT);
    if(!server.start())
        return -1;
    return 0;
}