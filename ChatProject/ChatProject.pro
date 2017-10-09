TEMPLATE = subdirs
CONFIG+=ordered
SUBDIRS = \
    Chat \
    ChatClient

app.depends = src
tests.depends = src

OTHER_FILES += \
    defaults.pri
