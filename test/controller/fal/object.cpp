#include "object.h"

QString Object::name() const
{
    return m_name;
}

void Object::setName(const QString &name)
{
    m_name = name;
}

quint16 Object::index() const
{
    return m_index;
}

void Object::setIndex(const quint16 &index)
{
    m_index = index;
}

quint16 Object::type() const
{
    return m_type;
}

void Object::setType(const quint16 &type)
{
    m_type = type;
}

quint8 Object::objectCode() const
{
    return m_objectCode;
}

void Object::setObjectCode(const quint8 &objectCode)
{
    m_objectCode = objectCode;
}

void Object::addSubObject(SubObject *subObject)
{
    m_subObjectList.append(subObject);
}

QList<SubObject *> Object::subObjectList() const
{
    return m_subObjectList;
}

Object::Object(QString name, quint16 index, quint16 type, quint8 objectCode, QObject *parent)
    : QObject(parent),
      m_name(name),
      m_index(index),
      m_type(type),
      m_objectCode(objectCode)
{
}
