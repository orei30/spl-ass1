#include "../include/User.h"
#include <iostream>
#include <string>
#include "../include/Watchable.h"


User::User(const std::string& name) : name(name) {
}

std::string User::getName() const {
    return this->name;
}

// User::User(User* other){
//     this->name = other->getName();
//     this->history=new vector<Watchable*>(other.get_History()&);
// }

void User::setName(std::string value) {
    this->name = value;
}

void User::addMovieToHistory(Watchable* value) {
    history.push_back(value);
}

// std::vector<Watchable*> get_history() const {
//     return this->history;
// }

LengthRecommenderUser::LengthRecommenderUser(const std::string& name):User(name) {}

// LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser* other):User(other.getName()) {}

RerunRecommenderUser::RerunRecommenderUser(const std::string& name):User(name) {}

// RerunRecommenderUser::RerunRecommenderUser(RerunRecommenderUser* other):User(other.getName()) {}

GenreRecommenderUser::GenreRecommenderUser(const std::string& name):User(name) {}

// GenreRecommenderUser::GenreRecommenderUser(GenreRecommenderUser* other):User(other.getName()) {}


