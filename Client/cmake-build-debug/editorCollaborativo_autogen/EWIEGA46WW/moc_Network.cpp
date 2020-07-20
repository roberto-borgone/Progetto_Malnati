/****************************************************************************
** Meta object code from reading C++ file 'Network.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Network.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Network.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Network_t {
    QByteArrayData data[19];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Network_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Network_t qt_meta_stringdata_Network = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Network"
QT_MOC_LITERAL(1, 8, 6), // "insert"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 6), // "Symbol"
QT_MOC_LITERAL(4, 23, 1), // "s"
QT_MOC_LITERAL(5, 25, 5), // "erase"
QT_MOC_LITERAL(6, 31, 6), // "string"
QT_MOC_LITERAL(7, 38, 9), // "logged_in"
QT_MOC_LITERAL(8, 48, 11), // "std::string"
QT_MOC_LITERAL(9, 60, 4), // "user"
QT_MOC_LITERAL(10, 65, 12), // "wrong_log_in"
QT_MOC_LITERAL(11, 78, 9), // "wrong_sub"
QT_MOC_LITERAL(12, 88, 9), // "getSocket"
QT_MOC_LITERAL(13, 98, 11), // "QSslSocket&"
QT_MOC_LITERAL(14, 110, 11), // "send_symbol"
QT_MOC_LITERAL(15, 122, 3), // "pos"
QT_MOC_LITERAL(16, 126, 3), // "prj"
QT_MOC_LITERAL(17, 130, 3), // "usr"
QT_MOC_LITERAL(18, 134, 16) // "message_received"

    },
    "Network\0insert\0\0Symbol\0s\0erase\0string\0"
    "logged_in\0std::string\0user\0wrong_log_in\0"
    "wrong_sub\0getSocket\0QSslSocket&\0"
    "send_symbol\0pos\0prj\0usr\0message_received"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Network[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
      10,    0,   63,    2, 0x06 /* Public */,
      11,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   65,    2, 0x0a /* Public */,
      14,    4,   68,    2, 0x0a /* Public */,
      18,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    4,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 8, 0x80000000 | 8,    4,   15,   16,   17,
    QMetaType::Void,

       0        // eod
};

void Network::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Network *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->insert((*reinterpret_cast< Symbol(*)>(_a[1]))); break;
        case 1: _t->erase((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 2: _t->logged_in((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->wrong_log_in(); break;
        case 4: _t->wrong_sub(); break;
        case 5: _t->getSocket((*reinterpret_cast< QSslSocket(*)>(_a[1]))); break;
        case 6: _t->send_symbol((*reinterpret_cast< Symbol(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4]))); break;
        case 7: _t->message_received(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Network::*)(Symbol );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::insert)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Network::*)(string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::erase)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Network::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::logged_in)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::wrong_log_in)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Network::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Network::wrong_sub)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Network::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_Network.data,
    qt_meta_data_Network,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Network::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Network::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Network.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Network::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void Network::insert(Symbol _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Network::erase(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Network::logged_in(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Network::wrong_log_in()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Network::wrong_sub()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
