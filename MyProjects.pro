QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    components/color_picker.cpp \
    components/date_picker.cpp \
    database/a_project_db.cpp \
    database/category_db.cpp \
    database/connexion_db.cpp \
    database/project_step_db.cpp \
    database/step_db.cpp \
    logic/a_project.cpp \
    logic/category.cpp \
    logic/checkpoint.cpp \
    logic/project_step.cpp \
    logic/project_step_value.cpp \
    logic/project_value.cpp \
    logic/step.cpp \
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
    components/category_view.h \
    components/color_item.h \
    components/color_picker.h \
    components/date_picker.h \
    components/icon_button.h \
    components/menu.h \
    components/menu_item.h \
    components/text_picker.h \
    database/a_project_db.h \
    database/category_db.h \
    database/connexion_db.h \
    database/project_step_db.h \
    database/step_db.h \
    date_picker.h \
    logic/a_project.h \
    logic/category.h \
    logic/checkpoint.h \
    logic/projectException.h \
    logic/project_step.h \
    logic/project_step_value.h \
    logic/project_value.h \
    logic/step.h \
    mainwindow.h \
    milestone_widget.h \
    parameters.h \
    view/Checkpoint_picker_view.h \
    view/a_project_view.h \
    view/category_view.h \
    view/checkpoint_view.h \
    view/pages/Add_page.h \
    view/pages/Project_page.h \
    view/pages/Stat_page.h \
    view/project_picker_view.h \
    view/project_step_value_view.h \
    view/project_step_view.h \
    view/project_value_view.h \
    view/project_view.h \
    view/step_picker_view.h \
    view/step_view.h

FORMS += \
    components/color_picker.ui \
    components/date_picker.ui

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
    images/user.png \
    left_arrow.svg \
    number.svg \
    right_arrow.svg \
    scripts/create.sql \
    scripts/init.sql
