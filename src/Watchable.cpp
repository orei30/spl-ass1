#include "../include/Watchable.h"
#include "../include/Session.h"
#include "../include/User.h"

using namespace std;

Watchable::Watchable(long id, int length, const vector<string> &tags) : id(id), length(length), tags(tags) {}

Watchable::~Watchable() {
    tags.clear();
}

Watchable::Watchable(const Watchable &other) : id(other.id), length(other.length), tags() {
    for(size_t i=0; i<other.getTags().size(); i++)
        tags.push_back(other.getTags()[i]);
}

Watchable &Watchable::operator=(const Watchable &other) {
    if (this != &other) {
        tags.clear();
        length = other.length;
        for(size_t i=0; i<other.getTags().size(); i++){
            tags.push_back(other.getTags()[i]);
        }
    }
    return *this;
}

long Watchable::getId() const {
    return this->id;
}

int Watchable::getLen() const {
    return this->length;
}

vector<string> Watchable::getTags() const {
    return this->tags;
}

string Watchable::tagsToString(const vector<string> &vector) const {
    string tags;
    if (!vector.empty()) {
        tags += "[" + vector[0];
        int numOfTags(vector.size());
        if (numOfTags != 1)
        {
            for (int i = 1; i < numOfTags - 1; ++i)
            {
                tags += ", " + vector[i];
            }
            tags += ", " + vector[numOfTags - 1];
        }
        tags += "]";
    }
    return tags;
}

Movie::Movie(long id, const string &name, int length, const vector<string> &tags) : Watchable(id, length, tags), name(name) {}

Movie::~Movie() {}

Movie::Movie(const Movie &other) : Watchable(other), name(other.name) {}

Movie &Movie::operator=(const Movie &other) {
    if (this != &other) {
        (*this).Watchable::operator=(other);
        name = other.name;
    }
    return *this;
}

string Movie::toString() const {
    return name;
}

Watchable* Movie::getNextWatchable(Session &ses) const {
    return ses.getActiveUser()->getRecommendation(ses);
}

Watchable* Movie::clone() {
    return new Movie(*this);
}

Episode::Episode(long id, const string &seriesName, int length, int season, int episode, const vector<string> &tags) : Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode), nextEpisodeId(id++) {}

Episode::Episode(long id, const string &seriesName, int length, int season, int episode, long nextEpisodeId, const vector<string> &tags) : Watchable(id, length, tags), seriesName(seriesName), season(season), episode(episode), nextEpisodeId(nextEpisodeId) {}

Episode::~Episode() {}

Episode::Episode(const Episode &other) : Watchable(other), seriesName(other.seriesName),
                                         season(other.season), episode(other.episode), nextEpisodeId(other.nextEpisodeId) {}

Episode &Episode::operator=(const Episode &other) {
    if (this != &other) {
        this->Watchable::operator=(other);
        seriesName = other.seriesName;
        season = other.season;
        episode = other.episode;
        nextEpisodeId = other.nextEpisodeId + 1;
    }
    return *this;
}

string Episode::toString() const {
    return seriesName + " S" + to_string(season) + "E" + to_string(episode);
}

Watchable * Episode::getNextWatchable(Session &ses) const {
    if(nextEpisodeId == -1) {
        return ses.getActiveUser()->getRecommendation(ses);
    } else {
        return ses.getContent().at(nextEpisodeId);
    }
}

Watchable* Episode::clone() {
    return new Episode(*this);
}