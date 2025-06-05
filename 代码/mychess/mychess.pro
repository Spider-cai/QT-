HEADERS += \
    Begin.h \
    Board.h \
    Chosse_oneortwo.h \
    GameMidia.h \
    NetGame.h \
    Stone.h \
    Voice.h

SOURCES += \
    Begin.cpp \
    Board.cpp \
    Chosse_oneortwo.cpp \
    GameMidia.cpp \
    NetGame.cpp \
    Stone.cpp \
    Voice.cpp \
    main.cpp

QT += widgets gui network multimedia

RESOURCES += \
    Resource.qrc

FORMS += \
    Begin.ui \
    chosse_oneortwo.ui

CONFIG+=resources_big
