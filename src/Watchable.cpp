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

std::string Movie::toString() const {
    return std::to_string(getId() + 1) + ". " + name + " " + std::to_string(getLen()) + " minutes " + vectorToString(getTags());
}
std::string Episode::toString() const {
    return std::to_string(getId() + 1) + ". " + seriesName + " S" + std::to_string(season) + "E" + std::to_string(episode) + " " + std::to_string(getLen()) + " minutes " + vectorToString(getTags());
}

std::string Watchable::vectorToString(const std::vector<std::string> &vector) const {
    std::string tags;
    if(!vector.empty()) {
        tags += "[" + vector[0];
        int numOfTags(vector.size());
        if(numOfTags != 1) {
            for(int i = 1; i < numOfTags - 1; ++i) {
                tags += ", " + vector[i];
            }
            tags += ", " + vector[numOfTags-1];
        }
        tags += "]";
    }
    return tags;
}
// Movie::Watchable* getNextWatchable(Session& ses) const{

// }
    
