#include "utils.h"

#include <QVariant>

#include "ethercat.h"

Utils::Utils()
{
}

QVariant * Utils::sdobytes2type(char * usdo, uint16 dtype)
{
    /* TODO: Get rid of these types of temp data structures */
    char hstr[1024];

    /* TODO: Probably unnecessary when using QVariant */
    uint8 *u8;
    int8 *i8;
    uint16 *u16;
    int16 *i16;
    uint32 *u32;
    int32 *i32;
    uint64 *u64;
    int64 *i64;
    float *sr;
    double *dr;
    char es[32];

    /* This stores the value in whatever format it should be */
    QVariant * value = new QVariant("Unknown type");

    //memset(&usdo, 0, 128);
    //ec_SDOread(slave, index, subidx, FALSE, &l, &usdo, EC_TIMEOUTRXM);
    switch(dtype)
    {
    case ECT_BOOLEAN:
        u8 = (uint8*) &usdo[0];
        if (*u8) value->setValue(true);
        else value->setValue(false);
        break;
    case ECT_INTEGER8:
        i8 = (int8*) &usdo[0];
        value->setValue(*i8);
        break;
    case ECT_INTEGER16:
        i16 = (int16*) &usdo[0];
        value->setValue(*i16);
        break;
    case ECT_INTEGER32:
    case ECT_INTEGER24:
        i32 = (int32*) &usdo[0];
        value->setValue(*i32);
        break;
    case ECT_INTEGER64:
        i64 = (int64*) &usdo[0];
        value->setValue(*i64);
        break;
    case ECT_UNSIGNED8:
        u8 = (uint8*) &usdo[0];
        value->setValue(*u8);
        break;
    case ECT_UNSIGNED16:
        u16 = (uint16*) &usdo[0];
        value->setValue(*u16);
        break;
    case ECT_UNSIGNED32:
    case ECT_UNSIGNED24:
        u32 = (uint32*) &usdo[0];
        value->setValue(*u32);
        break;
    case ECT_UNSIGNED64:
        u64 = (uint64*) &usdo[0];
        value->setValue(*u64);
        break;
    case ECT_REAL32:
        sr = (float*) &usdo[0];
        value->setValue(*sr);
        break;
    case ECT_REAL64:
        dr = (double*) &usdo[0];
        value->setValue(*dr);
        break;
    case ECT_BIT1:
    case ECT_BIT2:
    case ECT_BIT3:
    case ECT_BIT4:
    case ECT_BIT5:
    case ECT_BIT6:
    case ECT_BIT7:
    case ECT_BIT8:
        u8 = (uint8*) &usdo[0];
        value->setValue(*u8);
        break;
    case ECT_VISIBLE_STRING:
        value->setValue(QString(usdo));
        break;
    case ECT_OCTET_STRING:
        hstr[0] = 0x00;
        for (int i = 0 ; i < sizeof(usdo) - 1 ; i++)
        {
            sprintf(es, "0x%2.2x ", usdo[i]);
            strcat( hstr, es);
        }
        value->setValue(QString(hstr));
        break;
    default:
        /* Keep unknown value as a string. */
        break;
    }

    return value;
}
