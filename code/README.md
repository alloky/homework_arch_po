# Introduction 
TODO: Give a short introduction of your project. Let this section explain the objectives or the motivation behind this project. 


# Build and Test
TODO: Describe and show how to build your code and run the tests. 

# Contribute
TODO: Explain how other users and developers can contribute to make your code better. 

# Installation and Dependancy

## Install Cmake
sudo apt-get install gcc
sudo apt-get install g++
sudo apt-get install cmake

## Install OpenSSL
sudo apt-get install libssl-dev

## zlib
sudo apt-get install zlib1g-dev

## mysql
sudo apt-get install mysql-server
sudo apt-get install mysql-client
sudo apt-get install libmysqlclient-dev

## Install poco
git clone -b master https://github.com/pocoproject/poco.git
cd poco
mkdir cmake-build
cd cmake-build
cmake ..
cmake --build . --config Release
sudo cmake --build . --target install

## Install gtest
sudo apt-get install libgtest-dev
cd /usr/src/gtest/
sudo cmake -DBUILD_SHARED_LIBS=ON
sudo make
sudo cp *.so /usr/lib

## Update Library Cache
sudo ldconfig

## Don't forget to start mysql
sudo mysql_secure_installation utility
sudo systemctl start mysql
sudo systemctl enable mysql

## MySQL configuration hints
/etc/mysql/mysql.conf.d/mysqld.cnf:
skip-grant-tables
bind-address		= 127.0.0.1 ( The default. )
bind-address		= XXX.XXX.XXX.XXX ( The ip address of your Public Net interface. )
bind-address		= ZZZ.ZZZ.ZZZ.ZZZ ( The ip address of your Service Net interface. )
bind-address		= 0.0.0.0 ( All ip addresses. )

Access from other machines:
CREATE USER 'root'@'%' IDENTIFIED BY 'some_pass';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%';