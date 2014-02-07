TEMPLATE = app
TARGET = qubuntuone-accountexample
INSTALLS += target

INCLUDEPATH += ../../src
LIBS += -L../../lib -lqubuntuone

QT += network

HEADERS += \
    $$files(src/*.h)

SOURCES += \
    $$files(src/*.cpp)

unix {
    target.path = /opt/qubuntuone/bin
}
