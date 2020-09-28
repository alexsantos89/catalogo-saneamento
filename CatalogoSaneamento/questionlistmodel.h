#ifndef QUESTIONLISTMODEL_H
#define QUESTIONLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "questionnode.h"

class QuestionListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    QuestionListModel();

    enum QuestionListModelRoles
    {
        TextQuestionRole = Qt::UserRole + 1,
        TextColorRole
    };

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent) const;

    Q_INVOKABLE
    void appendQuestion(QuestionNode* questionNode);

private:
    QList<QuestionNode*> m_questions;

};

#endif // QUESTIONLISTMODEL_H
