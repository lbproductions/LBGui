#ifndef OBJECTLISTMODEL_H
#define OBJECTLISTMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>

namespace LBGui {

class ObjectListModelBase : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ObjectListModelBase(QObject *parent = 0);

protected slots:
    virtual void objectInserted(QSharedPointer<QObject> object) = 0;
    virtual void objectUpdated(QSharedPointer<QObject> object) = 0;
    virtual void objectRemoved(QSharedPointer<QObject> object) = 0;
};

template<class T>
class ObjectListModel : public ObjectListModelBase
{
public:
    explicit ObjectListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    virtual int rowOf(QSharedPointer<QObject> object) const;

    QSharedPointer<T> objectByIndex(const QModelIndex &index) const;
    virtual QList<QSharedPointer<T> > objects() const = 0;

protected:
    void objectInserted(QSharedPointer<QObject> object) Q_DECL_OVERRIDE;
    void objectUpdated(QSharedPointer<QObject> object) Q_DECL_OVERRIDE;
    void objectRemoved(QSharedPointer<QObject> object) Q_DECL_OVERRIDE;

private:
    QHash<QSharedPointer<T>, int> m_rows;
    void adjustExistingRows();
};

}

using namespace LBGui;

template<class T>
QSharedPointer<T> ObjectListModel<T>::objectByIndex(const QModelIndex &index) const
{
    if(index.row() >= objects().size())
        return QSharedPointer<T>();

    return objects().at(index.row());
}

template<class T>
ObjectListModel<T>::ObjectListModel(QObject *parent) :
    ObjectListModelBase(parent)
{
}

template<class T>
int ObjectListModel<T>::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return objects().size();
}

template<class T>
int ObjectListModel<T>::rowOf(QSharedPointer<QObject> object) const
{
    if(m_rows.contains(qSharedPointerCast<T>(object)))
        return m_rows.value(qSharedPointerCast<T>(object));

    return objects().indexOf(qSharedPointerCast<T>(object));
}

template<class T>
void ObjectListModel<T>::objectInserted(QSharedPointer<QObject> object)
{
    int row = rowOf(object);
    if(row < 0)
        return;

    beginInsertRows(QModelIndex(), row, row);
    m_rows.insert(qSharedPointerCast<T>(object), row);
    adjustExistingRows();
    endInsertRows();
}

template<class T>
void ObjectListModel<T>::objectUpdated(QSharedPointer<QObject> object)
{
    int row = rowOf(object);
    if(row < 0)
        return;

    emit dataChanged(index(row), index(row));
}

template<class T>
void ObjectListModel<T>::objectRemoved(QSharedPointer<QObject> object)
{
    int row = rowOf(object);
    if(row < 0)
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_rows.remove(qSharedPointerCast<T>(object));
    adjustExistingRows();
    endRemoveRows();
}

template<class T>
void ObjectListModel<T>::adjustExistingRows()
{
    int i = 0;
    foreach(QSharedPointer<T> object, objects()) {
        if(m_rows.contains(object))
            m_rows.insert(object, i);
        ++i;
    }
}

#endif // OBJECTLISTMODEL_H
