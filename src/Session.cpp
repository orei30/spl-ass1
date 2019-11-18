#include "../include/Session.h"
#include <../include/json.hpp>
#include <iostream>
#include <fstream>

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h"
#include "User.h"
#include "Watchable.h"

//Constructor
Session::Session(const std::string &configFilePath) {
    // read a JSON file
    using json = nlohmann::json;
    std::ifstream i(configFilePath);
    json j;
    i >> j;

    for (int i = 0; i < j["movies"].size(); i++) {
        content.push_back(new Movie(i, j["movies"][i]["name"], j["movies"][i]["length"], j["movies"][i]["tags"]));
        std::cout << "Moview: " << content.at(i)->toString() << std::endl;
    }
};

void Session::start() {
    std::string input("");
    std::cout << "SPLFLIX is now on!" << std::endl;
    LengthRecommenderUser* user = new LengthRecommenderUser("default");


    // while(input != "exit") {
    //     std::cout << "Your command: ";
    //     std::getline(std::cin, input);
    //     if(input.compare("createuser") == 0) {
    //         std::cout << "createuser" << input::endl;
    //     }
    //     if(input.compare("changeuser") == 0) {
    //         std::cout << "change user" << input::endl;
    //     }
    //     if(input.compare("deleteuser") == 0) {
    //         std::cout << "Delete User" << input::endl;
    //     }
    //     if(input.compare("dupuser") == 0) {
    //         std::cout << "Duplicate User" << input::endl;
    //     }
    //     if(input.compare("content") == 0) {
    //         std::cout << "Print Content List" << input::endl;
    //     }
    //     if(input.compare("watchhist") == 0) {
    //         std::cout << "Print Watch History" << input::endl;
    //     }
    //     if(input.compare("watch") == 0) {
    //         std::cout << "Watch" << input::endl;
    //     }
    //     if(input.compare("log") == 0) {
    //         std::cout << "Print Actions Log" << input::endl;
    //     }
    // }
}