# Install script for directory: /root/app/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/x86_64-linux-gnu-objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/server" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/server")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/server"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/root/app/code/build/bin/server")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/server" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/server")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/server"
         OLD_RPATH "/root/.conan/data/poco/1.11.0/_/_/package/22eda37759af2fef19902bdcb425dc1c049c7f23/lib:/root/.conan/data/pcre/8.45/_/_/package/9f7bf24b68c18f44b467c84f6f20820cfade908b/lib:/root/.conan/data/sqlite3/3.36.0/_/_/package/b44911574631882247d36a430d78dc66c47fc715/lib:/root/.conan/data/libpq/13.3/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/lib:/root/.conan/data/apr-util/1.6.1/_/_/package/881d178633bea5d3359192e7549c627a24074cec/lib:/root/.conan/data/libmysqlclient/8.0.25/_/_/package/f819302ae9fcf6ed467016ec2ec42696fdfba3d9/lib:/root/.conan/data/bzip2/1.0.8/_/_/package/5712964edf62ce3618094532519f7c0e8fc974cf/lib:/root/.conan/data/zlib/1.2.11/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/lib:/root/.conan/data/expat/2.4.1/_/_/package/8b564c3f5d90fb08f38ee6674624686b669b5ec1/lib:/root/.conan/data/openssl/1.1.1k/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/lib:/root/.conan/data/apr/1.7.0/_/_/package/1e34ecce38a6fd778c8f9c3e2aada8c48b3703d3/lib:/root/.conan/data/libiconv/1.16/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/lib:/root/.conan/data/zstd/1.5.0/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/lib:/root/.conan/data/lz4/1.9.3/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/lib:/usr/local/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/x86_64-linux-gnu-strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/server")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/root/app/code/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
