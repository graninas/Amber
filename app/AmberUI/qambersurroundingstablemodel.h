#ifndef QAMBERSURROUNDINGSTABLEMODEL_H
#define QAMBERSURROUNDINGSTABLEMODEL_H

#include <QAbstractTableModel>

#include <amberstructure.h>

class QAmberSurroundingsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit QAmberSurroundingsTableModel(QObject *parent = 0);

    void setup(const amber::Areas& areas);

//    QModelIndex index(int row, int column, const QModelIndex &parent) const;
//    QModelIndex parent(const QModelIndex &) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation,
                        int role = Qt::DisplayRole) const;

signals:

public slots:

private:

    QStringList m_header;
    QList<QStringList> m_data;

    void setupHeader();

};

#endif // QAMBERSURROUNDINGSTABLEMODEL_H
