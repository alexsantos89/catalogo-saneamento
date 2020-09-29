#include "questionnode.h"

QuestionNode::QuestionNode(unsigned int id, QString text, QObject *parent) : QObject(parent) , nodeId(id), m_text(text)
{
}

QuestionNode::QuestionNode(QObject *parent) : QObject(parent)
{
}

QuestionNode *QuestionNode::left() const
{
    return m_left;
}

QuestionNode *QuestionNode::right() const
{
    return m_right;
}

void QuestionNode::set_left(QuestionNode *node)
{
    m_left = node;
}

void QuestionNode::set_right(QuestionNode *node)
{
    m_right = node;
}

void QuestionNode::start_model()
{
    //initialize local and static variables
    QUrl fileURL = QUrl::fromLocalFile("resources/binary_tree.csv");
    m_parsed = false;
    QVector<QStringList> parsedFileLines(200);

    QString fileName = QQmlFile::urlToLocalFileOrQrc(fileURL);
    fileName = QString("binary_tree.csv");
    if (QFile::exists(fileName)) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            while (!file.atEnd()) {
                QByteArray data = file.readLine();
                //wordList.append(line.split(',').first());
                //QByteArray data = file.readAll();
                QTextCodec *codec = QTextCodec::codecForHtml(data);
                QString line = codec->toUnicode(data);
                qDebug() << line;
                bool flag;
                QStringList v = line.split(",");
                int id = v.first().toInt(&flag);
                if(!flag){
                    qDebug() << "Error during conversion to uint";
                    m_parsed = false;
                    emit parsedChanged();
                    return;
                }
                parsedFileLines[id] = v;
                nodesVector[id] = new QuestionNode(id,v.at(1));
            }
        }
    }
    else
    {
        //if file does not exist, parsed false and return
        m_parsed = false;
        emit parsedChanged();
        return;
    }

    //assign root node
    QuestionNode::rootNode = nodesVector[0];

    //iterate over the nodes vector to initialize the binary tree
    for (int i=0; i < nodesVector.size(); i++)
    {
        bool flag1=false,flag2=false;

        //if nullptr continue to next iteration
        if(!nodesVector.at(i))
        {
            continue;
        }

        //get the left and right ids
        int leftId = parsedFileLines[i].at(2).toInt(&flag1);
        int rightId = parsedFileLines[i].at(3).toInt(&flag2);

        //If the csv file has wrong syntax for children id then return
        if(!flag1 || !flag2)
        {
            m_parsed = false;
            emit parsedChanged();
            return;
        }

        //if left child is a valid node then assign
        if(leftId != -1)
            nodesVector[i]->set_left(nodesVector.at(leftId));

        //if right child is a valid node then assign
        if(rightId != -1)
            nodesVector[i]->set_right(nodesVector.at(rightId));
    }

    //return parsed true
    m_parsed = true;
    emit parsedChanged();

}

QuestionNode *QuestionNode::get_rootNode()
{
    return rootNode;
}

QString QuestionNode::get_text() const
{
    return m_text;
}

void QuestionNode::set_text(QString text)
{
    m_text = text;
}

//Initialize static members
QVector<QuestionNode*> QuestionNode::nodesVector = QVector<QuestionNode*>(200,nullptr);
QuestionNode* QuestionNode::rootNode = nullptr;
