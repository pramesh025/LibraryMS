QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_page.cpp \
    main.cpp \
    login.cpp \
    student_page.cpp

HEADERS += \
    admin.h \
    admin_page.h \
    book.h \
    date.h \
    json_parsing.h \
    login.h \
    student.h \
    student_page.h \
    user.h

FORMS += \
    admin_page.ui \
    login.ui \
    student_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    JSON/admin_data.json \
    JSON/book_data.json \
    JSON/student_data.json \
    img/default_profile.jpg
