cd .. 
mkdir build-${TYPE}
cd build-${TYPE}
qmake "CONFIG+=${TYPE}" ../tears && make && make -s check
