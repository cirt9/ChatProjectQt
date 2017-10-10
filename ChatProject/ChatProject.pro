TEMPLATE = subdirs
CONFIG+=ordered
SUBDIRS = \
    Chat \
    ChatClient \
    ChatServer

app.depends = src
tests.depends = src

OTHER_FILES += \
    defaults.pri
