#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/1_Assignment1_ShapeBounce/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    QQuickWindow *window = qobject_cast<QQuickWindow *>(engine.rootObjects().at(0));

    Backend backend(nullptr, window->contentItem());
    backend.readFile(
        "D:/Documents/Programming/C++/Study/Game_Development/1_Assignment1_ShapeBounce/config.txt");

    return app.exec();
}
