#include "User.h"

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
}

User::User(std::string username, std::string password, std::string email)
{
    if(username != "" && password != "" && email != ""){
        getDatabase();
        if(!userExists(username) && db->openDatabase())
            createUser(username, password, email);

        this->username=username ;
        this->password=password;
        this->email=email;
    }
}

User::User(int id, std::string username, std::string password, std::string email)
{
    getDatabase();
    this->id=id;
    this->username=username;
    this->password=password;
    this->email=email;
}

User::User(const User& user){
    getDatabase();
    this->id=user.id;
    this->username=user.username;
    this->password=user.password;
    this->email=user.email;
    this->friends=user.friends;
}

void User::setAffinity(User user, int affinity)
{
    if (affinity <= 10 && affinity >= 0)
        this->friends[user] = affinity;

    this->query.prepare("UPDATE Affinities SET affinity = :affinity WHERE fk_user1 = :user_one_id AND fk_user2 = :user_two_id");
    this->query.bindValue(":user_one_id", QVariant::fromValue(this->id));
    this->query.bindValue(":user_two_id", QVariant::fromValue(user.getId()));
    this->query.bindValue(":affinity", QVariant::fromValue(affinity));
    this->query.exec();
}

void User::addFriend(User user, int affinity)
{
    if(affinity >=0 && affinity<=10)
        this->friends.insert(user, affinity);

    this->query.prepare("INSERT INTO Affinities(fk_user1, fk_user2, affinity) VALUES(:user_one_id, :user_two_id, :affinity)");
    this->query.bindValue(":user_one_id", QVariant::fromValue(this->id));
    this->query.bindValue(":user_two_id", QVariant::fromValue(user.getId()));
    this->query.bindValue(":affinity", QVariant::fromValue(affinity));
    this->query.exec();
}

/**
 * @brief User::createUser Adds a user to the database
 * @param username The user's entered username
 * @param password The user's entered password assumes password is pre-encrypted
 * @param email The user's email
 */
User User::createUser(std::string username, std::string password, std::string email)
{
    QRegularExpression re = QRegularExpression(R"(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])");

    static QRegularExpressionMatch match = re.match(QString::fromStdString(email));

    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(username != "" && password != "" && match.hasMatch()){
        query.prepare("INSERT INTO Users(username, email, password) VALUES(:username, :email, :password)");
        query.bindValue(":username", QVariant::fromValue(QString::fromStdString(username)));
        query.bindValue(":email", QVariant::fromValue(QString::fromStdString(email)));
        query.bindValue(":password", QVariant::fromValue(QString::fromStdString(password)));
        query.exec();

        int id = query.lastInsertId().toInt();
        return User(id, username, password,email);
    }
    return User();
}

bool User::userExists(std::string username){
    this->query.prepare("SELECT * FROM Users WHERE username = :username");
    query.bindValue(":username", QVariant::fromValue(QString::fromStdString(username)));
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

    if(std::isdigit(id)){
        // find user in database by id
        query.prepare("SELECT * FROM Users WHERE id_user = :id");
        query.bindValue(":id", QVariant::fromValue(id));
        query.exec();

        if(query.size() == 1)
            ret = User(query.value(0).toInt(), query.value(1).toString().toStdString(), query.value(3).toString().toStdString(), query.value(2).toString().toStdString());

        query.prepare("SELECT * FROM Affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", id);
        query.exec();

        while(query.next()){
            ret.friends.insert(getUserById(query.value(1).toInt()), query.value(2).toInt());
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
User User::getUserByUsername(std::string username)
{
    User ret=User();

    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(username!=""){
        // find user in database by username
        query.prepare("SELECT * FROM Users WHERE username = :username");
        query.bindValue(":username", QVariant::fromValue(QString::fromStdString(username)));
        query.exec();

        if(query.size() == 1)
            ret = User(query.value(1).toString().toStdString(), query.value(3).toString().toStdString(), query.value(2).toString().toStdString());

        query.prepare("SELECT * FROM Affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", ret.getId());
        query.exec();

        while(query.next()){
            ret.friends.insert(getUserById(query.value(1).toInt()), query.value(2).toInt());
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
User User::getUserByEmail(std::string email)
{
    User ret=User();

    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    if(email!=""){
        // find user in database by email
        query.prepare("SELECT * FROM Users WHERE email = :email");
        query.bindValue(":email", QVariant::fromValue(QString::fromStdString(email)));
        query.exec();

        if(query.size() == 1)
            ret = User(query.value(1).toString().toStdString(), query.value(3).toString().toStdString(), query.value(2).toString().toStdString());

        query.prepare("SELECT * FROM Affinities WHERE fk_user1 = :user_one_id");
        query.bindValue(":user_one_id", ret.getId());
        query.exec();

        while(query.next()){
            ret.friends.insert(getUserById(query.value(1).toInt()), query.value(2).toInt());
        }
    }
    return ret;
}

int User::testLoginUsername(std::string username, std::string password)
{
    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    query.prepare("SELECT * FROM Users WHERE username = :username AND password = :password");

    query.bindValue(":username", QVariant::fromValue(username));
    query.bindValue(":password", QVariant::fromValue(password));

    query.exec();

    if(query.size()==1){
        return query.value(0).toInt();
    }

    return -1;
}

int User::testLoginEmail(std::string email, std::string password)
{
    Database* db = db->getInstance();

    QSqlQuery query = QSqlQuery(db->getDatabase());

    query.prepare("SELECT * FROM Users WHERE email = :email AND password = :password");

    query.bindValue(":email", QVariant::fromValue(email));
    query.bindValue(":password", QVariant::fromValue(password));

    query.exec();

    if(query.size()==1){
        return query.value(0).toInt();
    }

    return -1;
}

QMap<User, int> User::getFriends()
{
    // return all friends of user
    return friends;
}

/**
 * @brief User::getFriendsByAffinity Returns all the friends of the current user where the affinity is greater or equal to the minimum affinity provided.
 * @param minAffinity The minimum affinity for the users to be returned
 * @return A std::map of the <user, affinity> pairs.
 */
/*std::map<User, int, const User::cmpByUsernameLength> User::getFriendsByAffinity(int minAffinity) {
    std::map<User, int, const User::cmpByUsernameLength> friendsWithAffinity;

    for (auto it = friends.begin(); it !=friends.end(); ++it)
    {
        if (it->second >= minAffinity)
            friendsWithAffinity.insert(std::pair<User, int>(it->first, it->second));
    }

    return friendsWithAffinity;
}*/

QMap<User, int> User::getFriendsByAffinity(int minAffinity) {
    QMap<User, int> friendsWithAffinity;

    QMapIterator<User, int> i(friends);
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

std::string User::getUsername()
{
    return this->username;
}

std::string User::getEmail()
{
    return this->email;
}

User::~User()
{
    //free(db);
}
