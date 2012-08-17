#-------------------------------------------------
#
# Project created by QtCreator 2012-08-12T18:24:54
#
#-------------------------------------------------

QT       += core gui network

TARGET = ColonyServer
TEMPLATE = app


SOURCES += main.cpp\
		colonyserver.cpp \
	network/networkconfigurator.cpp \
	data/clientmodel.cpp \
	network/client.cpp \
	network/server.cpp \
	data/colonymodel.cpp \
    protocol/protocol.cpp \
    protocol/jsonprotocol.cpp

HEADERS  += colonyserver.hpp \
	network/networkconfigurator.hpp \
	data/clientmodel.hpp \
	network/client.hpp \
	network/server.hpp \
	data/colonymodel.hpp \
    protocol/protocol.hpp \
    protocol/jsonprotocol.hpp

FORMS    += colonyserver.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../colonyutils-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK__Release/release/ -lcolonyutils
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../colonyutils-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK__Release/debug/ -lcolonyutils
else:symbian: LIBS += -lcolonyutils
else:unix: LIBS += -L$$PWD/../colonyutils-build-desktop-Desktop_Qt_4_8_0_for_GCC__Qt_SDK__Release/ -lcolonyutils

INCLUDEPATH += $$PWD/../colonyutils
DEPENDPATH += $$PWD/../colonyutils

unix|win32: LIBS += -lqjson
