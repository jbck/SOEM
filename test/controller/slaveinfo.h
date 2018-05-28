#ifndef SLAVEINFO_H
#define SLAVEINFO_H

#include <QObject>
#include <QString>

#include "ethercat.h"
#include "fal/object.h"
#include "fal/subobject.h"

class SlaveInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList networkNames READ networkNames CONSTANT)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)
    Q_PROPERTY(QList<Object*> objectDictionary READ objectDictionary NOTIFY objectDictionaryChanged)

public:
    explicit SlaveInfo(QObject *parent = nullptr);
    ~SlaveInfo();

    Q_INVOKABLE void findAndConfigureSlaves();
    Q_INVOKABLE void recordDeviceState(const quint8 slaveId);
    Q_INVOKABLE void setDeviceState(const quint8 slaveId, quint8 state);
    Q_INVOKABLE void connect(QString networkDeviceName);
    Q_INVOKABLE void sdoRead(quint16 index, quint16 subindex);
    Q_INVOKABLE void odPrintout();

    QStringList networkNames();
    QString name();
    void setName(const QString &name);
    QString state();
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
    /* TODO: Put this somewhere else. */
    QStringList m_networkNames;
    /** All the objects in the slave */
    QList<Object *> m_objectDictionary;

    QString m_title;
    /* TODO: These need to be in their own class, so they can be listed */
    QString m_name;
    QString m_state;
};

#endif // SLAVEINFO_H
