#include "object.h"

Object::Object(quint16 index, quint16 type, QObject *parent)
    : QObject(parent),
      m_description(""),
      m_index(index),
      m_value_type(type)
{
}

QString Object::getString()
{
    return m_value.toString();
}

QVariant Object::getValue() const
{
    return m_value;
}

void Object::setValue(const QVariant &value)
{
    m_value.setValue(value);
}

QString Object::getDescription() const
{
    return m_description;
}

void Object::setDescription(const QString &description)
{
    m_description = description;
}

quint16 Object::getIndex() const
{
    return m_index;
}

void Object::setIndex(const quint16 &index)
{
    m_index = index;
}
