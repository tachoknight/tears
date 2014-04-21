#!/bin/sh
# Installs sodium on travis
set -ex
wget https://github.com/jedisct1/libsodium/archive/master.tar.gz -O /tmp/sodium.tar.gz
tar -xzvf /tmp/sodium.tar.gz
cd libsodium-master && ./configure --prefix=/usr && make && make check && make install
