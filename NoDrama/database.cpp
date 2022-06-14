#include "database.h"

/**
 * @brief Database::Database Construct a new Database singleton object
 */
Database::Database()
{
    db = QSqlDatabase::addDatabase(this->dbDriver);
    db.setHostName(this->dbHostname);
    db.setPort(this->dbPort);
    db.setDatabaseName(this->dbName);
    db.setUserName(this->dbUsername);
    db.setPassword(this->dbPassword);
}

/**
 * @brief Database::getInstance Returns the Database singleton object, or creates one if it doesn't exist
 * @return Database* Returns the Database singleton object
 */
Database* Database::getInstance(){
    if(!instance){
        instance = new Database;
    }
    return instance;
}

/**
 * @brief Database::getDatabase returns the database obect
 * @return QSqlDatabase returns the database obect
 */
 QSqlDatabase Database::getDatabase(){
    return db;
}

/**
 * @brief Checks if the db is open, if it is returns true, otherwise tries to open the database and returns true if it succeeds
 * 
 * @return true If db open or opened
 * @return false Id unable to open db
 */
bool Database::openDatabase(){
    return db.isOpen() ? true : db.open();
}

/**
 * @brief Returns whether the database is open or not
 * 
 * @return true if db is open
 * @return false if db is closed
 */
bool Database::isOpen(){
    return db.isOpen();
}
