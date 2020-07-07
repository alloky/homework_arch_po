cmake_minimum_required(VERSION 3.2)

project(hl_homework_01 C CXX)

SET (WEBSERVICE_BINARY "server")

include(FindPkgConfig)
find_package(PkgConfig QUIET REQUIRED)
pkg_check_modules(MYSQL REQUIRED QUIET mysqlclient)

find_package(OpenSSL)
find_package(GTest REQUIRED)
find_package(Threads)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL DataMySQL)

if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(${WEBSERVICE_BINARY} main.cpp 
                                    web_server/session/session.cpp
                                    database/database.cpp)

target_include_directories(${WEBSERVICE_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${WEBSERVICE_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )

add_executable(gtests tests.cpp)

target_link_libraries(gtests ${GTEST_LIBRARIES} 
                             ${CMAKE_THREAD_LIBS_INIT}                             
                             ${Poco_LIBRARIES})

target_link_libraries(${WEBSERVICE_BINARY} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES})

set_target_properties(gtests PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${WEBSERVICE_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(gtests PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
set_target_properties(${WEBSERVICE_BINARY} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

install(TARGETS ${WEBSERVICE_BINARY} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT Dmitriy.Dzyuba@mts.ru)
include(CPack)
enable_testing()
add_test(gtests gtests)
