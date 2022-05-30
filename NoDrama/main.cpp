#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "database.h"

Database *Database::instance = 0;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //const QUrl url(u"qrc:/NoDrama/main.qml"_qs);
    const QUrl url(u"qrc:/createParty.qml"_qs);
    //const QUrl url("qrc:/main.qml");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
