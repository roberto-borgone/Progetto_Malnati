/****************************************************************************
** Meta object code from reading C++ file 'DB_Client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../DB_Client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DB_Client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DB_Client_t {
    QByteArrayData data[12];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DB_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DB_Client_t qt_meta_stringdata_DB_Client = {
    {
QT_MOC_LITERAL(0, 0, 9), // "DB_Client"
QT_MOC_LITERAL(1, 10, 6), // "log_in"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 9), // "logged_in"
QT_MOC_LITERAL(4, 28, 11), // "std::string"
QT_MOC_LITERAL(5, 40, 4), // "user"
QT_MOC_LITERAL(6, 45, 9), // "main_menu"
QT_MOC_LITERAL(7, 55, 13), // "log_in_Window"
QT_MOC_LITERAL(8, 69, 16), // "subscribe_Window"
QT_MOC_LITERAL(9, 86, 11), // "send_log_in"
QT_MOC_LITERAL(10, 98, 14), // "send_subscribe"
QT_MOC_LITERAL(11, 113, 14) // "log_in_success"

    },
    "DB_Client\0log_in\0\0logged_in\0std::string\0"
    "user\0main_menu\0log_in_Window\0"
    "subscribe_Window\0send_log_in\0"
    "send_subscribe\0log_in_success"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DB_Client[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,
      10,    0,   62,    2, 0x0a /* Public */,
      11,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

       0        // eod
};

void DB_Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DB_Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->log_in(); break;
        case 1: _t->logged_in((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->main_menu(); break;
        case 3: _t->log_in_Window(); break;
        case 4: _t->subscribe_Window(); break;
        case 5: _t->send_log_in(); break;
        case 6: _t->send_subscribe(); break;
        case 7: _t->log_in_success((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DB_Client::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DB_Client::log_in)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DB_Client::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DB_Client::logged_in)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DB_Client::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_DB_Client.data,
    qt_meta_data_DB_Client,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DB_Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DB_Client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DB_Client.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int DB_Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
void DB_Client::log_in()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DB_Client::logged_in(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
