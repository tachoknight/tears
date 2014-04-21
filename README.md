#Tears#
Tears is a C++ wrapper library of libsodium using Qt datatypes.

There is no stable release of Tears as of yet since development
has just started and also because libsodium has not had a release
since 0.4.5

##Build:##
    git clone <url> tears
    mkdir build
    cd build
    qmake ../tears && make && make check

Currently it builds as a static library by default.

##License:##
The Tears source is distributed under the [ISC License][ISCLICENSE]
like libsodium. However it depends on Qt5 which is available
under [various licenses][QTLicense] which would be required for
Tears to work.

[ISCLICENSE]: http://opensource.org/licenses/ISC
[QTLicense]: http://qt-project.org/legal.html)
##Todo:##
- Wrap more of libsodium
- Extend QByteArray and QString so they wipe reallocated / freed memory
- Make build system more package friendly
  (inc. shared library support for unittests)