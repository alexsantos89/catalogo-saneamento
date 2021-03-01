#ifndef PDFLISTMODEL_H
#define PDFLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QObject>
#include <QString>
#include <qqmlfile.h>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QUrl>
#include <QStringList>

class PdfListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool parsed MEMBER m_parsed NOTIFY parsedChanged)
public:
    PdfListModel();

    enum pdflistmodelRoles
    {
        pdfName = Qt::UserRole + 1,
        pdfPath
    };

    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex &parent) const;

    Q_INVOKABLE
    void refreshModel(int questionNodeId);

signals:
    void parsedChanged();

private:
    QList<QList<QString>> m_pdfs;
    bool m_parsed;

};

#endif // PDFLISTMODEL_H
