#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <stdexcept>

class Database
{
private:
    static Database* instance;

    Database();

    QString dbDriver = "QMYSQL ";
    QString dbHostname="localhost";
    QString dbName = "NoDrama";
    QString dbUsername="root";
    QString dbPassword="root";
    int dbPort=5432;

    QSqlDatabase db;
public:
    static Database* getInstance();
    QSqlDatabase getDatabase();
    bool openDatabase();
    bool isOpen();
    ~Database();
};

#endif // DATABASE_H
