#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "slaveinfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<SlaveInfo>("com.synapticon.somanet.ethercat.slaveinfo", 1, 0, "SlaveInfo");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
