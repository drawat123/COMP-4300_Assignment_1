#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Backend>("com.company.shapebounce", 1, 0, "Backend");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/1_Assignment1_ShapeBounce/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
