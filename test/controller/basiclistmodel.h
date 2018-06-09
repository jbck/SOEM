#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QVariant>

class BasicListItem: public QObject {
  Q_OBJECT

public:
  BasicListItem(QObject* parent = 0) : QObject(parent) {}
  virtual ~BasicListItem() {}

  virtual long id() const = 0;
  virtual QVariant data(int role) const = 0;
  virtual QHash<int, QByteArray> roleNames() const = 0;

signals:
  void dataChanged();
};

class BasicListModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit BasicListModel(BasicListItem * prototype, QObject * parent = 0);
  ~BasicListModel();
  Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  void appendRow(BasicListItem* item);
  void appendRows(const QList<BasicListItem*> &items);
  void insertRow(int row, BasicListItem* item);
  bool removeRow(int row, const QModelIndex &parent = QModelIndex());
  bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
  BasicListItem * takeRow(int row);
  BasicListItem * find(const long &id) const;
  QModelIndex indexFromItem( const BasicListItem * item) const;
  void clear();

  // Set this in the inherited model.
  Q_INVOKABLE virtual void setData(const long id, const QVariant &value, int role = Qt::EditRole) = 0;

protected:
  QHash<int, QByteArray> roleNames() const;

  // Accessor for the class that inherits this.
  QList<BasicListItem*> & getList() { return m_list; }

private slots:
  void handleItemChange();

private:
  BasicListItem* m_prototype;
  QList<BasicListItem*> m_list;
};
