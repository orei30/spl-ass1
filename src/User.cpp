#include "../include/User.h"
#include "../include/Session.h"
#include "../include/Watchable.h"

using namespace std;

// Constructor
User::User(const string &name) : history(), name(name) {}

// Destructor
User::~User() {
    for (size_t i = 0; i < history.size(); ++i)
        delete history[i];
    history.clear();
}

// Copy Constructor
User::User(const User &other) : history(), name() {
    name = other.name;
    for (size_t i = 0; i < other.history.size(); i++)
        history.push_back(other.history[i]->clone());
        // history.push_back(other.content[i]->clone());
}

// Copy Assignment
User& User::operator=(const User &other) {
    if (this != &other) {
        name = other.name;
        for (size_t i = 0; i < history.size(); ++i)
            delete history[i];
        for (size_t i = 0; i < other.history.size(); i++) 
            history.push_back(other.history[i]);
        for (size_t i = 0; i < other.history.size(); ++i)
            delete other.history[i];
    }
    return *this;
}

// Move Constructor
User::User(User&& other)
    : history(other.history), name(other.name) {
    for (size_t i = 0; i < other.history.size(); ++i)
            delete other.history[i];
}

// Move Assignment
User& User::operator=(User &&other) {
    if (this != &other) {
        for (size_t i = 0; i < history.size(); ++i)
            delete history[i];
        name = other.name;
        for (size_t i = 0; i < other.history.size(); i++) 
            history.push_back(other.history[i]);
    }
    return *this;
}

string User::getName() const {
    return this->name;
}

void User::setName(string value) {
    name = value;
}

vector<Watchable*>& User::get_history() {
    return history;
}

// Constructor
LengthRecommenderUser::LengthRecommenderUser(const string &name) : User(name), avrLen(0) {}

// Destructor
LengthRecommenderUser::~LengthRecommenderUser() {}

// Copy Constructor
LengthRecommenderUser::LengthRecommenderUser(const LengthRecommenderUser &other) : User(other), avrLen(other.avrLen) {}

// Copy Assignment
LengthRecommenderUser& LengthRecommenderUser::operator=(const LengthRecommenderUser &other) {
    if (this != &other) {
        this->User::operator=(other);
        avrLen = other.avrLen;
    }
    return *this;
}

// Move Constructor
LengthRecommenderUser::LengthRecommenderUser(LengthRecommenderUser&& other) 
    : User(other), avrLen(other.avrLen) {
    for (size_t i = 0; i < other.history.size(); ++i)
            delete other.history[i];
}

// Move Assignment
LengthRecommenderUser& LengthRecommenderUser::operator=(LengthRecommenderUser &&other) {
    if (this != &other) {
        for (size_t i = 0; i < history.size(); ++i)
            delete history[i];
        setName(other.getName());
        avrLen = other.avrLen;
        for (size_t i = 0; i < other.history.size(); i++) 
            history.push_back(other.history[i]);
    }
    return *this;
}

void LengthRecommenderUser::addElementToHistory(Watchable *value) {
    history.push_back(value->clone());
    if (history.size() == 1)
        avrLen = value->getLen();
    else
        avrLen = ((avrLen * (history.size() - 1)) / history.size() + value->getLen() / history.size());
}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    int minDef(1000);
    Watchable* recommended = nullptr;
    for(auto const& element: s.getContent()) {
        bool allreadyWatchIt = false;
        for(size_t i = 0; !allreadyWatchIt & (i < history.size()); ++i) {
            if(history.at(i)->getId() == element->getId()) {
                allreadyWatchIt = true;
            }
        }
        if(!allreadyWatchIt) {
            if(abs(element->getLen()-avrLen) < minDef) {
                minDef = abs(element->getLen()-avrLen);
                recommended = element;
            }
        }
        
    }
    return recommended;
}

User* LengthRecommenderUser::clone(string newName) {
    LengthRecommenderUser* newUser = new LengthRecommenderUser(newName);
    newUser->avrLen = this->avrLen;
    for (size_t i = 0; i < this->history.size(); i++) 
        newUser->history.push_back(this->history[i]->clone());
    return newUser;
}

User* LengthRecommenderUser::clone() {
    return new LengthRecommenderUser(*this);
}

// Constructor
RerunRecommenderUser::RerunRecommenderUser(const string &name) : User(name), lastRecommendation(0) {}

// Destructor
RerunRecommenderUser::~RerunRecommenderUser() {}

// Copy Constructor
RerunRecommenderUser::RerunRecommenderUser(const RerunRecommenderUser &other) : User(other), lastRecommendation(other.lastRecommendation) {}

// Copy Assignment
RerunRecommenderUser& RerunRecommenderUser::operator=(const RerunRecommenderUser &other) {
    if (this != &other)
    {
        this->User::operator=(other);
        lastRecommendation = other.lastRecommendation;
    }
    return *this;
}

// Move Constructor
RerunRecommenderUser::RerunRecommenderUser(RerunRecommenderUser&& other)
    : User(other), lastRecommendation(other.lastRecommendation) {
    for (size_t i = 0; i < other.history.size(); ++i)
            delete other.history[i];
}

// Move Assignment
RerunRecommenderUser& RerunRecommenderUser::operator=(RerunRecommenderUser &&other) {
    if (this != &other) {
        for (size_t i = 0; i < history.size(); ++i)
            delete history[i];
        setName(other.getName());
        lastRecommendation = other.lastRecommendation;
        for (size_t i = 0; i < other.history.size(); i++) 
            history.push_back(other.history[i]);
    }
    return *this;
}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    return get_history()[lastRecommendation % get_history().size()];
}

void RerunRecommenderUser::addElementToHistory(Watchable *value) {
    if(!history.empty()) {
        if(value->getId() == history[lastRecommendation]->getId()) {
            lastRecommendation = lastRecommendation + 1;
        }
    }
    history.push_back(value->clone());
}

User* RerunRecommenderUser::clone(string newName) {
    RerunRecommenderUser* newUser = new RerunRecommenderUser(newName);
    newUser->lastRecommendation = this->lastRecommendation;
    for (size_t i = 0; i < this->history.size(); i++) 
        newUser->history.push_back(this->history[i]->clone());
    return newUser;
}

User* RerunRecommenderUser::clone() {
    return new RerunRecommenderUser(*this);
}

// Constructor
GenreRecommenderUser::GenreRecommenderUser(const string &name) : User(name), tagsMap(), orederedTags() {}

// Destructor
GenreRecommenderUser::~GenreRecommenderUser() {
    tagsMap.clear();
    orederedTags.clear();
}

// Copy Constructor
GenreRecommenderUser::GenreRecommenderUser(const GenreRecommenderUser &other) : User(other), tagsMap(), orederedTags() {
    for (pair<string, long> tag : other.tagsMap)
        tagsMap.insert(tag); 
    for (size_t i = 0; i < other.orederedTags.size(); i++) 
        orederedTags.push_back(other.orederedTags[i]);
}

// Copy Assignment
GenreRecommenderUser& GenreRecommenderUser::operator=(const GenreRecommenderUser &other) {
    if (this != &other) {
        this->User::operator=(other);
        for (pair<string, long> tag : other.tagsMap)
            tagsMap.insert(tag);
        for (size_t i = 0; i < other.orederedTags.size(); i++) 
            orederedTags.push_back(other.orederedTags[i]);
    }
    return *this;
}

// Move Constructor
GenreRecommenderUser::GenreRecommenderUser(GenreRecommenderUser&& other) 
    : User(other), tagsMap(), orederedTags() {
    for (pair<string, long> tag : other.tagsMap)
        tagsMap.insert(tag);
    for (size_t i = 0; i < other.orederedTags.size(); i++) 
        orederedTags.push_back(other.orederedTags[i]);
    for (size_t i = 0; i < other.history.size(); ++i)
        delete other.history[i];
    tagsMap.clear();
    orederedTags.clear();
}

// Move Assignment
GenreRecommenderUser& GenreRecommenderUser::operator=(GenreRecommenderUser &&other) {
    if (this != &other) {
        for (size_t i = 0; i < history.size(); ++i)
            delete history[i];
        tagsMap.clear();
        orederedTags.clear();
        setName(other.getName());
        for (pair<string, long> tag : other.tagsMap)
            tagsMap.insert(tag);
        for (size_t i = 0; i < other.orederedTags.size(); i++) 
            orederedTags.push_back(other.orederedTags[i]);
        for (size_t i = 0; i < other.history.size(); i++) 
            history.push_back(other.history[i]);
    }
    return *this;
}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {
    for(auto const& tag: orederedTags) {
        for(auto const& watchable: s.getContent()) {
            bool allreadyWatched = false;
            for(size_t k = 0; !allreadyWatched & (k < history.size()); ++k) {
                if(watchable->getId() == history[k]->getId()) {
                    allreadyWatched = true;
                }
            }
            if(!allreadyWatched) {
                for(auto const& watchableTag: watchable->getTags()) {
                    if(watchableTag == tag)
                        return watchable;
                }
            }
        }
    }
    return s.getContent()[243];
};

void GenreRecommenderUser::addElementToHistory(Watchable *value)
{
    history.push_back(value->clone());

    for(auto const& tag: value->getTags()) {
        if(tagsMap.find(tag) == tagsMap.end()) {
            tagsMap.insert({tag, 1});
            orederedTags.push_back(tag);
        } else {
            tagsMap.find(tag)->second++;
        }
    }
    for(size_t i = orederedTags.size()-1; i > 0; --i) {
        if(tagsMap.find(orederedTags[i])->second > tagsMap.find(orederedTags[i-1])->second) {
            switchTags(i);
        } else if(tagsMap.find(orederedTags[i])->second == tagsMap.find(orederedTags[i-1])->second) {
            if(tagsMap.find(orederedTags[i-1])->first.compare(tagsMap.find(orederedTags[i])->first) > 0) {
                switchTags(i);
            }
        }
    }
}

User* GenreRecommenderUser::clone(string newName) {
    GenreRecommenderUser* newUser = new GenreRecommenderUser(newName);
    for (size_t i = 0; i < this->history.size(); i++) 
        newUser->history.push_back(this->history[i]->clone());
    for (pair<string, long> tag : this->tagsMap)
        newUser->tagsMap.insert(tag);
    for (size_t i = 0; i < this->orederedTags.size(); i++) 
        newUser->orederedTags.push_back(this->orederedTags[i]);
    return newUser;
}

User* GenreRecommenderUser::clone() {
    return new GenreRecommenderUser(*this);
}

void GenreRecommenderUser::switchTags(long i) {
    string temp = orederedTags[i];
    orederedTags[i] = orederedTags[i-1];
    orederedTags[i-1] = temp;
}