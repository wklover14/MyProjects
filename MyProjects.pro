QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    color_picker.cpp \
    date_picker.cpp \
    main.cpp \
    mainwindow.cpp \
    parameters.cpp

HEADERS += \
    Colorful_circle.h \
    carrousel.h \
    color_item.h \
    color_picker.h \
    date_picker.h \
    mainwindow.h \
    milestone_widget.h \
    parameters.h

FORMS += \
    date_picker.ui \
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
    plus.svg \
    right_arrow.svg
