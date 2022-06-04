#ifndef QTUSERTEST_H
#define QTUSERTEST_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>
#include <QRegularExpression>
#include <QMap>
#include "database.h"
#include "qqmlregistration.h"

class User : public QObject
{
    Q_OBJECT
    QML_ELEMENT
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

    bool operator!=(const User& other) const{
        return username!=other.username;
    }

    bool operator=(const User& other) const{
        return username==other.username;
    }

private:
    int id;
    QString username;
    QString password;
    QString email;

    Database* db;
    QSqlQuery query;

    QMap<User, int> *friends;

    QRegularExpression re;

    bool userExists(QString);

    void getDatabase();

public:
    User();
    User(QString username, QString password, QString email);
    User(int, QString, QString, QString);
    User(const User&);
    ~User();

    int getId();
    QString getUsername();
    QString getEmail();


    void setAffinity(User, int);
    Q_INVOKABLE static User createUser(QString, QString, QString);
    void addFriend(User, int);
    static User getUserById(int);
    static User getUserByUsername(QString);
    static User getUserByEmail(QString);

    Q_INVOKABLE static int testLoginUsername(QString username, QString password);
    static int testLoginEmail(QString email, QString password);

    QMap<User, int> *getFriends();
    QMap<User, int> getFriendsByAffinity(int);
};

#endif // QTUSERTEST_H
