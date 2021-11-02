#!/bin/bash

/usr/sbin/sshd

update-alternatives \
 --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 \
 --slave /usr/bin/g++ g++ /usr/bin/g++-7 \
 --slave /usr/bin/gcov gcov /usr/bin/gcov-7 \
 --slave /usr/bin/gcov-tool gcov-tool /usr/bin/gcov-tool-7 \
 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-7 \
 --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-7 \
 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-7

until cd /root/app/code/build && conan install ../../Conanfile.txt --build=missing
do
    echo "Retrying conan install"
done

echo "==================================="
echo "Conan dependencies install success"
echo "==================================="


cd /root/app/code/build && cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cd /root/app/code/build && cmake --build .


DB="hl";
USER="root";
PASS="3.14Oneer";

until mysql -uroot -p3.14Oneer -h db -e "CREATE DATABASE IF NOT EXISTS $DB;" && cd /root/app/code/build/bin && ./server -db
do
    echo "Retrying db creation"
done

echo "==============================="
echo "db created success"
echo "==============================="


