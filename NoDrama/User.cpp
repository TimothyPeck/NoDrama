#include "User.h"

#include <iostream>

#include <QSqlError>

void User::getDatabase(){
    if(this->db==nullptr){
        this->db = db->getInstance();



        this->query = QSqlQuery(db->getDatabase());

        this->db->openDatabase();
    }
}

User::User(){
    getDatabase();
    this->username="";
    this->password="";
    this->email="";
    this->friends=new QMap<User, int>;
}

User::User(QString username, QString password, QString email)
{
    if(username != "" && password != "" && email != ""){
        getDatabase();
        /*if(!userExists(username) && db->openDatabase())
            createUser(username, password, email);
*/
        this->username=username ;
        this->password=password;
        this->email=email;
        this->friends=new QMap<User, int>;
    }
}

User::User(int id, QString username, QString password, QString email)
{
    getDatabase();
    this->id=id;
    this->username=username;
    this->password=password;
    this->email=email;
    this->friends=new QMap<User, int>;
}

User::User(const User& user){
    getDatabase();
    this->id=user.id;
    this->username=user.username;
    this->password=user.password;
    this->email=user.email;

    this->friends=user.friends;
    this->friends->detach();
}

void User::setAffinity(User user, int affinity)
{
    if (affinity <= 10 && affinity >= 0)
        this->friends->find(user).value() = affinity;

    db->getDatabase().transaction();
    this->query.prepare("UPDATE nodrama.affinities SET affinity = :affinity WHERE fk_user1 = :user_one_id AND fk_user2 = :user_two_id");
    this->query.bindValue(":user_one_id", QVariant::fromValue(this->id));
    this->query.bindValue(":user_two_id", QVariant::fromValue(user.getId()));
    this->query.bindValue(":affinity", QVariant::fromValue(affinity));
    this->query.exec();
    db->getDatabase().commit();
}

void User::addFriend(User user, int affinity)
{
    if(affinity >=0 && affinity<=10)
        this->friends->insert(user, affinity);


    db->getDatabase().transaction();
    this->query.prepare("INSERT INTO nodrama.affinities(fk_user1, fk_user2, affinity) VALUES(:user_one_id, :user_two_id, :affinity)");
    this->query.bindValue(":user_one_id", QVariant::fromValue(this->id));
    this->query.bindValue(":user_two_id", QVariant::fromValue(user.getId()));
    this->query.bindValue(":affinity", QVariant::fromValue(affinity));
    this->query.exec();

    db->getDatabase().commit();
}

/**
 * @brief User::createUser Adds a user to the database
 * @param username The user's entered username
 * @param password The user's entered password assumes password is pre-encrypted
 * @param email The user's email
 */
User User::createUser(QString username, QString password, QString email)
{
    //QString expression=R"([a-zA-Z0-9!#$%&'*+-/?^_`{|}~]+@[a-zA-Z0-9!#$%&'*+-/?^_`{|}~]+(\.[a-zA-Z0-9!#$%&'*+-/?^_`{|}~]{2,})+)";
    //QRegularExpression re = QRegularExpression(expression, QRegularExpression::CaseInsensitiveOption);

    email = email.toLower();

    Database* db = Database::getInstance();

    if(!db->isOpen())
        db->openDatabase();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(username != "" && password != "" && email != ""){
        db->getDatabase().transaction();

        query.prepare("INSERT INTO nodrama.users(username, email, password) VALUES (:username, :email, :password)");
        query.bindValue(":username", username);
        query.bindValue(":email", email);
        query.bindValue(":password", password);
        query.exec();

        int id = query.lastInsertId().toInt();

        if(query.lastError().type()==0){
            db->getDatabase().commit();
            query.finish();
            return User(id, username, password,email);
        }
    }

    query.finish();
    db->getDatabase().rollback();
    return User(-1, username, password, email);
}

bool User::userExists(QString username){
    getDatabase();
    this->query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", QVariant::fromValue((username)));
    query.exec();

    if(query.size() == 0)
        return false;
    else
        return true;
}

/**
 * @brief Finds a user by their id
 *
 * @param id The id of the user to find
 * @return User The found user
 */
User User::getUserById(int id)
{
    User ret=User();

    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    if(std::isdigit(id)){
        // find user in database by id
        query.prepare("SELECT * FROM nodrama.users WHERE id_user = :id");
        query.bindValue(":id", QVariant::fromValue(id));
        query.exec();

        if(query.size() == 1)
            ret = User(query.value(0).toInt(), query.value(1).toString(), query.value(3).toString(), query.value(2).toString());

        query.prepare("SELECT * FROM nodrama.affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", id);
        query.exec();

        while(query.next()){
            ret.friends->insert(getUserById(query.value(1).toInt()), query.value(2).toInt());
        }
    }

    return ret;
}

/**
 * @brief Finds a user by their username
 *
 * @param username The username of the user to find
 * @return User The found user
 */
User User::getUserByUsername(QString username)
{
    User ret=User();

    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    if(username!=""){
        // find user in database by username
        query.prepare("SELECT * FROM nodrama.users WHERE username = :username");
        query.bindValue(":username", QVariant::fromValue((username)));
        query.exec();

        if(query.size() == 1)
            ret = User(query.value(1).toString(), query.value(3).toString(), query.value(2).toString());

        query.prepare("SELECT * FROM nodrama.affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", ret.getId());
        query.exec();

        while(query.next()){
            ret.friends->insert(getUserById(query.value(1).toInt()), query.value(2).toInt());
        }
    }
    return ret;
}

/**
 * @brief Finds a user by their email
 *
 * @param email The email of the user to find
 * @return User The found user
 */
User User::getUserByEmail(QString email)
{
    User ret=User();

    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    if(email!=""){
        // find user in database by email
        query.prepare("SELECT * FROM nodrama.users WHERE email = :email");
        query.bindValue(":email", email);
        query.exec();

        if(query.size() == 1)
            ret = User(query.value(1).toString(), query.value(3).toString(), query.value(2).toString());

        query.prepare("SELECT * FROM nodrama.affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", ret.getId());
        query.exec();

        while(query.next()){
            ret.friends->insert(getUserById(query.value(1).toInt()), query.value(2).toInt());
        }
    }
    return ret;
}

int User::testLoginUsername(QString username, QString password)
{
    Database* db = db->getInstance();



    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    //qDebug() << QSqlDatabase::drivers();

    //qDebug() << db->getDatabase().lastError();

    //qDebug() << "Open? "<<db->isOpen();

    query.prepare("SELECT * FROM nodrama.users WHERE username = :username AND password = :password");

    query.bindValue(":username", username);
    query.bindValue(":password", password);

    query.exec();

    if(query.size()==1){
        query.first();
        return query.value(0).toInt();
    }

    return -1;
}

int User::testLoginEmail(QString email, QString password)
{
    Database* db = db->getInstance();

    QString name=(email);
    QString pass=(password);

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(!db->isOpen())
        db->openDatabase();

    query.prepare("SELECT * FROM nodrama.users WHERE email = :email AND password = :password");

    query.bindValue(":email", name);
    query.bindValue(":password", pass);

    query.exec();

    if(query.size()==1){
        query.first();
        return query.value(0).toInt();
    }

    return -1;
}

QMap<User, int> *User::getFriends()
{
    // return all friends of user
    return friends;
}

/**
 * @brief User::getFriendsByAffinity Returns all the friends of the current user where the affinity is greater or equal to the minimum affinity provided.
 * @param minAffinity The minimum affinity for the users to be returned
 * @return A QMap of the <user, affinity> pairs.
 */

QMap<User, int> User::getFriendsByAffinity(int minAffinity) {
    QMap<User, int> friendsWithAffinity;

    QMapIterator<User, int> i(*friends);
    while (i.hasNext()) {
        i.next();
        if (i.value() >= minAffinity)
            friendsWithAffinity.insert(i.key(), i.value());
    }

    return friendsWithAffinity;
}



int User::getId()
{
    return this->id;
}

QString User::getUsername()
{
    return this->username;
}

QString User::getEmail()
{
    return this->email;
}

User::~User()
{
    //free(db);
}
