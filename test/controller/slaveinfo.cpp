#include <QMessageLogger>
#include <QThread>
#include <QNetworkInterface>
#include <QRegularExpression>
#include <QElapsedTimer>

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

void SlaveInfo::sdoRead(quint16 index, quint16 subindex)
{
//    QElapsedTimer timer;
//    int bytes_read = 2;
//    qint8 data[2];
//    data[0]=1;
//    data[1]=1;
//    timer.start();
//    ec_SDOwrite(1, 0x6072, 0, false, bytes_read, data, EC_TIMEOUTRXM);
//    int workcounter = ec_SDOread(1, 0x6072, 0, false, &bytes_read, data, EC_TIMEOUTRXM);
//    qDebug() << timer.elapsed();
//    qDebug() << "Workcounter: " << workcounter;
//    qDebug() << "Bytes read: " << bytes_read;
//    qDebug() << "Value: " << *(qint16*)data;

    int i, j;

    ec_ODlistt ODlist;
    ec_OElistt OElist;

    ODlist.Entries = 0; /* WHY? */
    memset(&ODlist, 0, sizeof(ODlist));
    for (quint8 slaveId = 1; slaveId <= ec_slavecount; slaveId++) {
        if( ec_readODlist(slaveId, &ODlist))
        {
            qDebug() << " CoE Object Description found, " << ODlist.Entries << " entries.";
            for( i = 0 ; i < ODlist.Entries ; i++)
            {
                ec_readODdescription(i, &ODlist);
                while(EcatError) printf("%s", ec_elist2string());
                qDebug(" Index: %4.4x Datatype: %4.4x Objectcode: %2.2x Name: %s",
                    ODlist.Index[i], ODlist.DataType[i], ODlist.ObjectCode[i], ODlist.Name[i]);
                memset(&OElist, 0, sizeof(OElist));
                ec_readOE(i, &ODlist, &OElist);
                while(EcatError) printf("%s", ec_elist2string());
                for( j = 0 ; j < ODlist.MaxSub[i]+1 ; j++)
                {
                    if ((OElist.DataType[j] > 0) && (OElist.BitLength[j] > 0))
                    {
                        qDebug("  Sub: %2.2x Datatype: %4.4x Bitlength: %4.4x Obj.access: %4.4x Name: %s",
                            j, OElist.DataType[j], OElist.BitLength[j], OElist.ObjAccess[j], OElist.Name[j]);
                        if ((OElist.ObjAccess[j] & 0x0007))
                        {
                            qDebug() << "Datatype:" << OElist.DataType[j];
                            //printf("          Value :%s\n", SDO2string(slaveId, ODlist.Index[i], j, OElist.DataType[j]));
                        }
                    }
                }
            }
        }
        else
        {
            while(EcatError) printf("%s", ec_elist2string());
        }

    }
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

void SlaveInfo::recordDeviceState(const quint8 slaveId) {
    ec_readstate();
    setState(ec_slave[slaveId].state);
}

void SlaveInfo::setDeviceState(const quint8 slaveId, quint8 state)
{
    ec_FPWRw(ec_slave[slaveId].configadr, ECT_REG_ALCTL, htoes(state | EC_STATE_ACK) , EC_TIMEOUTRET3);
}
