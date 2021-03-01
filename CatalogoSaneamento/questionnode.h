#ifndef QUESTIONNODE_H
#define QUESTIONNODE_H

#include <QObject>
#include <QString>
#include <qqmlfile.h>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QUrl>
#include <QStringList>
#include <QVector>

class QuestionNode : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString p_text READ get_text NOTIFY textChanged())
    Q_PROPERTY(QuestionNode* p_left READ left)
    Q_PROPERTY(QuestionNode* p_right READ right)
    Q_PROPERTY(bool parsed MEMBER m_parsed NOTIFY parsedChanged)
    Q_PROPERTY(unsigned int p_id MEMBER nodeId)

public:
    explicit QuestionNode(unsigned int nodeId, QString textPor, QString textEn, QObject *parent = nullptr);
    explicit QuestionNode(QObject *parent = nullptr);
    QuestionNode* left() const;
    QuestionNode* right() const;
    unsigned int nodeId;
    void set_left(QuestionNode* node);
    void set_right(QuestionNode* node);
    enum Language {Portuguese, English};
    Q_ENUM(Language);
    Q_INVOKABLE
    void start_model();
    Q_INVOKABLE
    QuestionNode *get_rootNode();
    QString get_text() const;
    Q_INVOKABLE
    void set_text(QString textPor, QString textEn);
    Q_INVOKABLE
    static void set_language(Language language);
    static QVector<QuestionNode*> nodesVector;
    static QuestionNode* rootNode;
    static Language actualLanguage;

signals:
    void textChanged();
    void parsedChanged();

private:
    QString m_textPT;
    QString m_textEN;
    QuestionNode* m_left = nullptr;
    QuestionNode* m_right = nullptr;
    bool m_parsed;
};

#endif // QUESTIONNODE_H
