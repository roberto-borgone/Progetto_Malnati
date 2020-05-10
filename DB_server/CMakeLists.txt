cmake_minimum_required(VERSION 3.15)
project(DB_server)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5WebSockets REQUIRED)
#find_package(openssl REQUIRED)

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::WebSockets
        #OpenSSL::SSL
        )
list(REMOVE_DUPLICATES LIBRARIES)

add_executable(DB_server main.cpp DB_functions.cpp DB_functions.h sqlite3.c sqlite3.h DB_server.cpp DB_server.h)
target_link_libraries(DB_server ${LIBRARIES})