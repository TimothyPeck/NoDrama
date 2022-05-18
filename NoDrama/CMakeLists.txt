cmake_minimum_required(VERSION 3.5)

project(NoDrama VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql Quick)

#qt_add_resources(appNoDrama "images"
#    PREFIX "/"
#    FILES
#        images/NoDramaTranparent.PNG
#)

qt_add_executable(appNoDrama
    resources.qrc
    main.cpp
    createaccount.cpp
set(PROJECT_SOURCES
        resources.qrc
        main.cpp
        database.h
        User.h
        party.h
        database.cpp
        User.cpp
        party.cpp
        createaccount.cpp
        createaccount.h
        infopage.cpp
        infopage.h
)

qt_add_qml_module(appNoDrama
    URI NoDrama
    VERSION 1.0
    QML_FILES main.qml 
    QML_FILES createAccount.qml
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
#else()
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
#sendif()

set_target_properties(appNoDrama PROPERTIES
target_compile_definitions(NoDrama
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(NoDrama
  PRIVATE Qt5::Core Qt5::Quick Qt5::Sql)

set_target_properties(NoDrama PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appNoDrama
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appNoDrama
    PRIVATE Qt6::Quick)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(NoDrama)
    qt_finalize_executable(NoDrama)
endif()
