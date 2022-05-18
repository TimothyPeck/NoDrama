#ifndef QTUSERTEST_H
#define QTUSERTEST_H

//#include "QtUserTest_global.h"

// Production includes
#include <string>
#include <vector>
#include <map>

//#include <QtCore/qglobal.h>
#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>
#include <QRegularExpression>
#include <QMap>
#include "database.h"

class User
{
public:
    struct cmpByUsernameLength
    {
        bool operator()(const User& lhs, const User& rhs) const
        {
            return (lhs.username <= rhs.username);
        }
    };

    inline bool operator()(const User& lhs, const User& rhs) const
    {
        return (lhs.username <= rhs.username);
    }

    bool operator<(const User& other) const{
        return username <= other.username;
    }

    bool operator==(const User& other) const{
        return username==other.username;
    }

    bool operator=(const User& other) const{
        return username==other.username;
    }

private:
    int id;
    std::string username;
    std::string password;
    std::string email;

    Database* db;
    QSqlQuery query;

    QMap<User, int> friends;

    QRegularExpression re;

    bool userExists(std::string);

    void getDatabase();

public:
    User();
    User(std::string username, std::string password, std::string email);
    User(int, std::string, std::string, std::string);
    User(const User&);
    ~User();

    int getId();
    std::string getUsername();
    std::string getEmail();


    void setAffinity(User, int);
    static User createUser(std::string, std::string, std::string);
    void addFriend(User, int);
    static User getUserById(int);
    static User getUserByUsername(std::string);
    static User getUserByEmail(std::string);

    static int testLoginUsername(std::string username, std::string password);
    static int testLoginEmail(std::string email, std::string password);

    QMap<User, int> getFriends();
    QMap<User, int> getFriendsByAffinity(int);
};

#endif // QTUSERTEST_H
