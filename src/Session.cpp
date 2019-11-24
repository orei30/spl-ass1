#include "../include/Session.h"
#include <../include/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iterator>
#include "Action.h"
#include "User.h"
#include "Watchable.h"

//Constructor
// Session::Session(const std::string &configFilePath) : content(new vector<Watchable*>() : vector<BaseAction*> {
Session::Session(const std::string &configFilePath) : activeUser(new LengthRecommenderUser("default")) {
    userMap.insert({"default",activeUser});
    addDataToContentFromJsonFilePath(configFilePath);
};

void Session::start() {
    std::string input("");
    std::cout << "SPLFLIX is now on!" << std::endl;
    

    while(input != "exit") {
        std::cout << "Your command: ";
        std::getline(std::cin, input);
        setUserInput(input);
        std::vector<std::string> splitedInput = split(input, ' ');
        if(splitedInput[0].compare("createuser") == 0) {
            if(splitedInput.size() != 3) {
                std::cout << "Error - invalid parameters" << std::endl;
            } else {
                if(userMap.count(splitedInput[1]) != 0) {
                    std::cout << "Error - user exist" << std::endl;
                } else {
                    if(splitedInput[2].compare("len") == 0) {
                        userMap.insert({splitedInput[1], new LengthRecommenderUser(splitedInput[1])});
                    } else if(splitedInput[2].compare("rer") == 0) {
                        userMap.insert({splitedInput[1], new RerunRecommenderUser(splitedInput[1])});
                    } else if(splitedInput[2].compare("gen") == 0) {
                        userMap.insert({splitedInput[1], new GenreRecommenderUser(splitedInput[1])});
                    } else {
                        std::cout << "Error - invalid preffernce algorithem `" << std::endl;
                    }
                }
                
            }
        }
        if(splitedInput[0].compare("changeuser") == 0) {
            if(splitedInput.size() != 2) {
                std::cout << "Error - invalid parameters" << std::endl;
            } else {
                if(userMap.count(splitedInput[1]) == 0) {
                    std::cout << "Error - user doesn't exist" << std::endl;
                } else {
                    std::unordered_map<std::string,User*>::const_iterator userFromMap = userMap.find(splitedInput[1]);
                    activeUser = userFromMap->second;
                }
            }
        }
        if(splitedInput[0].compare("deleteuser") == 0) {
            if(splitedInput.size() != 2) {
                std::cout << "Error - invalid parameters" << std::endl;
            } else {
                if(userMap.count(splitedInput[1]) == 0) {
                    std::cout << "Error - user doesn't exist" << std::endl;
                } else {
                    userMap.erase(splitedInput[1]);
                }
            }
        }
        if(splitedInput[0].compare("dupuser") == 0) {
            if(splitedInput.size() != 3) {
                std::cout << "Error - invalid parameters" << std::endl;
            } else {
                if(userMap.count(splitedInput[1]) == 0) {
                    std::cout << "Error - user doesn't exist" << std::endl;
                } else {
                    if(userMap.count(splitedInput[2]) == 0) {
                        std::unordered_map<std::string,User*>::const_iterator userFromMap = userMap.find(splitedInput[1]);
                    } else {
                        std::cout << "Error - user exist" << std::endl;
                    }
                }
            }
            std::cout << "Duplicate User" << input << std::endl;
        }
        if(splitedInput[0].compare("content") == 0) {
            std::cout << "Print Content List" << input << std::endl;
        }
        if(splitedInput[0].compare("watchhist") == 0) {
            std::cout << "Print Watch History" << input << std::endl;
        }
        if(splitedInput[0].compare("watch") == 0) {
            std::cout << "Watch" << input << std::endl;
        }
        if(splitedInput[0].compare("log") == 0) {
            std::cout << "Print Actions Log" << input << std::endl;
        }
    }
}

std::string Session::getUserInput() const{
    return this->userInput;
}

void Session::setUserInput(std::string value) {
    this->userInput = value;
}

void Session::addDataToContentFromJsonFilePath(const std::string &configFilePath) {
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
}