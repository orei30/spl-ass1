#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

class Session;

enum ActionStatus{
	PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
	// Constructor
	BaseAction();
	// Destructor
    virtual ~BaseAction();
	// Copy Constructor
    BaseAction(const BaseAction &other);
	ActionStatus getStatus() const;
	virtual void act(Session& sess)=0;
	virtual std::string toString() const=0;
	virtual BaseAction* clone() = 0;
	std::string statusToString() const;
protected:
	void complete();
	void error(const std::string& errorMsg);
	std::string getErrorMsg() const;
private:
	std::string errorMsg;
	ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
	CreateUser();
    virtual ~CreateUser();
    CreateUser(const BaseAction &other);
	virtual void act(Session& sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};

class ChangeActiveUser : public BaseAction {
public:
	ChangeActiveUser();
    virtual ~ChangeActiveUser();
    ChangeActiveUser(const BaseAction &other);
	virtual void act(Session& sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};

class DeleteUser : public BaseAction {
public:
	DeleteUser();
    virtual ~DeleteUser();
    DeleteUser(const BaseAction &other);
	virtual void act(Session & sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};

class DuplicateUser : public BaseAction {
public:
	DuplicateUser();
    virtual ~DuplicateUser();
    DuplicateUser(const BaseAction &other);
	virtual void act(Session & sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};

class PrintContentList : public BaseAction {
public:
	PrintContentList();
    virtual ~PrintContentList();
    PrintContentList(const BaseAction &other);
	virtual void act (Session& sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};

class PrintWatchHistory : public BaseAction {
public:
	PrintWatchHistory();
    virtual ~PrintWatchHistory();
    PrintWatchHistory(const BaseAction &other);
	virtual void act (Session& sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};


class Watch : public BaseAction {
public:
	Watch();
	Watch(long id);
    virtual ~Watch();
    Watch(const Watch &other);
	virtual void act(Session& sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
private:
	long idWatch;
};

class PrintActionsLog : public BaseAction {
public:
	PrintActionsLog();
    virtual ~PrintActionsLog();
    PrintActionsLog(const BaseAction &other);
	virtual void act(Session& sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};

class Exit : public BaseAction {
public:
	Exit();
    virtual ~Exit();
    Exit(const BaseAction &other);
	virtual void act(Session& sess);
	virtual std::string toString() const;
	virtual BaseAction* clone();
};
#endif
