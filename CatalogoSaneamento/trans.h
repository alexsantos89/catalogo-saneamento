#ifndef TRANS_H
#define TRANS_H

#include <QObject>
#include <QTranslator>
#include <QDebug>
#include <QGuiApplication>
#include <QDir>
#include <QQmlEngine>

class Trans : public QObject
{
    Q_OBJECT

public:
    Trans(QQmlEngine *engine);

    Q_INVOKABLE void selectLanguage(QString language);

signals:
    void languageChanged();

private:
    QTranslator *_translator;
    QQmlEngine *_engine;
};

#endif // TRANS_H
