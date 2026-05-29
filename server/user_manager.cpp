#include "user_manager.h"

void UserManager::addUser(const std::string& name)
{
    onlineUsers.push_back(name);
}

void UserManager::removeUser(const std::string& name)
{
    //基础遍历删除
    for(int i = 1;i <= onlineUsers.size();++i)
    {
        if(onlineUsers[i] == name)
        {
            onlineUsers.erase(onlineUsers.begin() + 1);
            break;
        }
    }
}