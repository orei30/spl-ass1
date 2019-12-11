#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>

class Watchable;
class Session;

class User{
public:
    // Constructor
    User(const std::string& name);
    // Destructor
    virtual ~User();
    // Copy Constructor
    User(const User &other);
    // Move Constructor
    User(User &&other);
    // Copy Assignment
    User& operator=(const User &other);
    // Move Assignment
    User& operator=(User &&other);
    virtual Watchable* getRecommendation(Session& s) = 0;
    virtual void addElementToHistory(Watchable *) = 0;
    virtual User* clone(std::string)=0;
    virtual User* clone()=0;
    std::string getName() const;
    void setName(std::string);
    std::vector<Watchable*>& get_history();
protected:
    std::vector<Watchable*> history;
private:
    std::string name;

};


class LengthRecommenderUser : public User {
public:
    // Constructor
    LengthRecommenderUser(const std::string& name);
    // Destructor
    virtual ~LengthRecommenderUser();
    // Copy Constructor
    LengthRecommenderUser(const LengthRecommenderUser &);
    // Move Constructor
    LengthRecommenderUser(LengthRecommenderUser &&other);
    // Copy Assignment
    LengthRecommenderUser& operator=(const LengthRecommenderUser &other);
    // Move Assignment
    LengthRecommenderUser& operator=(LengthRecommenderUser &&other);
    virtual Watchable* getRecommendation(Session& s);
    virtual void addElementToHistory(Watchable *);
    virtual User* clone(std::string);
    virtual User* clone();
private:
    long avrLen;
};

class RerunRecommenderUser : public User {
public:
    // Constructor
    RerunRecommenderUser(const std::string& name);
    // Destructor
    virtual ~RerunRecommenderUser();
    // Copy Constructor
    RerunRecommenderUser(const RerunRecommenderUser &);
    // Move Constructor
    RerunRecommenderUser(RerunRecommenderUser &&other);
    // Copy Assignment
    RerunRecommenderUser& operator=(const RerunRecommenderUser &other);
    // Move Assignment
    RerunRecommenderUser& operator=(RerunRecommenderUser &&other);
    virtual Watchable* getRecommendation(Session& s);
    virtual void addElementToHistory(Watchable *);
    virtual User* clone(std::string);
    virtual User* clone();
private:
    long lastRecommendation;
};

class GenreRecommenderUser : public User {
public:
    // Constructor
    GenreRecommenderUser(const std::string& name);
    // Destructor
    virtual ~GenreRecommenderUser();
    // Copy Constructor
    GenreRecommenderUser(const GenreRecommenderUser &);
    // Move Constructor
    GenreRecommenderUser(GenreRecommenderUser &&other);
    // Copy Assignment
    GenreRecommenderUser& operator=(const GenreRecommenderUser &other);
    // Move Assignment
    GenreRecommenderUser& operator=(GenreRecommenderUser &&other);
    virtual Watchable* getRecommendation(Session& s);
    virtual void addElementToHistory(Watchable *);
    virtual User* clone(std::string);
    virtual User* clone();
private:
    std::map<std::string, long> tagsMap;
    std::vector<std::string> orederedTags;
    void switchTags(long);
};

#endif
