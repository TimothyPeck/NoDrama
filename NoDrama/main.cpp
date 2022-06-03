#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <QSqlError>
#include "database.h"
#include "User.h"
#include "party.h"

#include <QDebug>
#include <QCoreApplication>
#include <QDateTime>

Database *Database::instance = 0;

int main(int argc, char *argv[])
{
    qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Database *db=Database::getInstance();
    qDebug() << "database : ";

    QString a = QString::fromLocal8Bit(db->getDatabase().lastError().text().toStdString());
    qDebug() << a;
    qDebug() << "end";
    int tmp=User::testLoginUsername("Jeanne", "coucou123");
    qDebug() << tmp;

    qmlRegisterType<User>("com.myself", 1, 0, "User");

    //const QUrl url(u"qrc:/NoDrama/main.qml"_qs);
    const QUrl url(u"qrc:/main.qml"_qs);
    //const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
