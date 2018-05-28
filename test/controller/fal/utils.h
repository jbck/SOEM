#ifndef UTILS_H
#define UTILS_H

#include <QVariant>

class Utils
{
public:
    Utils();
    static QVariant * sdobytes2type(char * usdo, quint16 dtype);
};

#endif // UTILS_H
