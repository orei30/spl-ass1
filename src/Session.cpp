#include "../include/Session.h"
#include "../include/json.hpp"
#include "../include/Watchable.h"
#include "../include/User.h"

using namespace std;

//Constructor
Session::Session(const string &configFilePath) : content(), actionsLog(), userMap(), activeUser(new LengthRecommenderUser("default")) {
    userMap.insert({"default", activeUser});
    addDataToContentFromJsonFilePath(configFilePath);
}

// Destructor
Session::~Session() {
    clean();
}

// Copy Constructor
Session::Session(const Session &other) : content(), actionsLog(), userMap(), activeUser() {
    copy(other);
}

// Copy Assignment
Session& Session::operator=(const Session &other) {
    if (this != &other) {
        clean();
        copy(other);
    }
    return *this;
}

// Move Constructor
Session::Session(Session&& other)
    : content(other.content), actionsLog(other.actionsLog), userMap(other.userMap), activeUser(other.activeUser) {
    other.content.clear();
    other.actionsLog.clear();
    other.userMap.clear();
    other.activeUser = nullptr;
}

// Move Assignment
Session& Session::operator=(Session &&other) {
    if (this != &other) {
        clean();
        copy(other);
        other.clean();
    }
    return *this;
}

void Session::start() {
    string input;
    cout << "SPLFLIX is now on!" << endl;
    cin >> input;
    while (input != "exit") {
        if (input == "createuser") {
            BaseAction *cu = new CreateUser;
            cu->act(*this);
            actionsLog.push_back(cu);
        }
        if (input == "changeuser") {
            BaseAction *cau = new ChangeActiveUser;
            cau->act(*this);
            actionsLog.push_back(cau);
        }
        if (input == "deleteuser") {
            BaseAction *delu = new DeleteUser;
            delu->act(*this);
            actionsLog.push_back(delu);
        }
        if (input == "dupuser") {
            BaseAction *dupu = new DuplicateUser;
            dupu->act(*this);
            actionsLog.push_back(dupu);
        }
        if (input == "content") {
            BaseAction *pcl = new PrintContentList;
            pcl->act(*this);
            actionsLog.push_back(pcl);
        }
        if (input == "watchhist") {
            BaseAction *pwh = new PrintWatchHistory;
            pwh->act(*this);
            actionsLog.push_back(pwh);
        }
        if (input == "watch") {
            BaseAction *w = new Watch;
            w->act(*this);
        }
        if (input == "log") {
            BaseAction *pal = new PrintActionsLog;
            pal->act(*this);
            actionsLog.push_back(pal);
        }
        cin >> input;
    }
    if (input == "exit") {
        BaseAction *exit = new Exit;
        exit->act(*this);
        actionsLog.push_back(exit);
    }
}

void Session::setActiveUser(User* user) {
    activeUser = user;
}

User* Session::getActiveUser() {
    return activeUser;
}

bool Session::userExist(string userName) {
    return userMap.count(userName) != 0;
}

void Session::addUserToUserMap(std::string name, User* user){
    userMap.insert({name, user});
}

User* Session::getUserFromUserMap(std::string name) {
    return userMap.find(name)->second;
}

void Session::deleteUser(std::string name){
    delete userMap.find(name)->second;
    userMap.erase(name);
}

std::vector<Watchable*>& Session::getContent() {
    return content;
}

std::vector<BaseAction *>& Session::getActionsLog() {
    return actionsLog;
}

void Session::addToLog(BaseAction* action){
    actionsLog.push_back(action);
}

void Session::copy(const Session &other) {
    for (size_t i = 0; i < other.content.size(); ++i)
        content.push_back(other.content[i]->clone());
    for (size_t i = 0; i < other.actionsLog.size(); ++i)
        actionsLog.push_back(other.actionsLog[i]->clone());
    for (pair<string, User*> user : other.userMap)
        userMap.insert({user.second->getName(), user.second->clone()});
    activeUser = getUserFromUserMap(other.activeUser->getName());
}

void Session::clean() {
    for (size_t i = 0; i < content.size(); ++i)
        delete content[i];
    content.clear();
    for (size_t i = 0; i < actionsLog.size(); ++i)
        delete actionsLog[i];
    actionsLog.clear();
    for (pair<string, User*> user : userMap)
        delete user.second;
    userMap.clear();
    activeUser = nullptr;
}

void Session::addDataToContentFromJsonFilePath(const string &configFilePath) {
    // read a JSON file
    using json = nlohmann::json;
    ifstream i(configFilePath);
    json data;
    i >> data;

    int id(0);
    for (size_t i = 0; i < data["movies"].size(); ++i) {
        content.push_back(new Movie(id, data["movies"][i]["name"], data["movies"][i]["length"], data["movies"][i]["tags"]));
        id++;
    }

    for (size_t i = 0; i < data["tv_series"].size(); ++i)
    {
        for (size_t season = 1; season <= data["tv_series"][i]["seasons"].size(); ++season)
        {
            for (size_t episode = 1; episode <= data["tv_series"][i]["seasons"][season - 1]; ++episode)
            {
                if(i < data["tv_series"].size() - 1) {
                    if(data["tv_series"][i]["name"] == data["tv_series"][i+1]["name"]) {
                        content.push_back(new Episode(id, data["tv_series"][i]["name"], data["tv_series"][i]["episode_length"], season, episode, id, data["tv_series"][i]["tags"]));
                    } else {
                        content.push_back(new Episode(id, data["tv_series"][i]["name"], data["tv_series"][i]["episode_length"], season, episode, -1, data["tv_series"][i]["tags"]));
                    }
                } else {
                    content.push_back(new Episode(id, data["tv_series"][i]["name"], data["tv_series"][i]["episode_length"], season, episode, -1, data["tv_series"][i]["tags"]));
                }
                id++;
            }
        }
    }
}