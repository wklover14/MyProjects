QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components/color_picker.cpp \
    components/date_picker.cpp \
    logic/a_project.cpp \
    logic/category.cpp \
    logic/checkpoint.cpp \
    logic/quantifiable_project.cpp \
    main.cpp \
    mainwindow.cpp \
    parameters.cpp

HEADERS += \
    Colorful_circle.h \
    carrousel.h \
    color_item.h \
    color_picker.h \
    components/Colorful_circle.h \
    components/carrousel.h \
    components/color_item.h \
    components/color_picker.h \
    components/date_picker.h \
    components/milestone_widget.h \
    date_picker.h \
    logic/a_project.h \
    logic/category.h \
    logic/checkpoint.h \
    logic/quantifiable_project.h \
    mainwindow.h \
    milestone_widget.h \
    parameters.h

FORMS += \
    components/color_picker.ui \
    components/date_picker.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    calendar.svg \
    images/calendar.png \
    images/left_arrow.png \
    images/number.png \
    images/plus.png \
    images/right_arrow.png \
    left_arrow.svg \
    number.svg \
    right_arrow.svg
