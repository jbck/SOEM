#pragma once

#include "basiclistmodel.h"

class Network : public BasicListModel
{
    Q_OBJECT

    /* BasicListModel: Id of the item in the list */
    long m_id;

    /* List of all the network names on the system. */
    Q_PROPERTY(QStringList networkNames READ networkNames CONSTANT)
    QStringList m_networkNames;

public:
    Network(QObject * parent = 0);

    Q_INVOKABLE void setData(const long id, const QVariant &value, int role);
    Q_INVOKABLE void findAndConfigureSlaves();
    Q_INVOKABLE void connect(QString networkDeviceName);

    QStringList networkNames();
};
