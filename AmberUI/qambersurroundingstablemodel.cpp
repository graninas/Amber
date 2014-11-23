#include "qambersurroundingstablemodel.h"

#include "naming.h"
#include <QDebug>

QAmberSurroundingsTableModel::QAmberSurroundingsTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

/*
QModelIndex QAmberSurroundingsTableModel::index(int row, int column, const QModelIndex &parent) const
{
    qDebug() << "index(" << row << "," << column << ")";
    if (row >= m_data.size()
        || column >= m_header.size())
        return QModelIndex();

    return createIndex(row, column);
}

QModelIndex QAmberSurroundingsTableModel::parent(const QModelIndex &) const
{
    qDebug() << "parent";
    return QModelIndex();
}
*/

int QAmberSurroundingsTableModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "rowCount";
    /*
    if (parent == QModelIndex())
        return m_data.count();
*/
    return 0;
}

int QAmberSurroundingsTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    qDebug() << "columnCount";
    return m_header.size();
}

QVariant QAmberSurroundingsTableModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "data(" << index.row() << "," << index.column() << ")";
    /*
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_data.size())
        return QVariant();

    if (index.column() >= m_data.at(index.row()).size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_data.at(index.row()).at(index.column());

        */

    return QVariant();
}

QVariant QAmberSurroundingsTableModel::headerData(int section, Qt::Orientation /*orientation*/,
                                                  int role) const
{
    qDebug() << "headerData(" << section << ")";
    /*
    if (role == Qt::DisplayRole
            && section >= 0
            && section < m_header.size())
    {
        return QVariant(m_header[section]);
    }
    */
    return QVariant();
}

void QAmberSurroundingsTableModel::setup(const amber::Areas& areas)
{
    qDebug() << "setup";
    /*
    m_data.clear();
    setupHeader();

    std::for_each(areas.begin(), areas.end(),
                  [this](const amber::Areas::value_type& areaDef)
    {
        const amber::Area& area = areaDef.second;
        std::for_each(area.shadows.begin(), area.shadows.end(),
                      [this, &areaDef](const amber::Shadows::value_type& shadowDef)
        {
            QStringList row;
            row.append(QString::fromStdString(naming::areaName(areaDef.first)));
            row.append(QString::fromStdString(naming::shadowName(shadowDef.first)));

            // Warning! Unsafe code.
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::Ground)));
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::Water)));
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::Air)));
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::Sky)));
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::Flora)));
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::Fauna)));
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::AmberDistance)));
            row.append(QString::number(shadowDef.second.structure.at(amber::Element::ChaosDistance)));

            m_data.append(row);
        });
    });
*/
    qDebug() << "end of setup";
}

void QAmberSurroundingsTableModel::setupHeader()
{
    qDebug() << "setup header";

    // Warning! Hardcode.
    QStringList header;
    header.append("Area");
    header.append("Shadow");
    header.append(QString::fromStdString(naming::elementName(amber::Element::Ground)));
    header.append(QString::fromStdString(naming::elementName(amber::Element::Water)));
    header.append(QString::fromStdString(naming::elementName(amber::Element::Air)));
    header.append(QString::fromStdString(naming::elementName(amber::Element::Sky)));
    header.append(QString::fromStdString(naming::elementName(amber::Element::Flora)));
    header.append(QString::fromStdString(naming::elementName(amber::Element::Fauna)));
    header.append(QString::fromStdString(naming::elementName(amber::Element::AmberDistance)));
    header.append(QString::fromStdString(naming::elementName(amber::Element::ChaosDistance)));

    m_header = header;
    qDebug() << "end of setup header";
}
