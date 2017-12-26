# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8.11)
project (ncursesfm++)

include_directories(inc src)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB SOURCES src/*.cpp inc/*.hpp)

add_executable(ncursesfm++ main.cpp ${SOURCES})

find_package(PkgConfig REQUIRED)
find_package(Libnotify)
if(LIBNOTIFY_FOUND)
    message("Using libnotify")
    add_definitions( -DLIBNOTIFY_FOUND)
endif(LIBNOTIFY_FOUND)
find_package(Threads)

set(CURSES_NEED_NCURSES TRUE)
find_package(Ncursesw REQUIRED)

target_include_directories(ncursesfm++
	PRIVATE ${NCURSESW_INCLUDE_DIRS}
	PRIVATE ${LIBNOTIFY_INCLUDE_DIRS}
	PUBLIC include)

target_link_libraries(ncursesfm++
	${NCURSESW_LIBRARIES}
	${LIBNOTIFY_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT})

set_property(TARGET ncursesfm++ PROPERTY CXX_STANDARD 14)
