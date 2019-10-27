cmake_minimum_required(VERSION 3.13)
project(editorCollaborativo)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts )
list(REMOVE_DUPLICATES LIBRARIES)

add_executable(editorCollaborativo main.cpp Gui.cpp Gui.h Project.cpp Project.h Symbol.cpp Symbol.h Network.cpp Network.h)
target_link_libraries(editorCollaborativo ${LIBRARIES})










