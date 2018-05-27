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

quint16 SubObject::objectAccess() const
{
    return m_objectAccess;
}

void SubObject::setObjectAccess(const quint16 &objectAccess)
{
    m_objectAccess = objectAccess;
}

quint16 SubObject::subIndex() const
{
    return m_subIndex;
}

void SubObject::setSubIndex(const quint16 &subIndex)
{
    m_subIndex = subIndex;
}

SubObject::SubObject(quint16 subIndex,
                     QString name,
                     QVariant value,
                     quint16 valueType,
                     quint8 valueInfo,
                     quint16 bitLength,
                     quint16 objectAccess,
                     QObject *parent)
    : QObject(parent),
      m_subIndex(subIndex),
      m_name(name),
      m_value(value),
      m_valueType(valueType),
      m_valueInfo(valueInfo),
      m_bitLength(bitLength),
      m_objectAccess(objectAccess)
{
}
