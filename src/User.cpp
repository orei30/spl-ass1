#include "../include/User.h"
#include <iostream>
#include <string>

User::User(const std::string& name) : name(name) {
}

std::string User::getName() const {
    return this->name;
}

// void User::setName(std::string value) {
//     this->name = value;
// }

// std::vector<Watchable*> get_history() const {
//     return this->history;
// }

LengthRecommenderUser::LengthRecommenderUser(const std::string& name):User(name) {}

RerunRecommenderUser::RerunRecommenderUser(const std::string& name):User(name) {}

GenreRecommenderUser::GenreRecommenderUser(const std::string& name):User(name) {}