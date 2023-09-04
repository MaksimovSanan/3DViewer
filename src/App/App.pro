QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets opengl
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11 c


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    giflib/dgif_lib.c \
    giflib/egif_lib.c \
    giflib/gif_err.c \
    giflib/gif_font.c \
    giflib/gif_hash.c \
    giflib/gifalloc.c \
    giflib/quantize.c \
    ../parser.c \
    ../afine.c \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    qgifimage.cpp

HEADERS += \
    giflib/gif_hash.h \
    giflib/gif_lib.h \
    giflib/gif_lib_private.h \
    ../parser.h \
    ../afine.h \
    glwidget.h \
    mainwindow.h \
    qgifglobal.h \
    qgifimage.h \
    qgifimage_p.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

