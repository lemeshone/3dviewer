TEMPLATE = app
CONFIG += c++20 console
QT += widgets openglwidgets

SOURCES += \
    main.cpp \
    View/mainwindow.cpp \
    model/model.cpp \
    model/affineTransformer.cpp \
    Controller/controller.cpp \
    View/wireframewidget.cpp

HEADERS += \
    View/mainwindow.h \
    model/model.h \
    model/affineTransformer.h \
    Controller/controller.h \
    View/wireframewidget.h

FORMS += \
    View/mainwindow.ui