/****************************************************************************
** Meta object code from reading C++ file 'Gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Gui_t {
    QByteArrayData data[17];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Gui_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Gui_t qt_meta_stringdata_Gui = {
    {
QT_MOC_LITERAL(0, 0, 3), // "Gui"
QT_MOC_LITERAL(1, 4, 11), // "send_symbol"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 6), // "Symbol"
QT_MOC_LITERAL(4, 24, 1), // "s"
QT_MOC_LITERAL(5, 26, 3), // "pos"
QT_MOC_LITERAL(6, 30, 11), // "std::string"
QT_MOC_LITERAL(7, 42, 3), // "prj"
QT_MOC_LITERAL(8, 46, 3), // "usr"
QT_MOC_LITERAL(9, 50, 10), // "no_project"
QT_MOC_LITERAL(10, 61, 20), // "request_for_projects"
QT_MOC_LITERAL(11, 82, 13), // "close_project"
QT_MOC_LITERAL(12, 96, 11), // "new_project"
QT_MOC_LITERAL(13, 108, 8), // "time_out"
QT_MOC_LITERAL(14, 117, 8), // "position"
QT_MOC_LITERAL(15, 126, 9), // "logged_in"
QT_MOC_LITERAL(16, 136, 4) // "user"

    },
    "Gui\0send_symbol\0\0Symbol\0s\0pos\0std::string\0"
    "prj\0usr\0no_project\0request_for_projects\0"
    "close_project\0new_project\0time_out\0"
    "position\0logged_in\0user"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gui[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   49,    2, 0x06 /* Public */,
       9,    0,   58,    2, 0x06 /* Public */,
      10,    1,   59,    2, 0x06 /* Public */,
      11,    1,   62,    2, 0x06 /* Public */,
      12,    0,   65,    2, 0x06 /* Public */,
      13,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 6, 0x80000000 | 6,    4,    5,    7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    8,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,   16,

       0        // eod
};

void Gui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Gui *_t = static_cast<Gui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_symbol((*reinterpret_cast< Symbol(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4]))); break;
        case 1: _t->no_project(); break;
        case 2: _t->request_for_projects((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->close_project((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 4: _t->new_project(); break;
        case 5: _t->time_out((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->logged_in((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (Gui::*_t)(Symbol , int , std::string , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::send_symbol)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Gui::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::no_project)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Gui::*_t)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::request_for_projects)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Gui::*_t)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::close_project)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Gui::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::new_project)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Gui::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::time_out)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject Gui::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Gui.data,
      qt_meta_data_Gui,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Gui::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Gui::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Gui.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Gui::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Gui::send_symbol(Symbol _t1, int _t2, std::string _t3, std::string _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Gui::no_project()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Gui::request_for_projects(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Gui::close_project(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Gui::new_project()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void Gui::time_out(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
