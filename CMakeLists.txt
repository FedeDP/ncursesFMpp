# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)

project (ncursesfm++)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

include_directories(inc src)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB SOURCES src/*.cpp inc/*.hpp)

add_executable(ncursesfm++ main.cpp ${SOURCES})

find_package(PkgConfig REQUIRED)
find_package(Threads)
set(CURSES_NEED_NCURSES TRUE)
find_package(Ncursesw REQUIRED)
find_package(Udev REQUIRED)
find_package(libconfig++ REQUIRED)

target_include_directories(ncursesfm++
	PRIVATE ${NCURSESW_INCLUDE_DIRS}
	PRIVATE ${UDEV_INCLUDE_DIRS}
	PRIVATE ${LIBCONFIG++_INCLUDE_DIRS}
	PUBLIC include)

target_link_libraries(ncursesfm++
	${NCURSESW_LIBRARIES}
	${UDEV_LIBRARIES}
	${LIBCONFIG++_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	stdc++fs)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DCONFIG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Extra/ncursesFM++.conf")
else()
    add_definitions(-DCONFIG_PATH="/etc/default/ncursesFM++.conf")
endif()

set_property(TARGET ncursesfm++ PROPERTY CXX_STANDARD 14)
