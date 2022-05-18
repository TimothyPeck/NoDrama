#include "database.h"

Database::Database()
{
    db = QSqlDatabase::addDatabase(this->dbDriver);
    db.setHostName(this->dbHostname);
    db.setPort(this->dbPort);
    db.setDatabaseName(this->dbName);
    db.setUserName(this->dbUsername);
    db.setPassword(this->dbPassword);
}

Database* Database::getInstance(){
    if(!instance){
        instance = new Database;
    }
    return instance;
}

 QSqlDatabase Database::getDatabase(){
    return db;
}

bool Database::openDatabase(){
    return db.isOpen() ? true : db.open();
}

bool Database::isOpen(){
    return db.isOpen();
}

Database::~Database(){
    free(instance);
}
