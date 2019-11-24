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
    void start();
private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    template <typename Out>
    void split(const std::string &s, char delim, Out result);
    std::vector<std::string> split(const std::string &s, char delim);
};
#endif
