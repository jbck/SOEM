#include <QMessageLogger>
#include <QThread>
#include <QNetworkInterface>
#include <QRegularExpression>

#include "slaveinfo.h"
#include "ethercat.h"

SlaveInfo::SlaveInfo(QObject *parent) : QObject(parent)
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    /* Describe interfaces named 'lo' or start with a w (wireless?) */
    QRegularExpression re = QRegularExpression("(lo|w.*)");
    /* Filter out the interfaces described above */
    for (QNetworkInterface i : interfaces) {
        if (!i.name().contains(re)) {
            m_networkNames.append(i.name());
        }
    }
}

void SlaveInfo::connect(QString networkDeviceName)
{
    /* Initialize SOEM, bind socket to ifname */
    if(!ec_init(networkDeviceName.toStdString().c_str())) {
        QMessageLogger().fatal("Cannot open socket. Run as root.");
    }
    /* Now search for EtherCAT slaves */
    findAndConfigureSlaves();
}

QString SlaveInfo::title() const
{
    return m_title;
}

void SlaveInfo::setTitle(const QString &value)
{
    if (value == m_title) {
        return;
    }
    m_title = value;
    emit titleChanged();

}

QStringList SlaveInfo::networkNames()
{
    return m_networkNames;
}

QString SlaveInfo::name()
{
    return m_name;
}

void SlaveInfo::setName(const QString &name)
{
    if (name == m_name) {
        return;
    }
    m_name = name;
    emit nameChanged();
}

QString SlaveInfo::state()
{
    return m_state;
}

void SlaveInfo::setState(const quint8 state)
{
    QString newState;
    /* These cases test for the EtherCAT state enumeration */
    switch (state) {
    case 0x00:
        newState = "NONE";
        break;
    case 0x01:
        newState = "INIT";
        break;
    case 0x02:
        newState = "PREOP";
        break;
    case 0x03:
        newState = "BOOT";
        break;
    case 0x04:
        newState = "SAFEOP";
        break;
    case 0x08:
        newState = "OP";
        break;
    case 0x10:
        newState = "ERROR/ACK";
        break;
    }

    if (newState == m_state)
        return;

    m_state = newState;
    emit stateChanged();
}

void SlaveInfo::findAndConfigureSlaves()
{
    /* find and auto-config slaves */
    if (ec_config_init(FALSE) <= 0) {
         QMessageLogger().warning("No slaves were found.");
    }
    /* Measure propagation delays and such? */
    ec_configdc();

    for (quint8 slaveId = 1; slaveId <= ec_slavecount; slaveId++) {
        setState(ec_slave[slaveId].state);
        setName(QString(ec_slave[slaveId].name));
        setTitle("Slaves: " + QString::number(ec_slavecount));
    }

}

void SlaveInfo::setDeviceState(const quint8 slaveId, quint8 state)
{
    ec_FPWRw(ec_slave[slaveId].configadr, ECT_REG_ALCTL, htoes(state | EC_STATE_ACK) , EC_TIMEOUTRET3);
    QThread::msleep(200);
    ecx_readstate(&ecx_context);
    setState(ec_slave[slaveId].state);
}
