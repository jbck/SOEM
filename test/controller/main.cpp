#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "slaveinfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    SlaveInfo slaveinfo;

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("slaveinfo", &slaveinfo);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
