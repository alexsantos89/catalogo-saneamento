#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "trans.h"
#include "questionnode.h"
#include "questionlistmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<QuestionNode>("xyz.aahome89.base", 1, 0, "QuestionNode");
    qmlRegisterType<QuestionListModel>("xyz.aahome89.base", 1, 0, "QuestionListModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // object of our class with "magic" property for translation
    Trans trans(&engine);
    // make this object available from QML side
    engine.rootContext()->setContextProperty("trans", &trans);

    // used to reference files inside QML
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());

    return app.exec();
}
