#include "network.h"
#include "ethercat.h"
#include "slave.h"

#include <QNetworkInterface>
#include <QRegularExpression>

Network::Network(QObject * parent)
    : BasicListModel(new Slave(), parent)
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

    Slave * slave = new Slave(this);
    appendRow(slave);
    slave = new Slave(this);
    appendRow(slave);
    slave = new Slave(this);
    appendRow(slave);
}

void Network::setData(const long id, const QVariant &value, int role)
{
    /* Get the item with the given ID */
    Slave * slave = ((Slave *)find(id));
    if (slave == NULL) {
        return;
    }

    switch (role) {
    default:
        qWarning() << "ERROR: Log: This role is unknown:" << role;
        break;
    }
}

void Network::findAndConfigureSlaves()
{
    /* find and auto-config slaves */
    if (ec_config_init(FALSE) <= 0) {
         QMessageLogger().warning("No slaves were found.");
    }
    /* Measure propagation delays and such? */
    ec_configdc();

    for (quint8 slaveId = 1; slaveId <= ec_slavecount; slaveId++) {
        //setState(ec_slave[slaveId].state);
        //setName(QString(ec_slave[slaveId].name));
        //setTitle("Slaves: " + QString::number(ec_slavecount));
    }
}

QStringList Network::networkNames()
{
    return m_networkNames;
}


void Network::connect(QString networkDeviceName)
{
    /* Initialize SOEM, bind socket to ifname */
    if(!ec_init(networkDeviceName.toStdString().c_str())) {
        QMessageLogger().warning("Cannot open socket. Run as root.");
    }
    /* Now search for EtherCAT slaves */
    findAndConfigureSlaves();
}
