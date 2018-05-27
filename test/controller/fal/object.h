#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>

#include "fal/subobject.h"

class Object : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(quint16 index READ index WRITE setIndex NOTIFY indexChanged)
    Q_PROPERTY(quint16 type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(quint8 objectCode READ objectCode WRITE setObjectCode NOTIFY objectCodeChanged)
    //Q_PROPERTY(QList<SubObject> subObjectList READ subObjectList NOTIFY subObjectListChanged)

    /** A text description */
    QString m_name;
    /** The index of the object */
    quint16 m_index;
    /** Type of object (record, etc) */
    quint16 m_type;
    /** TOOD: I have no idea what this is. */
    quint8 m_objectCode;

    /** All the sub-objects this object contains */
    QList<SubObject *> m_subObjectList;

public:
    explicit Object(QString name, quint16 index, quint16 type, quint8 objectCode, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    quint16 index() const;
    void setIndex(const quint16 &index);

    quint16 type() const;
    void setType(const quint16 &type);

    quint8 objectCode() const;
    void setObjectCode(const quint8 &objectCode);

    void addSubObject(SubObject * subObject);

    QList<SubObject *> subObjectList() const;

signals:
    void nameChanged();
    void indexChanged();
    void typeChanged();
    void objectCodeChanged();

public slots:

};

#endif // OBJECT_H
