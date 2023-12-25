cmake_minimum_required(VERSION 2.8.11)

project(isaos LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Core Sql Xml Network Widgets Multimedia)

set(isaos_APPS
    app/main.cpp
    )

set(isaos_SRCS
    src/isaos.cpp
    )

set(isaos_MOCS
    include/isaos.h
    )

set(isaos_SUBS
    window-info/include/windowinfo.h
    window-info/src/windowinfo.cpp
    window-info/info.qrc
    gui-isaos/include/guiisaos.h
    gui-isaos/src/guiisaos.cpp
    gui-isaos/images.qrc
    csettings/include/csettings.h
    csettings/src/csettings.cpp
    setwindow/include/setwindow.h
    setwindow/src/setwindow.cpp
    csqldatabase/include/csqldatabase.h
    csqldatabase/src/csqldatabase.cpp
    txfworker/include/txfdata.h
    txfworker/src/txfdata.cpp
    vfsvmodel/include/vfsvmodel.h
    vfsvmodel/src/vfsvmodel.cpp
    vfsvparser/include/vfsvparser.h
    vfsvparser/src/vfsvparser.cpp
    vfsvgenerator/include/vfsvgenerator.h
    vfsvgenerator/src/vfsvgenerator.cpp
    vfsvxmlgen/include/vfsvxmlgen.h
    vfsvxmlgen/src/vfsvxmlgen.cpp
    vfsvxmlpars/include/vfsvxmlpars.h
    vfsvxmlpars/src/vfsvxmlpars.cpp
    vfsvmanager/include/vfsvmanager.h
    vfsvmanager/src/vfsvmanager.cpp
    vfvpmodel/include/vfvpmodel.h
    vfvpmodel/src/vfvpmodel.cpp
    vfvpparser/include/vfvpparser.h
    vfvpparser/src/vfvpparser.cpp
    vfvpgenerator/include/vfvpgenerator.h
    vfvpgenerator/src/vfvpgenerator.cpp
    vfvpxmlgen/include/vfvpxmlgen.h
    vfvpxmlgen/src/vfvpxmlgen.cpp
    vfvpxmlpars/include/vfvpxmlpars.h
    vfvpxmlpars/src/vfvpxmlpars.cpp
    vfvpmanager/include/vfvpmanager.h
    vfvpmanager/src/vfvpmanager.cpp
    gui-systemtray/include/systemtray.h
    gui-systemtray/src/systemtray.cpp
    gui-systemtray/images.qrc    
    guivfsvtray/include/guivfsv.h
    guivfsvtray/src/guivfsv.cpp
    guivfvptray/include/guivfvp.h
    guivfvptray/src/guivfvp.cpp
    )

include_directories(
    include
    window-info/include
    guivfvptray/include
    guivfsvtray/include    
    gui-systemtray/include
    gui-isaos/include
    csettings/include
    setwindow/include
    csqldatabase/include
    txfworker/include
    vfsvmodel/include
    vfsvparser/include
    vfsvgenerator/include
    vfsvxmlgen/include
    vfsvxmlpars/include
    vfsvmanager/include
    vfvpmodel/include
    vfvpparser/include
    vfvpgenerator/include
    vfvpxmlgen/include
    vfvpxmlpars/include
    vfvpmanager/include
    )

add_executable(isaos
    ${isaos_APPS}
    ${isaos_SRCS}
    ${isaos_MOCS}
    ${isaos_SUBS}
)

target_link_libraries(isaos Qt5::Core Qt5::Sql Qt5::Xml Qt5::Network Qt5::Widgets Qt5::Multimedia )

set(CPACK_PACKAGE_NAME "isaos")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VERSION  "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "ISAOS - Interaction Software Other System")
set(CPACK_PACKAGE_VENDOR "NIISSU")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "asuv")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER " Andrey") # required
set(CPACK_PACKAGE_CONTACT "Koshurnikov Andrey koshurnikovaa@n")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}.${CPACK_PACKAGE_VERSION}.${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA 
        ${CMAKE_CURRENT_SOURCE_DIR}/debian/postinst
        ${CMAKE_CURRENT_SOURCE_DIR}/debian/postrm)
set(CPACK_PACKAGE_FILES_SYS  ${CMAKE_CURRENT_SOURCE_DIR}/share/service/isaos.service)
set(CPACK_PACKAGE_FILES_CONF ${CMAKE_CURRENT_SOURCE_DIR}/csettings/share/conf.d/isaos.conf)
set(CPACK_PACKAGE_FILES_SQL
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_function.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_table.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_function_fs.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_table_fs.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_function_tcp.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_table_tcp.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_function_udp.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_table_udp.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_function_rm.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/asuv_table_rm.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/povz_database.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/povz_table.sql
        ${CMAKE_CURRENT_SOURCE_DIR}/csqldatabase/share/sql/povz_content.sql)
set(CPACK_GENERATOR "DEB")

install(TARGETS isaos DESTINATION local/niissu/isaos/bin)
install(FILES ${CPACK_PACKAGE_FILES_SYS}  DESTINATION /etc/systemd/system)
install(FILES ${CPACK_PACKAGE_FILES_CONF} DESTINATION local/niissu/isaos/etc)
install(FILES ${CPACK_PACKAGE_FILES_SQL}  DESTINATION local/niissu/isaos/sql)

include(CPack)

# Создаем debian-директорию
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/debian)

# Генерируем changelog файл
configure_file(debian/changelog.in ${CMAKE_CURRENT_BINARY_DIR}/debian/changelog @ONLY)
# Создаем compat файла
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/compat "9\n")
# Создаем  control файл
file(WRITE ${CMAKE_CURRENT_BYNARY_DIR}/debian/control
    "Source: ${CPACK_PACKAGE_NAME}
    Maintainer:  Andrey <koshurnikovaa@.ru>,  Ivan <i.m.petrishchev@.ru>
    Section: misc
    Priority: optional
    Standards-Version: 3.9.3
    Build-Depends: debhelper (>= 9)

    Package: ${CPACK_PACKAGE_NAME}
    Architecture: ${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}
    Depends: \${shlibs:Depends}, \${misc:Depends}, \libqt5sql5-psql, \${CPACK_DEBIAN_PACKAGE_DEPENDS}
    Description: ${CPACK_PACKAGE_DESCRIPTION_SUMMARY}
    ")
# Создаем rules файл
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/rules
"#!/user/bin/make -f

%:

    dh \$@
")
# Создаем source/format файла
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/source/format "3.0 (quilt)\n")

# Создаем isaos.install файл
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/${CPACK_PACKAGE_NAME}.install
"bin/* usr/local/niissu/isaos/bin
csqldatabase/share/sql/* usr/local/niissu/isaos/sql
csettings/share/conf.d/* usr/local/niissu/isaos/etc
share/desktop/* usr/share/applications
share/desktop/* etc/xdg/autostart
share/service/* lib/systemd/system
gui-systemtray/share/image/tray.png usr/local/niissu/isaos/icons")

# Создаем isaos.dirs файл
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/debian/${CPACK_PACKAGE_NAME}.dirs
"usr/local/niissu/isaos/bin
usr/local/niissu/isaos/etc
usr/local/niissu/isaos/sql
usr/local/niissu/isaos/icons")




