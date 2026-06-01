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
    //端口复用
    int opt = 1;
    setsockopt(listen_fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    //配制服务端地址结构
    sockaddr_in server_addr{};//列表初始化
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //绑定地址和端口
    if(bind(listen_fd,reinterpret_cast<sockaddr*>(&server_addr),sizeof(server_addr)) < 0)
    {
        std::cerr<<"bind绑定失败"<<std::endl;
        close(listen_fd);
        return;
    }
    //开启监听
    if(listen(listen_fd,5) < 0)
    {
        std::cerr<<"listen监听失败"<<std::endl;
        close(listen_fd);
        return;
    }
    std::cout<<"聊天服务端启动成功，端口："<<SERVER_PORT<<std::endl;
    std::cout<<"等待客户端连接"<<std::endl;
    //循环接受客户端连接
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    while(true)
    {
        //阻塞等待客户端连接
        int client_fd = accept(listen_fd,reinterpret_cast<sockaddr*>(&client_addr),&client_len);
        if(client_fd < 0)
        {
            std::cerr<<"accept接收失败"<<std::endl;
            continue;
        }
        //解析客户端 IP + 端口
        char client_ip[32]{};
        inet_ntop(AF_INET,&client_addr.sin_addr,client_ip,sizeof(client_ip));
        unsigned short client_port = ntohs(client_addr.sin_port);
        std::cout<<"新客户端接入"<<client_ip<<":"<<client_port<<std::endl;
        //接收客户端数据
        char recv_buf[BUF_SIZE]{};
        ssize_t recv_len = recv(client_fd,recv_buf,BUF_SIZE - 1,0);
        if(recv_len > 0)
        {
            std::cout<<"收到消息："<<recv_buf<<std::endl;
            //回显数据给客户端
            send(client_fd,recv_buf,recv_len,0);
        }
        else if(recv_len == 0)
            std::cout<<"客户端"<<client_ip<<"："<<client_port<<"已断开连接"<<std::endl;
        else
            std::cerr<<"recv接收数据出错"<<std::endl;
        //关闭客户端套接字
        close(client_fd);    
    }
    close(listen_fd);
}