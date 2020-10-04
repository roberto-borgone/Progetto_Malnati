/****************************************************************************
** Meta object code from reading C++ file 'Gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Gui_t {
    QByteArrayData data[24];
    char stringdata0[229];
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
QT_MOC_LITERAL(15, 126, 11), // "add_my_user"
QT_MOC_LITERAL(16, 138, 4), // "user"
QT_MOC_LITERAL(17, 143, 17), // "disconnect_socket"
QT_MOC_LITERAL(18, 161, 12), // "disconnected"
QT_MOC_LITERAL(19, 174, 11), // "clear_users"
QT_MOC_LITERAL(20, 186, 9), // "also_user"
QT_MOC_LITERAL(21, 196, 9), // "logged_in"
QT_MOC_LITERAL(22, 206, 8), // "add_user"
QT_MOC_LITERAL(23, 215, 13) // "change_cursor"

    },
    "Gui\0send_symbol\0\0Symbol\0s\0pos\0std::string\0"
    "prj\0usr\0no_project\0request_for_projects\0"
    "close_project\0new_project\0time_out\0"
    "position\0add_my_user\0user\0disconnect_socket\0"
    "disconnected\0clear_users\0also_user\0"
    "logged_in\0add_user\0change_cursor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Gui[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   79,    2, 0x06 /* Public */,
       9,    0,   88,    2, 0x06 /* Public */,
      10,    1,   89,    2, 0x06 /* Public */,
      11,    1,   92,    2, 0x06 /* Public */,
      12,    0,   95,    2, 0x06 /* Public */,
      13,    1,   96,    2, 0x06 /* Public */,
      15,    1,   99,    2, 0x06 /* Public */,
      17,    0,  102,    2, 0x06 /* Public */,
      18,    0,  103,    2, 0x06 /* Public */,
      19,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    1,  107,    2, 0x0a /* Public */,
      22,    1,  110,    2, 0x0a /* Public */,
      23,    2,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, 0x80000000 | 6, 0x80000000 | 6,    4,    5,    7,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    8,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, 0x80000000 | 6,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,   16,
    QMetaType::Void, 0x80000000 | 6,   16,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,   16,    5,

       0        // eod
};

void Gui::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Gui *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_symbol((*reinterpret_cast< Symbol(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4]))); break;
        case 1: _t->no_project(); break;
        case 2: _t->request_for_projects((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->close_project((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 4: _t->new_project(); break;
        case 5: _t->time_out((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->add_my_user((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 7: _t->disconnect_socket(); break;
        case 8: _t->disconnected(); break;
        case 9: _t->clear_users((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->logged_in((*reinterpret_cast< const std::string(*)>(_a[1]))); break;
        case 11: _t->add_user((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 12: _t->change_cursor((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Gui::*)(Symbol , int , std::string , std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::send_symbol)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::no_project)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Gui::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::request_for_projects)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (Gui::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::close_project)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (Gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::new_project)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (Gui::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::time_out)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (Gui::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::add_my_user)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (Gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::disconnect_socket)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (Gui::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::disconnected)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (Gui::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Gui::clear_users)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Gui::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Gui.data,
    qt_meta_data_Gui,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
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

// SIGNAL 6
void Gui::add_my_user(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Gui::disconnect_socket()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Gui::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void Gui::clear_users(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
