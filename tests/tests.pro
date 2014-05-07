TEMPLATE = subdirs
# Needed to ensure that things are built right, which you have to do yourself :(
CONFIG += ordered

# All the projects in your application are sub-projects of your solution
SUBDIRS = \
    pbkdf2-hmac-sha256 \
    secretbox \
    box \
    pwhash_scrypt

# Use .depends to specify that a project depends on another.
pbkdf2-hmac-sha256.depends = libtears
secretbox.depends = libtears
box.depends = libtears
pwhash_scrypt.depends = libtears

