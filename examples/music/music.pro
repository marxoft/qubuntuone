TEMPLATE = app
TARGET = qubuntuone-musicexample
INSTALLS += target

INCLUDEPATH += ../../src
LIBS += -L../../lib -lqubuntuone

QT += network
CONFIG += mobility
MOBILITY += multimedia

HEADERS += \
    $$files(src/*.h)

SOURCES += \
    $$files(src/*.cpp)

unix {
    target.path = /opt/qubuntuone/bin
}
