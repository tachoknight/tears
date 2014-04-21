set -ex
cd .. 
mkdir build-${TYPE}
cd build-${TYPE}
echo "Running qmake"
qmake "CONFIG+=${TYPE}" ../tears 
echo "Running make"
make 
echo "Running tests"
make -s check
