QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets phonon4qt5

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    directorysortmodel.cpp \
    exifdateitem.cpp \
    exifdatetimereader.cpp \
    filesystemmodel.cpp \
    folderview.cpp \
    folderviewmodel.cpp \
    itemdelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    sizedelegate.cpp \
    variantitem.cpp

HEADERS += \
    directorysortmodel.h \
    exifdateitem.h \
    exifdatetimereader.h \
    filesystemmodel.h \
    folderview.h \
    folderviewmodel.h \
    itemdelegate.h \
    mainwindow.h \
    sizedelegate.h \
    types.h \
    variantitem.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Kommander_de_DE.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    README.md \
    parent.svg

RESOURCES += \
    main.qrc
