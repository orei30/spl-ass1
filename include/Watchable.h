#ifndef WATCHABLE_H_
#define WATCHABLE_H_

#include <string>
#include <vector>

class Session;

class Watchable{
public:
    // Constructor
    Watchable(long id, int length, const std::vector<std::string>& tags);
    // Destructor
    virtual ~Watchable();
    // Copy Constructor
    Watchable(const Watchable &other);
    // Copy Assignment
    virtual Watchable& operator=(const Watchable &other);
    virtual std::string toString() const = 0;
    virtual Watchable* getNextWatchable(Session&) const = 0;
    long getId() const;
    int getLen() const;
    std::vector<std::string> getTags() const;
    virtual std::string tagsToString(const std::vector<std::string> &) const;
    virtual Watchable* clone() = 0;
private:
    const long id;
    int length;
    std::vector<std::string> tags;
};

class Movie : public Watchable{
public:
    // Constructor
    Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags);
    // Destructor
    virtual ~Movie();
    // Copy Constructor
    Movie(const Movie &other);
    // Copy Assignment
    virtual Movie& operator=(const Movie &other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual Watchable* clone();
private:
    std::string name;
};


class Episode: public Watchable{
public:
    // Constructors
    Episode(long id, const std::string& seriesName,int length, int season, int episode ,const std::vector<std::string>& tags);
    Episode(long id, const std::string& seriesName,int length, int season, int episode, long nextEpisodeId, const std::vector<std::string>& tags);
    // Destructor
    virtual ~Episode();
    // Copy Constructor
    Episode(const Episode& other);
    // Copy Assignment
    virtual Episode& operator=(const Episode& other);
    virtual std::string toString() const;
    virtual Watchable* getNextWatchable(Session&) const;
    virtual Watchable* clone();
private:
    std::string seriesName;
    int season;
    int episode;
    long nextEpisodeId;
};

#endif
