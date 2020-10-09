/****************************************************************************
** Meta object code from reading C++ file 'TaskGeneric.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../TaskGeneric.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TaskGeneric.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TaskGeneric_t {
    QByteArrayData data[9];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TaskGeneric_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TaskGeneric_t qt_meta_stringdata_TaskGeneric = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TaskGeneric"
QT_MOC_LITERAL(1, 12, 12), // "returnResult"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "result"
QT_MOC_LITERAL(4, 33, 14), // "forwardMessage"
QT_MOC_LITERAL(5, 48, 5), // "login"
QT_MOC_LITERAL(6, 54, 4), // "user"
QT_MOC_LITERAL(7, 59, 10), // "killClient"
QT_MOC_LITERAL(8, 70, 8) // "finished"

    },
    "TaskGeneric\0returnResult\0\0result\0"
    "forwardMessage\0login\0user\0killClient\0"
    "finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TaskGeneric[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    2,   42,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       7,    0,   50,    2, 0x06 /* Public */,
       8,    0,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TaskGeneric::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TaskGeneric *_t = static_cast<TaskGeneric *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnResult((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->forwardMessage((*reinterpret_cast< QByteArray(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->login((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->killClient(); break;
        case 4: _t->finished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (TaskGeneric::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaskGeneric::returnResult)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TaskGeneric::*_t)(QByteArray , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaskGeneric::forwardMessage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TaskGeneric::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaskGeneric::login)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TaskGeneric::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaskGeneric::killClient)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TaskGeneric::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TaskGeneric::finished)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject TaskGeneric::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_TaskGeneric.data,
      qt_meta_data_TaskGeneric,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TaskGeneric::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TaskGeneric::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TaskGeneric.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int TaskGeneric::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void TaskGeneric::returnResult(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TaskGeneric::forwardMessage(QByteArray _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TaskGeneric::login(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TaskGeneric::killClient()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void TaskGeneric::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
