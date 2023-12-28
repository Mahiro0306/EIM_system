QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    four_fix.cpp \
    four_fix_new.cpp \
    four_new.cpp \
    main.cpp \
    mainwindow.cpp \
    one_find.cpp \
    one_insert.cpp \
    one_new.cpp \
    one_sort.cpp \
    password.cpp \
    selectscene.cpp \
    systemfour.cpp \
    systemone.cpp \
    systemthree.cpp \
    systemtwo.cpp \
    three_delete.cpp \
    three_fix.cpp \
    three_fix_new.cpp \
    three_new.cpp \
    two_delete.cpp \
    two_fix.cpp \
    two_fix_new.cpp \
    two_new.cpp

HEADERS += \
    four_fix.h \
    four_fix_new.h \
    four_new.h \
    mainwindow.h \
    one_find.h \
    one_insert.h \
    one_new.h \
    one_sort.h \
    password.h \
    selectscene.h \
    systemfour.h \
    systemone.h \
    systemthree.h \
    systemtwo.h \
    three_delete.h \
    three_fix.h \
    three_fix_new.h \
    three_new.h \
    two_delete.h \
    two_fix.h \
    two_fix_new.h \
    two_new.h

FORMS += \
    four_fix.ui \
    four_fix_new.ui \
    four_new.ui \
    mainwindow.ui \
    one_find.ui \
    one_insert.ui \
    one_new.ui \
    one_sort.ui \
    password.ui \
    selectscene.ui \
    systemfour.ui \
    systemone.ui \
    systemthree.ui \
    systemtwo.ui \
    three_delete.ui \
    three_fix.ui \
    three_fix_new.ui \
    three_new.ui \
    two_delete.ui \
    two_fix.ui \
    two_fix_new.ui \
    two_new.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
