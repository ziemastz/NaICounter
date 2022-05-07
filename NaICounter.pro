QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    naicounter.cpp

HEADERS += \
    naicounter.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../digilent.adept.sdk_v2.4.2/lib64/ -ldepp

INCLUDEPATH += $$PWD/../digilent.adept.sdk_v2.4.2/include
DEPENDPATH += $$PWD/../digilent.adept.sdk_v2.4.2/include

win32: LIBS += -L$$PWD/../digilent.adept.sdk_v2.4.2/lib64/ -ldmgr

INCLUDEPATH += $$PWD/../digilent.adept.sdk_v2.4.2/include
DEPENDPATH += $$PWD/../digilent.adept.sdk_v2.4.2/include
