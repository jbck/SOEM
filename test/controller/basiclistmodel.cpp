#include <QDebug>
#include "basiclistmodel.h"

/**
 * @brief BasicListModel
 * @param prototype
 * @param parent
 */
BasicListModel::BasicListModel(BasicListItem * prototype, QObject * parent) :
    QAbstractListModel(parent), m_prototype(prototype)
{
}

/**
 * @brief BasicListModel::roleNames
 * @return a list of the role names.
 */
QHash<int, QByteArray> BasicListModel::roleNames() const
{
    return m_prototype->roleNames();
}

/**
 * @brief BasicListModel::rowCount
 * @param parent
 * @return the number of rows in the list.
 */
int BasicListModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_list.size();
}

/**
 * @brief Call the role method on the index'th element in the list.
 * @param index
 * @param role
 * @return the role data from the element in the list at the index.
 */
QVariant BasicListModel::data(const QModelIndex &index, int role) const
{
  if(index.row() < 0 || index.row() >= m_list.size())
    return QVariant();
  return m_list.at(index.row())->data(role);
}

/**
 * @brief BasicListModel::~BasicListModel
 */
BasicListModel::~BasicListModel() {
  delete m_prototype;
  clear();
}

/**
 * @brief Append a row to the list.
 * @param item
 */
void BasicListModel::appendRow(BasicListItem * item)
{
  appendRows(QList<BasicListItem*>() << item);
}

/**
 * @brief Append multiple rows to the list.
 * @param items
 */
void BasicListModel::appendRows(const QList<BasicListItem *> &items)
{
  beginInsertRows(QModelIndex(), rowCount(), rowCount()+items.size()-1);
  foreach(BasicListItem * item, items) {
    connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
    m_list.append(item);
  }
  endInsertRows();
}

/**
 * @brief Insert a row at a particular location.
 * @param row
 * @param item
 */
void BasicListModel::insertRow(int row, BasicListItem *item)
{
  beginInsertRows(QModelIndex(), row, row);
  connect(item, SIGNAL(dataChanged()), SLOT(handleItemChange()));
  m_list.insert(row, item);
  endInsertRows();
}

/**
 * @brief Emits the dataChanged signal about a changed list item.
 */
void BasicListModel::handleItemChange()
{
  BasicListItem* item = static_cast<BasicListItem*>(sender());
  QModelIndex index = indexFromItem(item);
  if(index.isValid())
    emit dataChanged(index, index);
}

/**
 * @brief Find the list item based on an identification number.
 * @param id
 * @return the list item that was found.
 */
BasicListItem * BasicListModel::find(const long &id) const
{
  foreach (BasicListItem * item, m_list) {
    if(item->id() == id) return item;
  }
  qDebug() << "Error: BasicListItem: Could not find item with ID:" << id;
  return 0;
}


/**
 * @brief Given a pointer to an item, figure out where it's located in the list.
 * @param item
 * @return the index of the item.
 */
QModelIndex BasicListModel::indexFromItem(const BasicListItem * item) const
{
  Q_ASSERT(item);
  for(int row=0; row<m_list.size(); ++row) {
    if(m_list.at(row) == item) return index(row);
  }
  return QModelIndex();
}

/**
 * @brief Clear all rows from the list.
 */
void BasicListModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_list.length());
    qDeleteAll(m_list);
    m_list.clear();
    endRemoveRows();
}

/**
 * @brief Remove a single row.
 * @param row
 * @param parent
 * @return true if it was possible to remove the row.
 */
bool BasicListModel::removeRow(int row, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  if(row < 0 || row >= m_list.size()) return false;
  beginRemoveRows(QModelIndex(), row, row);
  delete m_list.takeAt(row);
  endRemoveRows();
  return true;
}

/**
 * @brief Remove multiple rows.
 * @param row
 * @param count
 * @param parent
 * @return false if any single row is not in range.
 */
bool BasicListModel::removeRows(int row, int count, const QModelIndex &parent)
{
  Q_UNUSED(parent);
  if(row < 0 || (row+count) > m_list.size()) return false;
  beginRemoveRows(QModelIndex(), row, row+count-1);
  for(int i=0; i<count; ++i) {
    delete m_list.takeAt(row);
  }
  endRemoveRows();
  return true;
}

/**
 * @brief Pull a row out of the list (remove it) and return it.
 * @param row
 * @return the row that was removed.
 */
BasicListItem  * BasicListModel::takeRow(int row)
{
  beginRemoveRows(QModelIndex(), row, row);
  BasicListItem * item = m_list.takeAt(row);
  endRemoveRows();
  return item;
}
