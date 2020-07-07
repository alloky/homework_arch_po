# Introduction 
TODO: Give a short introduction of your project. Let this section explain the objectives or the motivation behind this project. 


# Build and Test
TODO: Describe and show how to build your code and run the tests. 

# Contribute
TODO: Explain how other users and developers can contribute to make your code better. 

# Installation and Dependancy
## Install OpenSSL
sudo apt-get install libssl-dev

## Install mysql

sudo apt-get install python3-dev default-libmysqlclient-dev build-essential
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install.sh)"

## install openssl
brew install openssl

## mysql
sudo apt-get install mysql-server
sudo apt-get install mysql-client
sudo apt-get install libmysqlclient-dev

## Install boost
sudo apt-get update
sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev

## Install cmake
sudo apt install cmake

## Install poco
git clone -b master https://github.com/pocoproject/poco.git
cd poco
mkdir cmake-build
cd cmake-build
cmake ..
cmake --build . --config Release
sudo cmake --build . --target install

## Install gtest
sudo apt isntall libgtest-dev
cd /usr/src/gtest/
sudo cmake -DBUILD_SHARED_LIBS=ON
sudo make
sudo cp *.so /usr/lib

## Install protobuf
https://github.com/protocolbuffers/protobuf/blob/master/src/README.md
git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
git submodule update --init --recursive
./autogen.sh
./configure
make
make check
sudo make install
sudo ldconfig # refresh shared library cache.


## Install gcc 9
sudo apt install software-properties-common
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt install gcc-7 g++-7 gcc-8 g++-8 gcc-9 g++-9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9 --slave /usr/bin/gcov gcov /usr/bin/gcov-9

## Generate cert
passphase: secret
openssl req -x509 -days 365 -newkey rsa:2048 -keyout any.pem -out any.pem
openssl req -new -key any.pem -out server.csr #no more -any.pem
openssl x509 -req -in server.csr -signkey any.pem -out rootcert.pem