#include "trans.h"

Trans::Trans(QQmlEngine *engine)
{
    _translator = new QTranslator(this);
    _engine = engine;
}

void Trans::selectLanguage(QString language)
{
    // working folder
    QDir dir = QDir(qApp->applicationDirPath()).absolutePath();

    if (!_translator->load(
                // for example, in case of "ru" language the file would be
                // translating-qml_ru.qm
                // extension is set automatically
                QString("translating-qml_%1").arg(language),
                // look for the file in i18n folder within working directory
                QString("%1/i18n").arg(dir.path())
                )
            )
    {
        qDebug() << "Failed to load translation file, falling back to main language";
    }
    // it's a global thing, we can use it anywhere (after #including <QGuiApplication>)
    qApp->installTranslator(_translator);
    _engine->retranslate();

    emit languageChanged();
}
