#include "subobject.h"

QString SubObject::name() const
{
    return m_name;
}

void SubObject::setName(const QString &name)
{
    m_name = name;
}

QVariant SubObject::value() const
{
    return m_value;
}

void SubObject::setValue(const QVariant &value)
{
    m_value = value;
}

quint16 SubObject::valueType() const
{
    return m_valueType;
}

void SubObject::setValueType(const quint16 &valueType)
{
    m_valueType = valueType;
}

quint8 SubObject::valueInfo() const
{
    return m_valueInfo;
}

void SubObject::setValueInfo(const quint8 &valueInfo)
{
    m_valueInfo = valueInfo;
}

quint16 SubObject::bitLength() const
{
    return m_bitLength;
}

void SubObject::setBitLength(const quint16 &bitLength)
{
    m_bitLength = bitLength;
}

SubObject::SubObject(QObject *parent) : QObject(parent)
{

}
