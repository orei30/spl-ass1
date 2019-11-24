#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{
public:
    User(const std::string& name);
    User(User*);
    // ~User();
    // virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    void setName(std::string);
    std::vector<Watchable*> get_history() const;
    void addMovieToHistory(Watchable*);
protected:
    std::vector<Watchable*> history;
private:
    std::string name;
};

//Todo: add a distructor


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    // virtual Watchable* getRecommendation(Session& s);
private:
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    // virtual Watchable* getRecommendation(Session& s);
private:
};

class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    // virtual Watchable* getRecommendation(Session& s);
private:
};

#endif
