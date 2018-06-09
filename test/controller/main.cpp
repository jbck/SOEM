#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "slave.h"
#include "network.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Slave slaveinfo;
    Network network;

    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("slaveinfo", &slaveinfo);
    context->setContextProperty("network", &network);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
