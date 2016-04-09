TEMPLATE = subdirs
# Needed to ensure that things are built right, which you have to do yourself :(
CONFIG += ordered
mac:QT_CONFIG -= no-pkg-config

# All the projects in your application are sub-projects of your solution
SUBDIRS = \
    pbkdf2-hmac-sha256 \
    secretbox \
    box \
    pwhash_scrypt
