#include "questionlistmodel.h"

QuestionListModel::QuestionListModel()
{

}

QVariant QuestionListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= m_questions.size())
        return QVariant();

    QuestionNode* pQuestionNode = m_questions[index.row()];

    if (!pQuestionNode)
        return QVariant();

    switch (role)
    {
        case TextQuestionRole:
            return pQuestionNode->get_text();
        case TextColorRole:
            return pQuestionNode->get_text();
    }

    return QVariant();

}

QHash<int, QByteArray> QuestionListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[TextQuestionRole] = "questionText";
    roles[TextColorRole] = "questionColor";

    return roles;
}

int QuestionListModel::rowCount(const QModelIndex &parent) const
{
    return m_questions.size();
}

void QuestionListModel::appendQuestion(QuestionNode *questionNode)
{
    int insertIndex = m_questions.size();

    beginInsertRows(QModelIndex(), insertIndex, insertIndex);

    m_questions.insert(m_questions.begin() + insertIndex, questionNode);

    endInsertRows();
}
