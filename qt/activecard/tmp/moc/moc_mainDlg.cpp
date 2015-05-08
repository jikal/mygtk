/****************************************************************************
** Meta object code from reading C++ file 'mainDlg.h'
**
** Created: Wed May 6 13:15:10 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/mainDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_mainDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      42,    8,    8,    8, 0x0a,
      51,   49,    8,    8, 0x0a,
      67,    8,    8,    8, 0x0a,
      85,    8,    8,    8, 0x0a,
      99,    8,    8,    8, 0x0a,
     110,  107,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_mainDlg[] = {
    "mainDlg\0\0populateJavaScriptWindowObject()\0"
    "onOk()\0f\0onFinised(bool)\0onVideoFinished()\0"
    "onSBClicked()\0onKey()\0nr\0"
    "replyFinished(QNetworkReply*)\0"
};

void mainDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        mainDlg *_t = static_cast<mainDlg *>(_o);
        switch (_id) {
        case 0: _t->populateJavaScriptWindowObject(); break;
        case 1: _t->onOk(); break;
        case 2: _t->onFinised((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onVideoFinished(); break;
        case 4: _t->onSBClicked(); break;
        case 5: _t->onKey(); break;
        case 6: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData mainDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject mainDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_mainDlg,
      qt_meta_data_mainDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &mainDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *mainDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *mainDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_mainDlg))
        return static_cast<void*>(const_cast< mainDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int mainDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
