#include "pdflistmodel.h"

PdfListModel::PdfListModel()
{

}

QVariant PdfListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() >= m_pdfs.size())
        return QVariant();

    QList<QString> pPdfs = m_pdfs[index.row()];

    switch (role)
    {
        case pdfName:
            return pPdfs[0];
        case pdfPath:
            return pPdfs[1];
    }

    return QVariant();

}

QHash<int, QByteArray> PdfListModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[pdfName] = "pdfName";
    roles[pdfPath] = "pdfPath";

    return roles;
}

int PdfListModel::rowCount(const QModelIndex &parent) const
{
    return m_pdfs.size();
}

void PdfListModel::refreshModel(int questionNodeId)
{
    beginResetModel();

    m_parsed = false;
    m_pdfs.clear();

    QUrl fileURL = QUrl::fromLocalFile("resources/pdf_files.csv");
    QString fileName = QQmlFile::urlToLocalFileOrQrc(fileURL);
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
                    continue;
                }
                QList<QString> pdf;
                pdf.append(v.at(1));
                pdf.append(v.at(2).trimmed());
                if (id == questionNodeId) {
                    m_pdfs.append(pdf);
                }
            }
        }
    }

    if (m_pdfs.size() > 0) {
        //return parsed true
        m_parsed = true;

    } else {
        m_parsed = false;
    }

    emit parsedChanged();
    endResetModel();
}

