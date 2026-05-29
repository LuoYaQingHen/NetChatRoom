#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include <vector>
//用户管理类模块
class UserManager
{
public:
    //添加在线用户
    void addUser (const std::string& name);
    //移除离线用户
    void removeUser (const std::string& name);
    //判断用户是否存在
    bool isUserExist (const std::string& name);
private:
    std::vector<std::string> onlineUsers; //在线用户列表;
};
#endif