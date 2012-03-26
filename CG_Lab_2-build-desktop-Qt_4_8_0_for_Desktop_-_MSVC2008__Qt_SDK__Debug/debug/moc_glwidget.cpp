/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created: Sat 17. Mar 19:51:54 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CG_Lab_2_3/glwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GlWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      30,    9,    9,    9, 0x0a,
      58,    9,    9,    9, 0x0a,
      85,    9,    9,    9, 0x0a,
     103,    9,    9,    9, 0x0a,
     121,    9,    9,    9, 0x0a,
     139,    9,    9,    9, 0x0a,
     160,    9,    9,    9, 0x0a,
     179,    9,    9,    9, 0x0a,
     199,    9,    9,    9, 0x0a,
     216,    9,    9,    9, 0x0a,
     235,    9,    9,    9, 0x0a,
     251,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GlWidget[] = {
    "GlWidget\0\0setPoligonMode(int)\0"
    "setDrawPointsOnPoligon(int)\0"
    "setDrawLinesOnPoligon(int)\0setColourR(float)\0"
    "setColourB(float)\0setColourG(float)\0"
    "setColourAlfa(float)\0setLineSize(float)\0"
    "setPointSize(float)\0setAlfaFunc(int)\0"
    "setAlfaRef(double)\0setSFactor(int)\0"
    "setDFactor(int)\0"
};

void GlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GlWidget *_t = static_cast<GlWidget *>(_o);
        switch (_id) {
        case 0: _t->setPoligonMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setDrawPointsOnPoligon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setDrawLinesOnPoligon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setColourR((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->setColourB((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->setColourG((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 6: _t->setColourAlfa((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->setLineSize((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->setPointSize((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 9: _t->setAlfaFunc((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->setAlfaRef((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->setSFactor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setDFactor((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GlWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GlWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_GlWidget,
      qt_meta_data_GlWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GlWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GlWidget))
        return static_cast<void*>(const_cast< GlWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int GlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
