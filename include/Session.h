#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "Action.h"

class User;
class Watchable;
class Session{
public:
    Session(const std::string &configFilePath);
    // ~Session();
    void addUserToUserMap(std::string,User*);
    void start();
    std::string getUserInput() const;
    void setUserInput(std::string);
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    std::string userInput;
    void addDataToContentFromJsonFilePath(const std::string &configFilePath);
};
#endif
