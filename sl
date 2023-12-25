cmake_minimum_required(VERSION 3.10)
project(aos LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql Xml Network Widgets Multimedia)

set(aos_APPS
    app/main.cpp
)

set(aos_SRCS
    src/aos.cpp
)

set(aos_MOCS
    include/aos.h
)

set(aos_SUBS
    window-info/include/windowinfo.h
    window-info/src/windowinfo.cpp
    window-info/info.qrc
)

include_directories(
    include
    window-info/include
)

add_executable(aos
    ${aos_APPS}
    ${aos_SRCS}
    ${aos_MOCS}
    ${aos_SUBS}
)

target_link_libraries(aos Qt5::Core Qt5::Sql Qt5::Xml Qt5::Network Qt5::Widgets Qt5::Multimedia)

# Install rules
install(TARGETS aos DESTINATION local/ni/aos/bin)
install(DIRECTORY window-info/ DESTINATION local/ni/aos/window-info)
install(FILES ${CPACK_PACKAGE_FILES_SYS} DESTINATION /etc/systemd/system)
install(FILES ${CPACK_PACKAGE_FILES_CONF} DESTINATION local/ni/aos/etc)
install(FILES ${CPACK_PACKAGE_FILES_SQL} DESTINATION local/ni/aos/sql)

# CPack configuration
set(CPACK_PACKAGE_NAME "aos")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VERSION  "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "aos - Interaction Software Other System")
set(CPACK_PACKAGE_VENDOR "NI")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5sql5-psql, as")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Andrey") # required
set(CPACK_PACKAGE_CONTACT "Koov Akoshuraa@n")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}.${CPACK_PACKAGE_VERSION}.${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA 
        ${CMAKE_CURRENT_SOURCE_DIR}/debian/postinst
        ${CMAKE_CURRENT_SOURCE_DIR}/debian/postrm)

# Debian directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/debian)

# changelog file
configure_file(debian/changelog.in ${CMAKE_CURRENT_BINARY_DIR}/debian/changelog @ONLY)

# compat file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/compat "9\n")

# control file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/control
"Source: ${CPACK_PACKAGE_NAME}
Maintainer: Andrey <knikovaa@.ru>, Ivan <i.m.thchev@.ru>
Section: misc
Priority: optional
Standards-Version: 3.9.3
Build-Depends: debhelper (>= 9)

Package: ${CPACK_PACKAGE_NAME}
Architecture: ${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}
Depends: \${shlibs:Depends}, \${misc:Depends}, libqt5sql5-psql, \${CPACK_DEBIAN_PACKAGE_DEPENDS}
Description: ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}
")

# rules file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/rules
"#!/usr/bin/make -f

%:
    dh \$@
")

# source/format file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/source/format "3.0 (quilt)\n")

# aos.install file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/${CPACK_PACKAGE_NAME}.install
"bin/* usr/local/ni/aos/bin
csqldatabase/share/sql/* usr/local/ni/aos/sql
csettings/share/conf.d/* usr/local/ni/aos/etc
share/desktop/* usr/share/applications
share/desktop/* etc/xdg/autostart
share/service/* lib/systemd/system
gui-systemtray/share/image/tray.png usr/local/ni/aos/icons")

# aos.dirs file
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/${CPACK_PACKAGE_NAME}.dirs
"usr/local/ni/aos/bin
usr/local/ni/aos/etc
usr/local/ni/aos/sql
usr/local/ni/aos/icons")

include(CPack)
