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
    Q_PROPERTY(QString p_text MEMBER m_text NOTIFY textChanged())
    Q_PROPERTY(QuestionNode* p_left READ left)
    Q_PROPERTY(QuestionNode* p_right READ right)
    Q_PROPERTY(bool parsed MEMBER m_parsed NOTIFY parsedChanged)

public:
    explicit QuestionNode(unsigned int id, QString textPor, QObject *parent = nullptr);
    explicit QuestionNode(QObject *parent = nullptr);
    QuestionNode* left() const;
    QuestionNode* right() const;
    unsigned int id;
    void set_left(QuestionNode* node);
    void set_right(QuestionNode* node);
    enum Language {Portuguese, English};
    Q_ENUM(Language);
    Q_INVOKABLE
    void start_model();
    Q_INVOKABLE
    QuestionNode *get_rootNode();
    static QVector<QuestionNode*> nodesVector;
    static QuestionNode* rootNode;

signals:
    void textChanged();
    void parsedChanged();
    void requestStart();

private:
    QString m_textPT;
    QString m_textEN;
    QString m_text;
    QuestionNode* m_left;
    QuestionNode* m_right;
    bool m_parsed;

};

#endif // QUESTIONNODE_H
