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

/**
 * @brief The User class
 */
class User : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ getUsername() CONSTANT)
    Q_PROPERTY(QString email READ getEmail() CONSTANT)
    QML_ELEMENT
public:

    /**
     * @brief The cmpByUsernameLength struct, used to compare two users by their usernames. Name is not a good representation of implementation, does not really compare by length
     */
    struct cmpByUsernameLength
    {
        /**
         * @brief operator () compares two users by their username
         * @param lhs
         * @param rhs
         * @return
         */
        bool operator()(const User& lhs, const User& rhs) const
        {
            return (lhs.username <= rhs.username);
        }
    };

    /**
     * @brief operator () compares two users by their username @see cmpByUsernameLength
     * @param lhs
     * @param rhs
     * @return
     */
    inline bool operator()(const User& lhs, const User& rhs) const
    {
        return (lhs.username <= rhs.username);
    }

    /**
     * @brief operator < Compares users, uses the username
     * @param other
     * @return
     */
    bool operator<(const User& other) const{
        return username <= other.username;
    }

    /**
     * @brief operator == Equality operator for the user class, uses the username
     * @param other
     * @return
     */
    bool operator==(const User& other) const{
        return username==other.username;
    }

    /**
     * @brief operator != Inequality operator for the user class, uses the username
     * @param other
     * @return
     */
    bool operator!=(const User& other) const{
        return username!=other.username;
    }

    /**
     * @brief operator= Assignement operator for the user class, returns reference to self
     * @param other
     * @return
     */
    Q_INVOKABLE User& operator=(const User& other){
        id=other.id;
        username=other.username;
        password=other.password;
        email=other.email;
        friends=other.friends;
        friends->detach();
        re=other.re;

        return *this;
    }

private:
    /**
     * @brief id Id of the user in the database
     */
    int id;
    /**
     * @brief username Username of the user
     */
    QString username;
    /**
     * @brief password The password of the user
     */
    QString password;
    /**
     * @brief email The email of the user
     */
    QString email;

    Database* db;
    QSqlQuery query;

    /**
     * @brief friends The friends of the user with corresponding affinity
     */
    QMap<User, int> *friends;

    QRegularExpression re;

    static bool userExists(QString);

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
    Q_INVOKABLE QString getUsername() const;
    Q_INVOKABLE QString getEmail();


    Q_INVOKABLE void setAffinity(User, int);
    Q_INVOKABLE static User* createUser(QString, QString, QString);
    Q_INVOKABLE void addFriendOrUpdateAffinity(QString username, int affinity);
    Q_INVOKABLE void addFriend(User, int);
    Q_INVOKABLE static User* getUserById(int);
    Q_INVOKABLE static User* getUserByUsername(QString);
    Q_INVOKABLE static User* getUserByEmail(QString);

    Q_INVOKABLE static int testLoginUsername(QString username, QString password);
    Q_INVOKABLE static int testLoginEmail(QString email, QString password);

    Q_INVOKABLE QMap<User, int> *getFriends();
    Q_INVOKABLE QVariantList getFriendsForDisplay();
    Q_INVOKABLE QVariantList pushElement(QVariantList l, QString n);
    Q_INVOKABLE QMap<User, int> getFriendsByAffinity(int);
};

#endif // QTUSERTEST_H
