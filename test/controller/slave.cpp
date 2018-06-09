#include <QMessageLogger>
#include <QThread>
#include <QDebug>

#include <QElapsedTimer>

#include "slave.h"
#include "ethercat.h"
#include "fal/utils.h"
#include "fal/object.h"
#include "fal/subobject.h"

Slave::Slave(QObject * parent) : BasicListItem(parent)
{
    Object * object = new Object("Name 0", 0x1000, 0, 1);
    m_objectDictionary.append(object);
    object = new Object("Name 1", 0x1001, 0, 1);
    m_objectDictionary.append(object);
    object = new Object("Name 2", 0x1002, 0, 1);
    m_objectDictionary.append(object);
}

Slave::~Slave()
{
    /* Release the socket */
    ec_close();
}

QVariant Slave::data(int role) const
{
    switch(role) {
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Slave::roleNames() const
{
    QHash<int, QByteArray> names;
    return names;
}

void Slave::sdoRead(quint16 index, quint16 subindex)
{
//    QElapsedTimer timer;
//    timer.start();
//    qDebug() << timer.elapsed();

    /* Remove all the old objects so new objects can be added */
    m_objectDictionary.clear();

    ec_ODlistt ODlist;
    ec_OElistt OElist;

    char usdo[128];

    ODlist.Entries = 0; /* TODO: Why, if the memset is right below this? */
    memset(&ODlist, 0, sizeof(ODlist));
    /* TODO: Do this for every slave instead of just the first */
    int slaveId = 1;
    if( ec_readODlist(slaveId, &ODlist))
    {
        /* The OD has been read for this slave. Time to populate the Object list. */
        qDebug() << " CoE Object Description found, " << ODlist.Entries << " entries.";
        for(quint16 i = 0 ; i < ODlist.Entries ; i++)
        {
            /*
             * Handle the Object
             */
            ec_readODdescription(i, &ODlist);
            while(EcatError) qDebug("%s", ec_elist2string());
            Object * object = new Object(QString(ODlist.Name[i]),
                                         ODlist.Index[i],
                                         ODlist.DataType[i],
                                         ODlist.ObjectCode[i], this);
            /*
             * Handle the Sub-objects
             */
            memset(&OElist, 0, sizeof(OElist));
            ec_readOE(i, &ODlist, &OElist);
            while(EcatError) printf("%s", ec_elist2string());
            for(quint16 j = 0 ; j < ODlist.MaxSub[i]+1 ; j++)
            {
                if ((OElist.DataType[j] > 0) && (OElist.BitLength[j] > 0))
                {
                    /* Grab the value of the SDO */
                    /* TODO: Get rid of all the array crap. */
                    memset(&usdo, 0, 128);
                    int l = sizeof(usdo) - 1;
                    /* TODO: Wrap this in a check for write-only objects */
                    ec_SDOread(slaveId, object->index(), j, FALSE, &l, &usdo, EC_TIMEOUTRXM);
                    QVariant * value = Utils::sdobytes2type(usdo, OElist.DataType[j]);
                    /* Populate the object with the data */
                    SubObject * subObject = new SubObject(j, /* sub-index */
                                                          QString(OElist.Name[j]),
                                                          *value,
                                                          OElist.DataType[j],
                                                          OElist.ValueInfo[j],
                                                          OElist.BitLength[j],
                                                          OElist.ObjAccess[j], object);
                    object->addSubObject(subObject);
                }
            }
            m_objectDictionary.append(object);

        }
    }
    else
    {
        while(EcatError) printf("%s", ec_elist2string());
    }

}

void Slave::odPrintout()
{
    qDebug() << "Object Dictionary";
    for (Object * object : m_objectDictionary) {
        qDebug() << QString("%1").arg(object->index() , 0, 16) << ":" << object->name();
        for (SubObject * subObject : object->subObjectList())
        {
            qDebug() << "  Sub" << subObject->subIndex() << ":" << subObject->value() << ":" << subObject->name();
        }
    }
}

QString Slave::title() const
{
    return m_title;
}

void Slave::setTitle(const QString &value)
{
    if (value == m_title) {
        return;
    }
    m_title = value;
    emit titleChanged();

}

QList<Object *> Slave::objectDictionary() const
{
    return m_objectDictionary;
}


QString Slave::name()
{
    return m_name;
}

void Slave::setName(const QString &name)
{
    if (name == m_name) {
        return;
    }
    m_name = name;
    emit nameChanged();
}

QString Slave::state()
{
    return m_state;
}

void Slave::setState(const quint8 state)
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


void Slave::recordDeviceState(const quint8 slaveId) {
    ec_readstate();
    setState(ec_slave[slaveId].state);
}

void Slave::setDeviceState(const quint8 slaveId, quint8 state)
{
    ec_FPWRw(ec_slave[slaveId].configadr, ECT_REG_ALCTL, htoes(state | EC_STATE_ACK) , EC_TIMEOUTRET3);
}
