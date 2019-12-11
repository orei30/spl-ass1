#include "../include/Action.h"
#include "../include/Session.h"
#include "../include/User.h"
#include "../include/Watchable.h"

using namespace std;

// Constructor
BaseAction::BaseAction() : errorMsg(""), status(PENDING) {}

BaseAction::~BaseAction() {}

BaseAction::BaseAction(const BaseAction &other) : errorMsg(other.errorMsg), status(other.status) {}

void BaseAction::complete() {
    status = COMPLETED;
}

void BaseAction::error(const string &errorMsg) {
    status = ERROR;
    this->errorMsg = errorMsg;
    cout << "Error - " + errorMsg << endl;
}

ActionStatus BaseAction::getStatus() const {
    return this->status;
}

string BaseAction::getErrorMsg() const {
    return this->errorMsg;
}

string BaseAction::statusToString() const{
    if(status==COMPLETED)
        return "COMPLETED";
    if(status==ERROR)
        return "ERROR";
    return "PENDING";    
}

CreateUser::CreateUser(){}

CreateUser::~CreateUser() {}

CreateUser::CreateUser(const BaseAction &other): BaseAction(other) {}

void CreateUser::act(Session &sess) {
    string name;
    string alg;
    cin >> name >> alg;
    if (sess.userExist(name)){
        error("username is already in use");
    }
    else if (alg != "len" && alg != "rer" && alg != "gen") {
        error("recommendation algorithm is invalid");
    } else {
        if (alg == "len")
            sess.addUserToUserMap(name, new LengthRecommenderUser(name));
        if (alg == "rer")
            sess.addUserToUserMap(name, new RerunRecommenderUser(name));
        if (alg == "gen")
            sess.addUserToUserMap(name, new GenreRecommenderUser(name));
        complete();
    }
}

string CreateUser::toString() const {
    if(statusToString() == "ERROR") {
        return "CreateUser " + statusToString() + ": " + getErrorMsg();
    } else {
        return "CreateUser " + statusToString();
    }
}

BaseAction* CreateUser::clone() {
    return new CreateUser(*this);
}

ChangeActiveUser::ChangeActiveUser() {}

ChangeActiveUser::ChangeActiveUser(const BaseAction &other): BaseAction(other) {}

ChangeActiveUser::~ChangeActiveUser() {}

void ChangeActiveUser::act(Session &sess) {
    string name;
    cin >> name;
    if (!sess.userExist(name)) {
        error("username does not exist");
    } else {
        sess.setActiveUser(sess.getUserFromUserMap(name));
        complete();
    }
}

string ChangeActiveUser::toString() const{
    if(statusToString() == "ERROR") {
        return "ChangeActiveUser " + statusToString() + ": " + getErrorMsg();
    } else {
        return "ChangeActiveUser " + statusToString();
    }
}

BaseAction* ChangeActiveUser::clone() {
    return new ChangeActiveUser(*this);
}

DeleteUser::DeleteUser() {}

DeleteUser::DeleteUser(const BaseAction &other): BaseAction(other) {}

DeleteUser::~DeleteUser() {}

void DeleteUser::act(Session &sess) {
    string name;
    cin >> name;
    if (!sess.userExist(name)) {
        error("username does not exist");
    } else {
        sess.deleteUser(name);
        complete();
    }
}

string DeleteUser::toString() const {
    if(statusToString() == "ERROR") {
        return "DeleteUser " + statusToString() + ": " + getErrorMsg();
    } else {
        return "DeleteUser " + statusToString();
    }
}

BaseAction* DeleteUser::clone() {
    return new DeleteUser(*this);
}

DuplicateUser::DuplicateUser() {}

DuplicateUser::DuplicateUser(const BaseAction &other): BaseAction(other) {}

DuplicateUser::~DuplicateUser() {}

void DuplicateUser::act(Session &sess) {
    string oldUserName;
    cin >> oldUserName;
    string newUserName;
    cin >> newUserName;
    if (sess.userExist(newUserName)) {
        error("username is already in use");
    } else {
        if (!sess.userExist(oldUserName)) {
            error("username does not exist");
        } else {
            sess.addUserToUserMap(newUserName, sess.getUserFromUserMap(oldUserName)->clone(newUserName));
            complete();
        }
    }
}

string DuplicateUser::toString() const {
    if(statusToString() == "ERROR") {
        return "DuplicateUser " + statusToString() + ": " + getErrorMsg();
    } else {
        return "DuplicateUser " + statusToString();
    }
}

BaseAction* DuplicateUser::clone() {
    return new DuplicateUser(*this);
}

PrintContentList::PrintContentList() {}

PrintContentList::PrintContentList(const BaseAction &other): BaseAction(other) {}

PrintContentList::~PrintContentList() {}

void PrintContentList::act(Session &sess) {
    for (size_t i = 0; i < sess.getContent().size(); ++i)
        cout << to_string(sess.getContent()[i]->getId() + 1) + ". " + sess.getContent()[i]->toString() + " " + to_string(sess.getContent()[i]->getLen()) + " minutes " + sess.getContent()[i]->tagsToString(sess.getContent()[i]->getTags()) << endl;
}

string PrintContentList::toString() const {
    if(statusToString() == "ERROR") {
        return "PrintContentList " + statusToString() + ": " + getErrorMsg();
    } else {
        return "PrintContentList " + statusToString();
    }
}

BaseAction* PrintContentList::clone() {
    return new PrintContentList(*this);
}

PrintWatchHistory::PrintWatchHistory() {}

PrintWatchHistory::PrintWatchHistory(const BaseAction &other): BaseAction(other) {}

PrintWatchHistory::~PrintWatchHistory() {}

void PrintWatchHistory::act(Session &sess) {
    cout << "Watch History for " + sess.getActiveUser()->getName() << endl;
    for (size_t f = 0; f < sess.getActiveUser()->get_history().size(); ++f)
        cout << to_string(f + 1) + ". " + sess.getActiveUser()->get_history()[f]->toString() << endl;
    complete();
}

string PrintWatchHistory::toString() const {
    if(statusToString() == "ERROR") {
        return "PrintWatchHistory " + statusToString() + ": " + getErrorMsg();
    } else {
        return "PrintWatchHistory " + statusToString();
    }
}

BaseAction* PrintWatchHistory::clone() {
    return new PrintWatchHistory(*this);
}

Watch::Watch():BaseAction(), idWatch(-1) {}

Watch::Watch(long id):BaseAction(), idWatch(id) {}

Watch::Watch(const Watch &other): BaseAction(other), idWatch(other.idWatch) {}

Watch::~Watch() {}

void Watch::act(Session &sess) {
    if(idWatch==-1)
        cin >> idWatch;
    Watchable *toWatch = sess.getContent()[idWatch-1];
    cout << "Watching " + toWatch->toString() << endl;
    sess.getActiveUser()->addElementToHistory(toWatch);
    complete();
    sess.addToLog(this);
    Watchable *recom = toWatch->getNextWatchable(sess);
    cout << "We recommend watching " + recom->toString() + " Continue Watching[y/n]" << endl;
    string yes;
    cin >> yes;
    if(yes == "y") {
        BaseAction* next= new Watch(recom->getId()+1);
        next->act(sess);
    }
}

string Watch::toString() const {
    if(statusToString() == "ERROR") {
        return "Watch " + statusToString() + ": " + getErrorMsg();
    } else {
        return "Watch " + statusToString();
    }
}

BaseAction* Watch::clone() {
    return new Watch(*this);
}

PrintActionsLog::PrintActionsLog() {}

PrintActionsLog::PrintActionsLog(const BaseAction &other): BaseAction(other) {}

PrintActionsLog::~PrintActionsLog() {}

void PrintActionsLog::act(Session &sess) {
    for (int i = sess.getActionsLog().size()-1; i > -1; i--)
        cout << sess.getActionsLog()[i]->toString() << endl;
    complete();
}

string PrintActionsLog::toString() const {
    if(statusToString() == "ERROR") {
        return "PrintActionsLog " + statusToString() + ": " + getErrorMsg();
    } else {
        return "PrintActionsLog " + statusToString();
    }
}

BaseAction* PrintActionsLog::clone() {
    return new PrintActionsLog(*this);
}

Exit::Exit() {}

Exit::Exit(const BaseAction &other): BaseAction(other) {}

Exit::~Exit() {}

void Exit::act(Session &sess) {
    complete();
}

string Exit::toString() const {
    if(statusToString() == "ERROR") {
        return "Exit " + statusToString() + ": " + getErrorMsg();
    } else {
        return "Exit " + statusToString();
    }
}

BaseAction* Exit::clone() {
    return new Exit(*this);
}