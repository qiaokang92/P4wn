#!/bin/bash
# Setup script for assert-p4
# author: Gabriel Martins <gabrielnmartins@gmail.com>

MAIN_INSTALL_DIR=$(pwd)

sudo apt-get update
sudo apt-get install -y git vim

#========================================================================================
#=== Installing p4c =====================================================================
# adapted from https://github.com/jafingerhut/p4-guide/blob/master/bin/install-p4dev.sh
#========================================================================================

echo "#==============================================================================="
echo "#=== Installing p4c ============================================================"
echo "# adapted from https://github.com/jafingerhut/p4-guide/blob/master/bin/install-p4dev.sh"
echo "#==============================================================================="

MAX_PARALLEL_JOBS=3
INSTALL_DIR="${PWD}"
THIS_SCRIPT_FILE_MAYBE_RELATIVE="$0"
THIS_SCRIPT_DIR_MAYBE_RELATIVE="${THIS_SCRIPT_FILE_MAYBE_RELATIVE%/*}"
THIS_SCRIPT_DIR_ABSOLUTE=`readlink -f "${THIS_SCRIPT_DIR_MAYBE_RELATIVE}"`

# protobuf dependencies
sudo apt-get install -y autoconf automake libtool curl make unzip

# p4c dependencies
sudo apt-get install -y git automake libtool libgc-dev bison flex libfl-dev \
	libgmp-dev libboost-dev libboost-iostreams-dev libboost-graph-dev pkg-config \
	python python-scapy python-ipaddr python-ply tcpdump cmake

# behavioral model
echo "Installing p4lang/behavioral-model..."

cd "${INSTALL_DIR}"
git clone https://github.com/p4lang/behavioral-model.git
cd behavioral-model
./install_deps.sh
./autogen.sh
./configure 'CXXFLAGS=-O0 -g'
make
sudo make install

# protobuf
echo "Installing google/protobuf..."

cd "${INSTALL_DIR}"
git clone https://github.com/google/protobuf
cd protobuf

git checkout v3.2.0
./autogen.sh
./configure
make
sudo make install
sudo ldconfig

make clean

# p4c => forked p4c:0.1.0, p4c-bm2-ss:0.0.5
echo "Installing p4c..."

cd "${INSTALL_DIR}"
git clone --recursive https://github.com/gnmartins/p4c.git

cd p4c
mkdir build
cd build
# Configure for a debug build
cmake .. -DCMAKE_BUILD_TYPE=DEBUG $*
make -j${MAX_PARALLEL_JOBS}
cd "${INSTALL_DIR}"

#========================================================================================
#=== Installing p4pktgen ================================================================
#========================================================================================

echo "#==============================================================================="
echo "#=== Installing p4pktgen ======================================================="
echo "#==============================================================================="

git clone https://github.com/p4pktgen/p4pktgen.git

cd p4pktgen
./tools/install.sh
cd "${INSTALL_DIR}"

exit 0

#========================================================================================
#=== Installing klee ====================================================================
# adapted from https://github.com/tum-i22/klee-install/blob/master/README.md
#========================================================================================

echo "#==============================================================================="
echo "#=== Installing klee ==========================================================="
echo "# adapted from https://github.com/tum-i22/klee-install/blob/master/README.md"
echo "#==============================================================================="

mkdir klee-build
BUILDDIR="klee-build"
cd "$BUILDDIR"

# dependencies
sudo apt-get install -y bc bison build-essential cmake curl flex git libboost-all-dev \
	libcap-dev libncurses5-dev python-minimal python-pip subversion unzip zlib1g-dev

#=== LLVM ===========================
echo "Building LLVM..."

svn co https://llvm.org/svn/llvm-project/llvm/tags/RELEASE_342/final llvm
svn co https://llvm.org/svn/llvm-project/cfe/tags/RELEASE_342/final llvm/tools/clang
svn co https://llvm.org/svn/llvm-project/compiler-rt/tags/RELEASE_342/final llvm/projects/compiler-rt
svn co https://llvm.org/svn/llvm-project/libcxx/tags/RELEASE_342/final llvm/projects/libcxx
svn co https://llvm.org/svn/llvm-project/test-suite/tags/RELEASE_342/final/ llvm/projects/test-suite

rm -rf llvm/.svn
rm -rf llvm/tools/clang/.svn
rm -rf llvm/projects/compiler-rt/.svn
rm -rf llvm/projects/libcxx/.svn
rm -rf llvm/projects/test-suite/.svn

cd llvm
./configure --enable-optimized --disable-assertions --enable-targets=host --with-python="/usr/bin/python2"
make -j `nproc`

make -j `nproc` check-all
cd ..

#====================================
#=== Minisat ========================
echo "Building Minisat..."

git clone --depth 1 https://github.com/stp/minisat.git
rm -rf minisat/.git

cd minisat
make
cd ..

#====================================
#=== STP ============================
echo "Building STP..."

git clone --depth 1 --branch stp-2.2.0 https://github.com/stp/stp.git
rm -rf stp/.git

cd stp
mkdir build
cd build
cmake \
 -DBUILD_STATIC_BIN=ON \
 -DBUILD_SHARED_LIBS:BOOL=OFF \
 -DENABLE_PYTHON_INTERFACE:BOOL=OFF \
 -DMINISAT_INCLUDE_DIR="../../minisat/" \
 -DMINISAT_LIBRARY="../../minisat/build/release/lib/libminisat.a" \
 -DCMAKE_BUILD_TYPE="Release" \
 -DTUNE_NATIVE:BOOL=ON ..
make -j `nproc`
cd ../..

#====================================
#=== uclibc =========================
echo "Building uclibc and the POSIX environment model..."

git clone --depth 1 --branch klee_uclibc_v1.0.0 https://github.com/klee/klee-uclibc.git
rm -rf klee-uclibc/.git

cd klee-uclibc
./configure \
 --make-llvm-lib \
 --with-llvm-config="../llvm/Release/bin/llvm-config" \
 --with-cc="../llvm/Release/bin/clang"
make -j `nproc`
cd ..

#====================================
#=== Z3 =============================
echo "Building Z3..."

git clone --depth 1 --branch z3-4.5.0 https://github.com/Z3Prover/z3.git
rm -rf z3/.git

cd z3
python scripts/mk_make.py
cd build
make -j `nproc`

# partialy copied from make install target
mkdir -p ./include
mkdir -p ./lib
cp ../src/api/z3.h ./include/z3.h
cp ../src/api/z3_v1.h ./include/z3_v1.h
cp ../src/api/z3_macros.h ./include/z3_macros.h
cp ../src/api/z3_api.h ./include/z3_api.h
cp ../src/api/z3_ast_containers.h ./include/z3_ast_containers.h
cp ../src/api/z3_algebraic.h ./include/z3_algebraic.h
cp ../src/api/z3_polynomial.h ./include/z3_polynomial.h
cp ../src/api/z3_rcf.h ./include/z3_rcf.h
cp ../src/api/z3_fixedpoint.h ./include/z3_fixedpoint.h
cp ../src/api/z3_optimization.h ./include/z3_optimization.h
cp ../src/api/z3_interp.h ./include/z3_interp.h
cp ../src/api/z3_fpa.h ./include/z3_fpa.h
cp libz3.so ./lib/libz3.so
cp ../src/api/c++/z3++.h ./include/z3++.h

cd ../..

#====================================
#=== KLEE ===========================
echo "Building KLEE..."

git clone --depth 1 --branch 1.3.x https://github.com/gnmartins/klee.git
rm -rf klee/.git

BUILDDIR=`pwd`
cd klee
./configure \
 LDFLAGS="-L$BUILDDIR/minisat/build/release/lib/" \
 --with-llvm=$BUILDDIR/llvm/ \
 --with-llvmcc=$BUILDDIR/llvm/Release/bin/clang \
 --with-llvmcxx=$BUILDDIR/llvm/Release/bin/clang++ \
 --with-stp=$BUILDDIR/stp/build/ \
 --with-uclibc=$BUILDDIR/klee-uclibc \
 --with-z3=$BUILDDIR/z3/build/ \
 --enable-cxx11 \
 --enable-posix-runtime

make -j `nproc` ENABLE_OPTIMIZED=1

# Copy Z3 libraries to a place, where klee can find them
cp ../z3/build/lib/libz3.so ./Release+Asserts/lib/

make -j `nproc` check
cd ..

#========================================================================================
echo "#==============================================================================="

echo -e "\n" >> ~/.profile
echo "# assert-p4:" >> ~/.profile
echo "# p4c binaries" >> ~/.profile
echo "P4C_BUILD_DIR="$MAIN_INSTALL_DIR/p4c/build"" >> ~/.profile
echo "" >> ~/.profile
echo "# klee binaries" >> ~/.profile
echo "KLEE_BIN_DIR="$MAIN_INSTALL_DIR/klee-build/klee/Release+Asserts/bin"" >> ~/.profile
echo "LLVM_BIN_DIR="$MAIN_INSTALL_DIR/klee-build/llvm/Release/bin"" >> ~/.profile
echo "" >> ~/.profile
echo "PATH="\$P4C_BUILD_DIR:\$KLEE_BIN_DIR:\$LLVM_BIN_DIR:\$HOME/bin:\$HOME/.local/bin:\$PATH"" >> ~/.profile

echo "All assert-p4 dependencies have been compiled."
echo "The build directories have been added to your PATH in ~/.profile"
echo -e "\tP4C_BUILD_DIR=\"$MAIN_INSTALL_DIR/p4c/build\""
echo -e "\tKLEE_BIN_DIR=\"$MAIN_INSTALL_DIR/klee-build/klee/Release+Asserts/bin\""
echo -e "\tLLVM_BIN_DIR=\"$MAIN_INSTALL_DIR/klee-build/llvm/Release/bin\""
echo "For any suggestions, please contact <gabrielnmartins@gmail.com>."

echo "#==============================================================================="
