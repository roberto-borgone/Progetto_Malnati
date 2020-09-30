cmake_minimum_required(VERSION 3.13)
project(editorCollaborativo)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(libcurl_INCLUDE_DIR "C:/Curl/curl-7.72.0-win64-mingw/include")

include_directories(${libcurl_INCLUDE_DIR})

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5WebSockets REQUIRED)

list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        Qt5::WebSockets)
list(REMOVE_DUPLICATES LIBRARIES)

add_executable(editorCollaborativo main.cpp Gui.cpp Gui.h Project.cpp Project.h Symbol.cpp Symbol.h Network.cpp Network.h DB_Client.cpp DB_Client.h PopUp.h ProjectsPopup.h ClickableLabel.h NewProjectPopUp.h Profile.cpp Profile.h WrongCredentialsPopUp.h Mail.cpp Mail.h)
target_link_libraries(editorCollaborativo ${LIBRARIES} ws2_32 C:/Curl/curl-7.72.0-win64-mingw/lib/libcurl.dll.a)










