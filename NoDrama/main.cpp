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
#include <QQmlContext>

Database *Database::instance = 0;

int main(int argc, char *argv[])
{
    qputenv("QT_DEBUG_PLUGINS", QByteArray("1"));

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Database *db=Database::getInstance();
    //qDebug() << "database : " << db->getDatabase().databaseName();

    //QString a = QString::fromLocal8Bit(db->getDatabase().lastError().text().toStdString());

    db->openDatabase();
    //qDebug() << "last error : " << a;

    //int tmp=User::testLoginUsername("A", "A");
    //qDebug() << tmp;

    //User* u = User::getUserById(tmp);
    //qDebug() << u->getUsername();

    // -> utilisé pour créer une instance d'un objet qml du type "User" -> portée seulement le fichier ou l'objet est instancié
    qmlRegisterType<User>("com.myself", 1, 0, "User");
    qmlRegisterType<Party>("com.myself", 1, 0, "Party");
    User *currentUser = new User();
    Party *currentParty = new Party();
    User *tmpUser = new User();

    const QUrl url(u"qrc:/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlContext* rootContext = engine.rootContext();
    // Utilisé pour transmettre une instance d'un objet à la partie QML -> portée dans tous les fichiers
    rootContext->setContextProperty("currentUser", currentUser);
    rootContext->setContextProperty("tmpUser", tmpUser);
    rootContext->setContextProperty("currentParty", currentParty);

    return app.exec();
}
