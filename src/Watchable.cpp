#include "../include/Watchable.h"
#include <iostream>

#include <string>
#include <vector>

Watchable::Watchable(long id, int length, const std::vector<std::string>& tags) :
    id(id), length(length), tags(tags) {
}

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags) :
    Watchable(id, length, tags), name(name) {
}

Episode::Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags) :
    Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode) {
}

long Watchable::getId() const {
    return this->id;
}

int Watchable::getLen() const {
    return this->length;
}

std::vector<std::string> Watchable::getTags() const {
    return this->tags;
}

// std::string Movie::toString() const {
//         return std::cout << "Id: " + getId() +  " Name: " + name << " Length: " + getLen() + " Tags: " + getTags() << std::endl;
// }

// std::string Episode::toString() const {
//         return std::cout << "Id: " << getId() << " Name: " << seriesName << " Season: " << season << " Episode: " << episode << " Length: " << getLen() << " Tags: " << getTags() << std::endl;
// }

std::string Movie::toString() const {
        return "Id: " + std::to_string(getId()) + " Name: " + name + " Length: " + std::to_string(getLen());
}
std::string Episode::toString() const {
        return "Id: " + std::to_string(getId()) + " Name: " + seriesName + " Season: " + std::to_string(season) + " Episode: " + std::to_string(episode) + " Length: " + std::to_string(getLen());
}
// Movie::Watchable* getNextWatchable(Session& ses) const{

// }
    
