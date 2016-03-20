TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    oglitem.cpp \
    slidingpuzzle2drenderer.cpp \
    slidingpuzzleutility.cpp \
    vertex.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
# include(deployment.pri)

HEADERS += \
    oglitem.h \
    slidingpuzzle2drenderer.h \
    slidingpuzzleutility.h \
    vertex.h
