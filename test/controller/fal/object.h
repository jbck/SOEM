#ifndef OBJECT_H
#define OBJECT_H

#include <QObject>
#include <QVariant>

class Object : public QObject
{
    Q_OBJECT
public:
    explicit Object(quint16 index, quint16 type, QObject *parent = nullptr);
    QString getString();

    QVariant getValue() const;
    void setValue(const QVariant &value);

    QString getDescription() const;
    void setDescription(const QString &description);

    quint16 getIndex() const;
    void setIndex(const quint16 &index);

signals:

public slots:

private:
    /** Object description as it appears from the slave */
    QString m_description;
    /** The index of the object */
    quint16 m_index;
    /** Contains the actual value of this object */
    QVariant m_value;
    /** Describes the type of the value */
    quint16 m_value_type;
};

#endif // OBJECT_H
