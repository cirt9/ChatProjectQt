TEMPLATE = subdirs
CONFIG+=ordered
SUBDIRS = \
    Chat

app.depends = src
tests.depends = src

OTHER_FILES += \
    defaults.pri
