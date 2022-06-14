#include "User.h"
#include <iostream>
#include <QSqlError>

/**
 * @brief  User::getDatabase Creates the database object if it doesn't exist. Also creates the query object. Opens the database.
 */
void User::getDatabase()
{
    if (this->db == nullptr)
    {
        this->db = db->getInstance();
        this->query = QSqlQuery(db->getDatabase());
        this->db->openDatabase();
    }
}

/**
 * @brief User::User Construct a new empty User object
 */
User::User()
{
    getDatabase();
    this->username = "";
    this->password = "";
    this->email = "";
    this->friends = new QMap<User, int>;
}

/**
 * @brief User::User OBSOLETE. Construct a new User object with the given username and password. Does not add to the database.
 * @param username The username of the user
 * @param password  The user's password
 * @param email The user's email
 */
User::User(QString username, QString password, QString email)
{
    if (username != "" && password != "" && email != "")
    {
        getDatabase();
        this->username = username;
        this->password = password;
        this->email = email;
        this->friends = new QMap<User, int>;
    }
}

/**
 * @brief User::User Construct a new User object with the id, username, password, and email.
 * @param id The user's id in the database
 * @param username The username of the user
 * @param password The user's password
 * @param email The user's email
 */

User::User(int id, QString username, QString password, QString email)
{
    getDatabase();
    this->id = id;
    this->username = username;
    this->password = password;
    this->email = email;
    this->friends = new QMap<User, int>;
}

/**
 * @brief User::User Copy constructor for User
 * @param user The User to copy
 */
User::User(const User &user)
{
    getDatabase();
    this->id = user.id;
    this->username = user.username;
    this->password = user.password;
    this->email = user.email;

    this->friends = user.friends;
    this->friends->detach();
}

/**
 * @brief User::User Copy constructor for user class @see User(const User &user)
 * @param u
 */
User::User(User* u)
{
    this->id = u->getId();
    this->username = u->getUsername();
    this->password = u->password;
    this->email = u->getEmail();

    this->friends = u->friends;
    this->friends->detach();
}

/**
 * @brief User::constructor Same as copy constructor @see User(User* u)
 * @param u The user to be copied
 */
void User::constructor(User* u)
{
    this->id = u->id;
    this->username = u->username;
    this->password = u->password;
    this->email = u->email;

    this->friends = u->friends;
    this->friends->detach();
}

/**
 * @brief User::setAffinity Sets the affinity in the database for the user and the given friend.
 * @param user The friend whose affinity is to be updated
 * @param affinity The affinity to set
 */
void User::setAffinity(User user, int affinity)
{
    if (affinity <= 10 && affinity >= 0){
        QMap<User,int>::iterator i;
        for(i = this->friends->begin(); i != friends->end(); i++)
        {
            if(i.key().username == user.getUsername()){
                i.value() = affinity;
                qDebug() << i.key().username << " : " << i.value();
            }
        }
    }

    Database *db = Database::getInstance();

    if (!db->isOpen())
        db->openDatabase();

    db->getDatabase().transaction();
    this->query.prepare("UPDATE nodrama.affinities SET affinity = :affinity WHERE fk_user1 = :user_one_id AND fk_user2 = :user_two_id");
    this->query.bindValue(":user_one_id", QVariant::fromValue(this->id));
    this->query.bindValue(":user_two_id", QVariant::fromValue(user.getId()));
    this->query.bindValue(":affinity", QVariant::fromValue(affinity));
    this->query.exec();
    db->getDatabase().commit();

    qDebug() << "set affinity : " << db->getDatabase().lastError();
}

/**
 * @brief User::addFriend Adds a frind to the user and the database with the given affinity.
 * @param user The user to add as a friend
 * @param affinity The affinity of the friend
 */
void User::addFriend(User user, int affinity)
{
    if (affinity >= 0 && affinity <= 10){
        this->friends->insert(user, affinity);

        Database *db = Database::getInstance();

        if (!db->isOpen())
            db->openDatabase();

        db->getDatabase().transaction();
        this->query.prepare("INSERT INTO nodrama.affinities(fk_user1, fk_user2, affinity) VALUES(:user_one_id, :user_two_id, :affinity)");
        this->query.bindValue(":user_one_id", QVariant::fromValue(this->id));
        this->query.bindValue(":user_two_id", QVariant::fromValue(user.getId()));
        this->query.bindValue(":affinity", QVariant::fromValue(affinity));
        this->query.exec();

        db->getDatabase().commit();

        qDebug() << "add friends last error : " << db->getDatabase().lastError();
    }
}

/**
 * @brief User::createUser Adds a user to the database
 * @param username The user's entered username
 * @param password The user's entered password assumes password is pre-encrypted
 * @param email The user's email
 */
User* User::createUser(QString username, QString password, QString email)
{
    qDebug()<<"username: "<<username;

    email = email.toLower();

    Database *db = Database::getInstance();

    if (!db->isOpen())
        db->openDatabase();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if (username != "" && password != "" && email != "")
    {
        db->getDatabase().transaction();

        query.prepare("INSERT INTO nodrama.users(username, email, password) VALUES (:username, :email, :password)");
        query.bindValue(":username", username);
        query.bindValue(":email", email);
        query.bindValue(":password", password);
        query.exec();

        int id = query.lastInsertId().toInt();

        qDebug()<<query.lastError();

        if (query.lastError().type() == 0)
        {
            db->getDatabase().commit();
            query.finish();
            User* u = new User(id, username, password, email);
            return u;
        }
    }

    query.finish();
    db->getDatabase().rollback();
    User* u = new User(-1, username, password, email);
    return u;
}

/**
 * @brief User::addFriendOrUpdateAffinity Adds the affinity to a user or updates it if the user already has an affinity
 * @param username The username of the user whose affinity needs updating
 * @param affinity The affinity to set
 */
void User::addFriendOrUpdateAffinity(QString username, int affinity)
{
    User *u;
    u = User::getUserByUsername(username);

    QMap<User,int>::iterator i;
    for(i = this->friends->begin(); i != friends->end(); i++)
    {
        qDebug() << i.key().username << " : " << i.value();
        if(i.key().username == u->getUsername()){
            this->setAffinity(u, affinity);
            return;
        }
    }

    this->addFriend(u, affinity);
}

/**
 * @brief User::userExists Checks if the user exists in the database
 * @param username The username to of the user to check
 * @return true If user exists
 * @return false If user doesn't exist
 */
bool User::userExists(QString username)
{
    Database *db = Database::getInstance();

    if (!db->isOpen())
        db->openDatabase();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", QVariant::fromValue((username)));
    query.exec();

    if (query.size() == 0)
        return false;
    else
        return true;
}

/**
 * @brief User::getUserById Finds a user by their id
 * @param id The id of the user to find
 * @return User The found user
 */
User *User::getUserById(int id)
{
    User *ret = new User();

    Database *db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if (!db->isOpen())
        db->openDatabase();

        // find user in database by id
        query.prepare("SELECT * FROM nodrama.users WHERE id_user = :id");
        query.bindValue(":id", QVariant::fromValue(id));
        query.exec();

        while(query.next()){
            ret = new User(query.value(0).toInt(), query.value(1).toString(), query.value(3).toString(), query.value(2).toString());
        }

        query.prepare("SELECT * FROM nodrama.affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", id);
        query.exec();

        while (query.next())
        {
            qDebug() << query.value(1).toInt() << query.value(2).toInt();
            ret->friends->insert(*getUserById(query.value(1).toInt()), query.value(2).toInt());
        }

    return ret;
}

/**
 * @brief User::getUserByUsername Finds a user by their username
 * @param username The username of the user to find
 * @return User The found user
 */
User *User::getUserByUsername(QString username)
{
    User *ret = new User();

    Database *db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if (!db->isOpen())
        db->openDatabase();

    if (username != "")
    {
        // find user in database by username
        query.prepare("SELECT * FROM nodrama.users WHERE username = :username");
        query.bindValue(":username", username);
        query.exec();

        while(query.next()){
            query.first();
            ret = new User(query.value(0).toInt() ,query.value(1).toString(), query.value(3).toString(), query.value(2).toString());
        }

        query.prepare("SELECT * FROM nodrama.affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", ret->getId());
        query.exec();

        while (query.next())
        {
            qDebug() << query.value(0).toInt() << query.value(1).toInt() << query.value(2).toInt();;
            ret->friends->insert(*getUserById(query.value(1).toInt()), query.value(2).toInt());
        }
    }
    return ret;
}

/**
 * @brief User::getUserByEmail Finds a user by their email
 * @param email The email of the user to find
 * @return User The found user
 */
User *User::getUserByEmail(QString email)
{
    User *ret = new User();

    Database *db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if (!db->isOpen())
        db->openDatabase();

    if (email != "")
    {
        // find user in database by email
        query.prepare("SELECT * FROM nodrama.users WHERE email = :email");
        query.bindValue(":email", email);
        query.exec();

        if (query.size() == 1)
            ret = new User(query.value(1).toString(), query.value(3).toString(), query.value(2).toString());

        query.prepare("SELECT * FROM nodrama.affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", ret->getId());
        query.exec();

        while (query.next())
        {
            ret->friends->insert(*getUserById(query.value(1).toInt()), query.value(2).toInt());
        }
    }
    return ret;
}

/**
 * @brief User::testLoginUsername Attempts to login with the given username and password, returns the id of the user if the atttempt was successful, -1 otherwise
 * @param username The username to try
 * @param password The password of the user
 * @return int Id of the user if exists, -1 otherwise
 */
int User::testLoginUsername(QString username, QString password)
{
    Database *db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if (!db->isOpen())
        db->openDatabase();

    query.prepare("SELECT * FROM nodrama.users WHERE username = :username AND password = :password");

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    query.exec();

    while(query.next()){
        query.first();
        return query.value(0).toInt();
    }

    return -1;
}

/**
 * @brief User::testLoginEmail Attempts to login with the given email and password, returns the id of the user if the atttempt was successful, -1 otherwise
 * @param email The email of the user to try
 * @param password The password of the user
 * @return int Id of the user if exists, -1 otherwise
 */
int User::testLoginEmail(QString email, QString password)
{
    Database *db = db->getInstance();

    QString name = (email);
    QString pass = (password);

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if (!db->isOpen())
        db->openDatabase();

    query.prepare("SELECT * FROM nodrama.users WHERE email = :email AND password = :password");

    query.bindValue(":email", name);
    query.bindValue(":password", pass);

    query.exec();

    if (query.size() == 1)
    {
        query.first();
        return query.value(0).toInt();
    }

    return -1;
}

/**
 * @brief User::getFriends Returns the friends of the user
 * @return QMap<User, int>* A pointer to the friends of the user
 */
QMap<User, int> *User::getFriends()
{
    // return all friends of user
    return friends;
}

/**
 * @brief User::getFriendsForDisplay Returns the friends of the user in a way that QML can display them
 * @return QVariantList The list containing the friends of the user
 */
QVariantList User::getFriendsForDisplay()
{
    QVariantList list;

    QMap<User,int>::iterator i;
    for(i = this->friends->begin(); i != friends->end(); i++)
    {
        QVariantMap map;
        qDebug() << i.key().username << " : " << i.value();
        map.insert(i.key().username, i.value());
        list << map;
    }
    return list;
}

/**
 * @brief User::pushElement push an element in a QVariantList. Used in UI because JS function push() doesnt't work.
 * @param l The QVariantList to add the element to
 * @param n The string to add in the list
 * @return QVariantList A list with the new element added
 */
QVariantList User::pushElement(QVariantList l, QString n)
{
    l << n;
    return l;
}

/**
 * @brief User::getFriendsByAffinity Returns all the friends of the current user where the affinity is greater or equal to the minimum affinity provided.
 * @param minAffinity The minimum affinity for the users to be returned
 * @return A QMap of the <user, affinity> pairs.
 */
QMap<User, int> User::getFriendsByAffinity(int minAffinity)
{
    QMap<User, int> friendsWithAffinity;

    QMapIterator<User, int> i(*friends);
    while (i.hasNext())
    {
        i.next();
        if (i.value() >= minAffinity)
            friendsWithAffinity.insert(i.key(), i.value());
    }

    return friendsWithAffinity;
}

/**
 * @brief User::getId Returns the id of the user
 * @return int The id
 */
int User::getId()
{
    return this->id;
}

/**
 * @brief User::getUsername Returns the username of the user
 * @return QString The username
 */
QString User::getUsername() const
{
    return this->username;
}

/**
 * @brief User::getEmail Returns the email of the user
 * @return QString The email
 */
QString User::getEmail()
{
    return this->email;
}

/**
 * @brief User::~User Destroy the User object
 */
User::~User()
{
    // free(db);
}
