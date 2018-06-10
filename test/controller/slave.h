#pragma once

#include <QObject>
#include <QString>

#include "basiclistmodel.h"
#include "ethercat.h"
#include "fal/object.h"
#include "fal/subobject.h"


class Slave : public BasicListItem
{
    Q_OBJECT
    Q_ENUMS(Roles)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    Q_PROPERTY(QList<Object*> objectDictionary READ objectDictionary NOTIFY objectDictionaryChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        NameRole,
        StateRole,
    };

    explicit Slave(QObject * parent = nullptr);
    ~Slave();

    long id() const { return m_id; }
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE void recordDeviceState(const quint8 slaveId);
    Q_INVOKABLE void setDeviceState(const quint8 slaveId, quint8 state);
    Q_INVOKABLE void sdoRead(quint16 index, quint16 subindex);
    Q_INVOKABLE void odPrintout();

    QString name() const;
    void setName(const QString &name);
    QString state() const;
    void setState(const quint8 state);
    QString title() const;
    void setTitle(const QString &value);

    QList<Object *> objectDictionary() const;

signals:
    void titleChanged();
    void nameChanged();
    void stateChanged();
    void objectDictionaryChanged();

private:
     long m_id;

    /** All the objects in the slave */
    QList<Object *> m_objectDictionary;

    QString m_title;
    /* TODO: These need to be in their own class, so they can be listed */
    QString m_name;
    QString m_state;
};
