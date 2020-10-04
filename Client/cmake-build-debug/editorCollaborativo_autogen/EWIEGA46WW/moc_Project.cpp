/****************************************************************************
** Meta object code from reading C++ file 'Project.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Project.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Project.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Project_t {
    QByteArrayData data[11];
    char stringdata0[102];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Project_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Project_t qt_meta_stringdata_Project = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Project"
QT_MOC_LITERAL(1, 8, 14), // "internalInsert"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "Symbol"
QT_MOC_LITERAL(4, 31, 1), // "s"
QT_MOC_LITERAL(5, 33, 14), // "internalDelete"
QT_MOC_LITERAL(6, 48, 6), // "string"
QT_MOC_LITERAL(7, 55, 2), // "id"
QT_MOC_LITERAL(8, 58, 13), // "remove_symbol"
QT_MOC_LITERAL(9, 72, 14), // "externalInsert"
QT_MOC_LITERAL(10, 87, 14) // "externalDelete"

    },
    "Project\0internalInsert\0\0Symbol\0s\0"
    "internalDelete\0string\0id\0remove_symbol\0"
    "externalInsert\0externalDelete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Project[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       8,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   48,    2, 0x0a /* Public */,
      10,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Project::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Project *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->internalInsert((*reinterpret_cast< Symbol(*)>(_a[1]))); break;
        case 1: _t->internalDelete((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 2: _t->remove_symbol((*reinterpret_cast< Symbol(*)>(_a[1]))); break;
        case 3: _t->externalInsert((*reinterpret_cast< Symbol(*)>(_a[1]))); break;
        case 4: _t->externalDelete((*reinterpret_cast< string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Project::*)(Symbol );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Project::internalInsert)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Project::*)(string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Project::internalDelete)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Project::*)(Symbol );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Project::remove_symbol)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Project::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Project.data,
    qt_meta_data_Project,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Project::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Project::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Project.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Project::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Project::internalInsert(Symbol _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Project::internalDelete(string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Project::remove_symbol(Symbol _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
