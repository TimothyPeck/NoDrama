#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <stdexcept>

class Database
{
private:
    static Database* instance;

    Database();

    QString dbDriver = "QPSQL"; // QSQLITE
    QString dbHostname="localhost"; //157.26.106.45
    QString dbName = "nodrama"; //
    QString dbUsername="postgres"; //root
    QString dbPassword="pass"; //root
    int dbPort = 5432; //3306

    QSqlDatabase db;
public:
    static Database* getInstance();
    QSqlDatabase getDatabase();
    bool openDatabase();
    bool isOpen();
};

#endif // DATABASE_H
