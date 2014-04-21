#!/bin/sh
# Installs sodium on travis
set -ex
wget -q https://github.com/jedisct1/libsodium/archive/master.tar.gz -O /tmp/sodium.tar.gz
ar -xzf /tmp/sodium.tar.gz
cd libsodium-master && ./autogen.sh && ./configure -prefix=/usr && make -s && make check && sudo make install
