#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include "Action.h"

class User;
class Watchable;

class Session{
public:
    // Constructor
    Session(const std::string &configFilePath);
    // Destructor
    ~Session();
    // Copy Constructor
    Session(const Session &other);
    // Move Constructor
    Session(Session &&other);
    // Copy Assignment
    Session& operator=(const Session &other);
    // Move Assignment
    Session& operator=(Session &&other);
    void start();
    void setActiveUser(User*);
    User* getActiveUser();
    bool userExist(std::string userName);
    void addUserToUserMap(std::string, User*);
    User* getUserFromUserMap(std::string);
    void deleteUser(std::string);
    std::vector<Watchable*>& getContent();
    std::vector<BaseAction*>& getActionsLog();
    void addToLog(BaseAction*);
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    void copy(const Session &other);
    void clean();
    void addDataToContentFromJsonFilePath(const std::string &configFilePath);
};
#endif
