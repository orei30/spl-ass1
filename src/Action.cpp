#include <iostream>
#include <fstream>


#include <string>
#include "../include/Action.h"


BaseAction::BaseAction() : status(PENDING){}

void CreateUser::act(Session& sess) {
    
}


template <typename Out>
void Session::split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}

std::vector<std::string> Session::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

//  ActionStatus getStatus() const{
//      return this->status;
//  }

//  std::string getErrorMsg() const{
//      return this->errorMsg;
//  }

//  CreateUser:: CreateUser() : BaseAction() {}

//  void CreateUser::act(Session& sess){
//      sess->usermap.userMap.pushback
// }
// std::string CreateUser::toString() const{

// }

//  ChangeActiveUser:: ChangeActiveUser() : BaseAction() {}

//  void ChangeActiveUser::act(Session& sess){
//     std::string delimiter = " ";
//     std::string token = sess.substr(s.find(delimiter), sess.length()-1);
// // }

// std::string ChangeActiveUser::toString() const{
    
// }


//  DeleteUser:: DeleteUser() : BaseAction() {}

//  void DeleteUser::act(Session& sess){
     
// }

// std::string DeleteUser::toString() const{
    
// }


//  DuplicateUser:: DuplicateUser() : BaseAction() {}

//  void DuplicateUser::act(Session& sess){
     
// }

// std::string DuplicateUser::toString() const{
    
// }

//  PrintContentList:: PrintContentList() : BaseAction() {}

//  void PrintContentList::act(Session& sess){
     
// }

// std::string PrintContentList::toString() const{
    
// }

//  PrintWatchHistory:: PrintWatchHistory() : BaseAction() {}

//  void PrintWatchHistory::act(Session& sess){
     
// }

// std::string PrintWatchHistory::toString() const{
    
// }

//  Watch:: Watch() : BaseAction() {}

//  void Watch::act(Session& sess){
     
// }

// std::string Watch::toString() const{
    
// }

//  PrintActionsLog:: PrintActionsLog() : BaseAction() {}

//  void PrintActionsLog::act(Session& sess){
     
// }

// std::string PrintActionsLog::toString() const{
    
// }

//  Exit:: Exit() : BaseAction() {}

// void Exit::act(Session& sess){
     
// }

// std::string Exit::toString() const{
    
// }