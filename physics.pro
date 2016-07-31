TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
#    camera.cpp \
    vector3.cpp \
    rungekuttaintegrator.cpp \
    eulerintegrator.cpp \
    modifiedeulerintegrator.cpp \
    particlesystem.cpp \
    spring.cpp \
    attraction.cpp \
    particle.cpp

HEADERS += \
    force.h \
    spring.h \
    particle.h \
    integrator.h \
    attraction.h \
    eulerintegrator.h \
    particlesystem.h \
    modifiedeulerintegrator.h \
    rungekuttaintegrator.h \
#    camera.h \
    vector3.h

LIBS += -L /usr/lib/x86_64-linux-gnu -lglut -lGLU -lGL


#INCLUDEPATH += /usr/local/include \
#                /usr/local/include/opencv \
#                /usr/local/include/opencv2
