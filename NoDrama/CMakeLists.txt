cmake_minimum_required(VERSION 3.16)

project(NoDrama VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Sql Quick)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Sql Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql Quick)

set(PROJECT_SOURCES
        resources.qrc
        main.cpp
        createaccount.cpp
        createaccount.h
        infopage.cpp
        infopage.h
        User.h
        User.cpp
        party.h
        party.cpp
        database.cpp
        database.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(NoDrama
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET NoDrama APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(NoDrama SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(NoDrama
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(NoDrama
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(NoDrama
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql)

set_target_properties(NoDrama PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(NoDrama)
    qt_finalize_executable(NoDrama)
endif()

###############################################################################
##########           DOXYGEN
###############################################################################

find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
message(FATAL_ERROR "Doxygen is needed to build the documentation.")
endif()

cmake_path(GET ${CMAKE_CURRENT_SOURCE_DIR} PARENT_PATH PARENT_DIR)

set(doxyfile ${PARENT_DIR}/Doxyfile)

add_custom_target(BuildDoc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating Doxygen documentation"
    VERBATIM
)