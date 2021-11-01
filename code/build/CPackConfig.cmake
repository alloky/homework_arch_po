# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "/root/app/code;/root/app/code/build")
set(CPACK_CMAKE_GENERATOR "Unix Makefiles")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/local/lib/python3.7/dist-packages/cmake/data/share/cmake-3.21/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "hl_homework_01 built using CMake")
set(CPACK_GENERATOR "DEB")
set(CPACK_INSTALL_CMAKE_PROJECTS "/root/app/code/build;hl_homework_01;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "/root/.conan/data/poco/1.11.0/_/_/package/22eda37759af2fef19902bdcb425dc1c049c7f23/;/root/.conan/data/pcre/8.45/_/_/package/9f7bf24b68c18f44b467c84f6f20820cfade908b/;/root/.conan/data/sqlite3/3.36.0/_/_/package/b44911574631882247d36a430d78dc66c47fc715/;/root/.conan/data/sqlite3/3.36.0/_/_/package/b44911574631882247d36a430d78dc66c47fc715/lib/cmake;/root/.conan/data/libpq/13.3/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/;/root/.conan/data/apr-util/1.6.1/_/_/package/881d178633bea5d3359192e7549c627a24074cec/;/root/.conan/data/libmysqlclient/8.0.25/_/_/package/f819302ae9fcf6ed467016ec2ec42696fdfba3d9/;/root/.conan/data/bzip2/1.0.8/_/_/package/5712964edf62ce3618094532519f7c0e8fc974cf/;/root/.conan/data/bzip2/1.0.8/_/_/package/5712964edf62ce3618094532519f7c0e8fc974cf/lib/cmake;/root/.conan/data/zlib/1.2.11/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/;/root/.conan/data/expat/2.4.1/_/_/package/8b564c3f5d90fb08f38ee6674624686b669b5ec1/;/root/.conan/data/openssl/1.1.1k/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/;/root/.conan/data/openssl/1.1.1k/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/lib/cmake;/root/.conan/data/apr/1.7.0/_/_/package/1e34ecce38a6fd778c8f9c3e2aada8c48b3703d3/;/root/.conan/data/libiconv/1.16/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/;/root/.conan/data/zstd/1.5.0/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/;/root/.conan/data/lz4/1.9.3/_/_/package/6c07b793c4aa4ddff70625d62e11a1646fcbd578/")
set(CPACK_NSIS_DISPLAY_NAME "hl_homework_01 ")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "hl_homework_01 ")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "/root/app/code/build/CPackConfig.cmake")
set(CPACK_PACKAGE_CONTACT "Dmitriy.Dzyuba@mts.ru")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/local/lib/python3.7/dist-packages/cmake/data/share/cmake-3.21/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "hl_homework_01 built using CMake")
set(CPACK_PACKAGE_FILE_NAME "hl_homework_01--Linux")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "hl_homework_01 ")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "hl_homework_01 ")
set(CPACK_PACKAGE_NAME "hl_homework_01")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "")
set(CPACK_PACKAGE_VERSION_MAJOR "")
set(CPACK_PACKAGE_VERSION_MINOR "")
set(CPACK_PACKAGE_VERSION_PATCH "")
set(CPACK_RESOURCE_FILE_LICENSE "/usr/local/lib/python3.7/dist-packages/cmake/data/share/cmake-3.21/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/usr/local/lib/python3.7/dist-packages/cmake/data/share/cmake-3.21/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/local/lib/python3.7/dist-packages/cmake/data/share/cmake-3.21/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/root/app/code/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_RPM "OFF")
set(CPACK_SOURCE_TBZ2 "ON")
set(CPACK_SOURCE_TGZ "ON")
set(CPACK_SOURCE_TXZ "ON")
set(CPACK_SOURCE_TZ "ON")
set(CPACK_SOURCE_ZIP "OFF")
set(CPACK_SYSTEM_NAME "Linux")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "Linux")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/root/app/code/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
