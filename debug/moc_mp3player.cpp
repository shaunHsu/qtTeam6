/****************************************************************************
** Meta object code from reading C++ file 'mp3player.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mp3player.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mp3player.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSmp3PlayerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSmp3PlayerENDCLASS = QtMocHelpers::stringData(
    "mp3Player",
    "on_btnScanDir_clicked",
    "",
    "getMetaData",
    "on_btnPlayTrack_clicked",
    "on_horizontalSlider_valueChanged",
    "value",
    "on_btnStop_clicked",
    "on_btnNext_clicked",
    "updateTrackPos",
    "position",
    "updateTrackTime",
    "updateTrackDur",
    "on_trackPosSlider_valueChanged",
    "on_btnPrev_clicked",
    "autoplayNext",
    "loadLyrics",
    "trackPath",
    "updateLyricsDisplay",
    "currentTime",
    "findMp3Files",
    "QDir",
    "dir",
    "QStringList&",
    "fileList"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSmp3PlayerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  104,    2, 0x08,    1 /* Private */,
       3,    0,  105,    2, 0x08,    2 /* Private */,
       4,    0,  106,    2, 0x08,    3 /* Private */,
       5,    1,  107,    2, 0x08,    4 /* Private */,
       7,    0,  110,    2, 0x08,    6 /* Private */,
       8,    0,  111,    2, 0x08,    7 /* Private */,
       9,    1,  112,    2, 0x08,    8 /* Private */,
      11,    0,  115,    2, 0x08,   10 /* Private */,
      12,    0,  116,    2, 0x08,   11 /* Private */,
      13,    1,  117,    2, 0x08,   12 /* Private */,
      14,    0,  120,    2, 0x08,   14 /* Private */,
      15,    0,  121,    2, 0x08,   15 /* Private */,
      16,    1,  122,    2, 0x08,   16 /* Private */,
      18,    1,  125,    2, 0x08,   18 /* Private */,
      20,    2,  128,    2, 0x08,   20 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   17,
    QMetaType::Void, QMetaType::LongLong,   19,
    QMetaType::Void, 0x80000000 | 21, 0x80000000 | 23,   22,   24,

       0        // eod
};

Q_CONSTINIT const QMetaObject mp3Player::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSmp3PlayerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSmp3PlayerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSmp3PlayerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<mp3Player, std::true_type>,
        // method 'on_btnScanDir_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getMetaData'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnPlayTrack_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_horizontalSlider_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_btnStop_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnNext_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTrackPos'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'updateTrackTime'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTrackDur'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_trackPosSlider_valueChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_btnPrev_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'autoplayNext'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadLyrics'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'updateLyricsDisplay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'findMp3Files'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDir &, std::false_type>,
        QtPrivate::TypeAndForceComplete<QStringList &, std::false_type>
    >,
    nullptr
} };

void mp3Player::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mp3Player *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btnScanDir_clicked(); break;
        case 1: _t->getMetaData(); break;
        case 2: _t->on_btnPlayTrack_clicked(); break;
        case 3: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->on_btnStop_clicked(); break;
        case 5: _t->on_btnNext_clicked(); break;
        case 6: _t->updateTrackPos((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 7: _t->updateTrackTime(); break;
        case 8: _t->updateTrackDur(); break;
        case 9: _t->on_trackPosSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_btnPrev_clicked(); break;
        case 11: _t->autoplayNext(); break;
        case 12: _t->loadLyrics((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->updateLyricsDisplay((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *mp3Player::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mp3Player::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSmp3PlayerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int mp3Player::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
