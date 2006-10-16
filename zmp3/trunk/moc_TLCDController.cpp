/****************************************************************************
** Meta object code from reading C++ file 'TLCDController.h'
**
** Created: Mo Jul 10 20:38:52 2006
**      by: The Qt Meta Object Compiler version 59 (Qt 4.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "TLCDController.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TLCDController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_TLCDController[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TLCDController[] = {
    "TLCDController\0\0connectedToLCDServer()\0"
};

const QMetaObject TLCDController::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TLCDController,
      qt_meta_data_TLCDController, 0 }
};

const QMetaObject *TLCDController::metaObject() const
{
    return &staticMetaObject;
}

void *TLCDController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TLCDController))
	return static_cast<void*>(const_cast<TLCDController*>(this));
    return QThread::qt_metacast(_clname);
}

int TLCDController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: connectedToLCDServer(); break;
        }
        _id -= 1;
    }
    return _id;
}
