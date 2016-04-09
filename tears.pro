TEMPLATE = subdirs
# Needed to ensure that things are built right, which you have to do yourself :(
CONFIG += ordered
mac:QT_CONFIG -= no-pkg-config

# All the projects in your application are sub-projects of your solution
SUBDIRS = libtears \
          tests

# All tests depend on libtears so it will be built first
tests.depends = libtears
