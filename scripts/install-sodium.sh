#!/bin/sh
# Installs sodium on travis
set -ex
wget https://github.com/jedisct1/libsodium/archive/master.zip -O /tmp/sodium.tar.gz
tar -xzvf sodium.tar.gz
cd sodium-master && ./configure --prefix=/usr && make && make check && make install
