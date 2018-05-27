#ifndef SUBOBJECT_H
#define SUBOBJECT_H

#include <QObject>

class SubObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(quint16 valueType READ valueType WRITE setValueType NOTIFY valueTypeChanged)
    Q_PROPERTY(quint8 valueInfo READ valueInfo WRITE setValueInfo NOTIFY valueInfoChanged)
    Q_PROPERTY(quint16 bitLength READ bitLength WRITE setBitLengthInfo NOTIFY bitLengthChanged)

    /** A text description */
    QString m_name;
    /** Contains the actual value of this object */
    QVariant m_value;
    /** Describes the type of the value */
    quint16 m_valueType;
    /** Info about this object */
    quint8 m_valueInfo;
    /** Number of bits */
    quint16 m_bitLength;
    /** Access permissions */
    quint16 m_objectAccess;

public:
    explicit SubObject(QString name,
                       QVariant value,
                       quint16 valueType,
                       quint8 valueInfo,
                       quint16 bitLength,
                       quint16 objectAccess,
                       QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QVariant value() const;
    void setValue(const QVariant &value);

    quint16 valueType() const;
    void setValueType(const quint16 &valueType);

    quint8 valueInfo() const;
    void setValueInfo(const quint8 &valueInfo);

    quint16 bitLength() const;
    void setBitLength(const quint16 &bitLength);

    quint16 objectAccess() const;
    void setObjectAccess(const quint16 &objectAccess);

signals:
    void nameChanged();
    void valueChanged();
    void valueTypeChanged();
    void valueInfoChanged();
    void bitLengthChanged();

public slots:
    /* No slots. */

};

#endif // SUBOBJECT_H
