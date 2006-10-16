/****************************************************************************
** Meta object code from reading C++ file 'TPushButtonSystem.h'
**
** Created: Mo Jul 10 20:38:55 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TPushButtonSystem.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TPushButtonSystem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TPushButtonSystem[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // signals: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x05,
      30,   18,   18,   18, 0x05,
      39,   18,   18,   18, 0x05,
      50,   18,   18,   18, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TPushButtonSystem[] = {
    "TPushButtonSystem\0\0moveDown()\0moveUp()\0moveLeft()\0moveRight()\0"
};

const QMetaObject TPushButtonSystem::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TPushButtonSystem,
      qt_meta_data_TPushButtonSystem, 0 }
};

const QMetaObject *TPushButtonSystem::metaObject() const
{
    return &staticMetaObject;
}

void *TPushButtonSystem::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TPushButtonSystem))
	return static_cast<void*>(const_cast<TPushButtonSystem*>(this));
    return QThread::qt_metacast(_clname);
}

int TPushButtonSystem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: moveDown(); break;
        case 1: moveUp(); break;
        case 2: moveLeft(); break;
        case 3: moveRight(); break;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void TPushButtonSystem::moveDown()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void TPushButtonSystem::moveUp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void TPushButtonSystem::moveLeft()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void TPushButtonSystem::moveRight()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
