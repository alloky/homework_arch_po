# FROM conanio/gcc7

# RUN pwd

# USER root
FROM ubuntu:16.04


# Install gcc 7
RUN apt update -qq \
&& apt install -yq software-properties-common python-software-properties \
&& add-apt-repository -y ppa:ubuntu-toolchain-r/test \
&& apt update -qq \
&& apt install -yq g++-7 \
&& apt clean \
&& rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
# Configure alias
RUN update-alternatives \
 --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 \
 --slave /usr/bin/g++ g++ /usr/bin/g++-7 \
 --slave /usr/bin/gcov gcov /usr/bin/gcov-7 \
 --slave /usr/bin/gcov-tool gcov-tool /usr/bin/gcov-tool-7 \
 --slave /usr/bin/gcc-ar gcc-ar /usr/bin/gcc-ar-7 \
 --slave /usr/bin/gcc-nm gcc-nm /usr/bin/gcc-nm-7 \
 --slave /usr/bin/gcc-ranlib gcc-ranlib /usr/bin/gcc-ranlib-7

RUN update-alternatives --install /usr/bin/x86_64-linux-gnu-gcc x86_64-linux-gnu-gcc /usr/bin/x86_64-linux-gnu-gcc-7 70
RUN update-alternatives --config gcc

RUN gcc --version
RUN g++ --version

RUN apt-get update && apt-get upgrade -y
RUN apt install -y python3 python3-pip software-properties-common
RUN add-apt-repository ppa:deadsnakes/ppa
RUN apt-get update -y
RUN apt install -y python3.7
RUN python3.7 -m pip install --upgrade pip

RUN update-alternatives --install /usr/bin/python python /usr/bin/python3.7 10

RUN apt remove -y cmake
RUN pip install cmake --upgrade

RUN apt install -y gdb

# Conan install
RUN apt update && apt upgrade -y && apt install python3-pip cmake build-essential -y
RUN python3.7 -m pip install conan MarkupSafe==1.1.1


RUN conan profile new default --detect  # Generates default profile detecting GCC and sets old ABI
RUN conan profile update settings.compiler.libcxx=libstdc++11 default  # Sets libcxx to C++11 ABI
RUN conan profile update settings.compiler.version=7.5 default



# Dependencies
RUN apt install -y libssl-dev
RUN apt install libgtest-dev
RUN apt install -y libmysqlclient-dev
RUN cd /usr/src/gtest/ && cmake -DBUILD_SHARED_LIBS=ON && make && cp *.so /usr/lib

# Setup ssh
RUN apt-get update && apt-get install -y openssh-server
RUN mkdir /var/run/sshd
RUN echo 'root:screencast' | chpasswd
RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile

EXPOSE 22
# WORKDIR app

# RUN ls -la ~
# RUN cp /root/host_ssh ~/.ssh
# RUN chown root:$USER ~/.ssh/config
# RUN chmod 644 ~/.ssh/config

# RUN cd /home/conan/app && mkdir build && cd build && conan install ../Conanfile.txt


RUN apt install -y mysql-client

# File managment
RUN mkdir /root/app
ADD ./Conanfile.txt /root/app/Conanfile.txt
ADD ./setup_env.sh /root/app/setup_env.sh
RUN chmod +x /root/app/setup_env.sh

CMD /root/app/setup_env.sh