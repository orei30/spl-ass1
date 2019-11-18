#include "../include/Watchable.h"
#include <iostream>

Watchable::Watchable(long id, int length, const std::vector<std::string>& tags) :
    id(id), length(length), tags(tags) {
}

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) :
    Watchable(id, length, tags), name(name) {
}

Episode::Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags) :
    Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode) {
}

std::string Movie::toString(bool print_full=false) const {
    if(print_full) {
        return std::cout << "Id: " << id << << " Name: " << name << " Length: " << length << " Tags: " << tags << std::endl;
    } else {
        return std::cout << "Id: " << id << << " Name: " << name << std::endl;
    }
}

std::string Episode::toString(bool print_full=false) const {
    if(print_full) {
        return std::cout << "Id: " << id << << " Name: " << seriesName << std::endl;
    } else {
        return std::cout << "Id: " << id << << " Name: " << seriesName << std::endl;
    }
}