#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <stdexcept>

/**
 * @brief The Database class, contains the information to connect to and open the nodrama database. Bad pratice to keep it like this but choices and time are limited.
 */
class Database
{
private:
    static Database* instance;

    Database();

    /**
     * @brief dbDriver The database driver
     */
    QString dbDriver = "QPSQL"; //
    /**
     * @brief dbHostname The host name of the database
     */
    QString dbHostname="localhost"; //
    /**
     * @brief dbName The name of the database
     */
    QString dbName = "nodrama"; // NoDrama
    /**
     * @brief dbUsername The username of the database
     */
    QString dbUsername="postgres"; //
    /**
     * @brief dbPassword The password of the database
     */
    QString dbPassword="pass"; //postgres

    /**
     * @brief dbPort The post number of the database
     */
    int dbPort = 5432; //

    /**
     * @brief db The database
     */
    QSqlDatabase db;

public:
    static Database* getInstance();
    QSqlDatabase getDatabase();
    bool openDatabase();
    bool isOpen();
};

#endif // DATABASE_H
