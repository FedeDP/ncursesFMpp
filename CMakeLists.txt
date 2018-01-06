cmake_minimum_required (VERSION 3.3.2)

project (ncursesfm++ VERSION 0.5)

set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)

include_directories(inc src)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

file(GLOB SOURCES src/*.cpp inc/*.hpp)

add_executable(ncursesfm++ ${SOURCES} Extra/ncursesFM++.conf)

install (TARGETS ncursesfm++ DESTINATION bin)
install(FILES Extra/ncursesFM++.conf DESTINATION etc/default COMPONENT config)

find_package(PkgConfig REQUIRED)
find_package(Threads)
set(CURSES_NEED_NCURSES TRUE)
find_package(Ncursesw REQUIRED)
find_package(Udev REQUIRED)
find_package(libconfig++ REQUIRED)
find_package(Gettext REQUIRED)
find_package(Intl REQUIRED)

target_include_directories(ncursesfm++
	PRIVATE ${NCURSESW_INCLUDE_DIRS}
	PRIVATE ${UDEV_INCLUDE_DIRS}
	PRIVATE ${LIBCONFIG++_INCLUDE_DIRS}
	PRIVATE ${Intl_INCLUDE_DIRS}
	PUBLIC include)

target_link_libraries(ncursesfm++
	${NCURSESW_LIBRARIES}
	${UDEV_LIBRARIES}
	${LIBCONFIG++_LIBRARIES}
	${Intl_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	stdc++fs)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DCONFIG_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Extra/ncursesFM++.conf")
else()
    add_definitions(-DCONFIG_PATH="/etc/default/ncursesFM++.conf")
endif()

add_definitions(-DLOCALEDIR="${CMAKE_INSTALL_PREFIX}/share/locale")

file(GLOB LANGS po/*.po)
GETTEXT_CREATE_TRANSLATIONS (po/ncursesFM++.pot ALL ${LANGS})

INCLUDE(InstallRequiredSystemLibraries)
 
SET(CPACK_SET_DESTDIR "on")
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Federico Di Pierro <nierro92@gmail.com>")
SET(CPACK_PACKAGE_DESCRIPTION "ncurses file manager written in c++")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast, lightweight and user friendly file manager")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libncursesw5 libconfig++9 gettext libudev1")
SET(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
SET(CPACK_DEBIAN_PACKAGE_SECTION "utils")
 
INCLUDE(CPack)

set_property(TARGET ncursesfm++ PROPERTY CXX_STANDARD 14)
