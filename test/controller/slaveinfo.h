#ifndef SLAVEINFO_H
#define SLAVEINFO_H

#include <QObject>
#include <QString>

#include "ethercat.h"

class SlaveInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList networkNames READ networkNames CONSTANT)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString state READ state NOTIFY stateChanged)

public:
    explicit SlaveInfo(QObject *parent = nullptr);

    Q_INVOKABLE void findAndConfigureSlaves();
    Q_INVOKABLE void setDeviceState(const quint8 slaveId, quint8 state);
    Q_INVOKABLE void connect(QString networkDeviceName);
    Q_INVOKABLE void sdoRead(quint16 index, quint16 subindex);

    QStringList networkNames();
    QString name();
    void setName(const QString &name);
    QString state();
    void setState(const quint8 state);
    QString title() const;
    void setTitle(const QString &value);

signals:
    void titleChanged();

    void nameChanged();
    void stateChanged();

private:
    QStringList m_networkNames;
    QString m_title;
    //char m_ethercat_IOmap[4096];

    /* TODO: These need to be in their own class, so they can be listed */
    QString m_name;
    QString m_state;
};

#endif // SLAVEINFO_H
