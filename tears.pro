TEMPLATE = subdirs
# Needed to ensure that things are built right, which you have to do yourself :(
CONFIG += ordered

# All the projects in your application are sub-projects of your solution
SUBDIRS = libtears \
          tests/pbkdf2-hmac-sha256 \
          tests/secretbox

# Use .depends to specify that a project depends on another.
pbkdf2-hmac-sha256.depends = libtears
secretbox.depends = libtears
