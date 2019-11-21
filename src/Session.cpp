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
// Session::Session(const std::string &configFilePath) : content(new vector<Watchable*>() : vector<BaseAction*> {
Session::Session(const std::string &configFilePath) {
    // read a JSON file
    using json = nlohmann::json;
    std::ifstream i(configFilePath);
    json data;
    i >> data;
    
    int id(0);
    for(int i = 0; i < data["movies"].size(); ++i) {
        content.push_back(new Movie(id, data["movies"][i]["name"], data["movies"][i]["length"], data["movies"][i]["tags"]));
        id++;
    }

    for(int i = 0; i < data["tv_series"].size(); ++i) {
        for(int season = 1; season <= data["tv_series"][i]["seasons"].size(); ++season) {
            for(int episode = 1; episode <= data["tv_series"][i]["seasons"][season-1]; ++episode) {
                content.push_back(new Episode(id, data["tv_series"][i]["name"], data["tv_series"][i]["episode_length"], season, episode, data["tv_series"][i]["tags"]));
                id++;
            }
        }
    }

    for(int f = 0; f < content.size(); ++f)
        std::cout << content[f]->toString() << '\n';

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