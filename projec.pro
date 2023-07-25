QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ChessScore.cpp \
    InitChess.cpp \
    Op1.cpp \
    Op2.cpp \
    Win.cpp \
    eight_direction.cpp \
    form.cpp \
    item.cpp \
    jinshou.cpp \
    main.cpp \
    mainwindow.cpp \
    three_five.cpp

HEADERS += \
    Headers/form.h \
    Headers/item.h \
    Headers/mainwindow.h \
    Headers/quanju.h \
    Headers/touh.h

FORMS += \
    form.ui \
    mainwindow.ui

TRANSLATIONS += \
    projec_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \ \
    C:/Users/dell/Desktop/bai.png \
    C:/Users/dell/Desktop/beijing.jpg \
    C:/Users/dell/Desktop/beijing.png \
    F:/背景.mp3 \
    chess.ico

RC_ICONS = chess.ico
QT += multimedia

RESOURCES += \
    image.qrc
