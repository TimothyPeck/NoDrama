#ifndef QTUSERTEST_H
#define QTUSERTEST_H

#include <QObject>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QVariant>
#include <QRegularExpression>
#include <QMap>
#include "database.h"
//#include "qqmlregistration.h"
#include <QtQml/qqmlregistration.h>

class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername() CONSTANT)
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

    Q_INVOKABLE bool operator=(const User& other) const{
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
    Q_INVOKABLE User();
    Q_INVOKABLE User(QString username, QString password, QString email);
    Q_INVOKABLE User(int, QString, QString, QString);
    Q_INVOKABLE User(const User&);
    Q_INVOKABLE User(User*);
    Q_INVOKABLE void constructor(User*);
    ~User();

    Q_INVOKABLE int getId();
    Q_INVOKABLE QString getUsername();
    Q_INVOKABLE QString getEmail();


    Q_INVOKABLE void setAffinity(User, int);
    Q_INVOKABLE static User createUser(QString, QString, QString);
    Q_INVOKABLE void addFriend(User, int);
    Q_INVOKABLE static User* getUserById(int);
    Q_INVOKABLE static User* getUserByUsername(QString);
    Q_INVOKABLE static User* getUserByEmail(QString);

    Q_INVOKABLE static int testLoginUsername(QString username, QString password);
    Q_INVOKABLE static int testLoginEmail(QString email, QString password);

    Q_INVOKABLE QMap<User, int> *getFriends();
    Q_INVOKABLE QMap<User, int> getFriendsByAffinity(int);
};

#endif // QTUSERTEST_H
