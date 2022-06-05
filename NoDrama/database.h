#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <stdexcept>

class Database
{
private:
    static Database* instance;

    Database();

    QString dbDriver = "QPSQL"; //
    QString dbHostname="localhost"; //
    QString dbName = "nodrama"; // NoDrama
    QString dbUsername="postgres"; //
    QString dbPassword="pass"; //postgres
    int dbPort = 5432; //

    QSqlDatabase db;
public:
    static Database* getInstance();
    QSqlDatabase getDatabase();
    bool openDatabase();
    bool isOpen();
};

#endif // DATABASE_H
