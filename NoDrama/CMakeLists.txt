cmake_minimum_required(VERSION 3.16)

project(NoDrama VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

#qt_add_resources(appNoDrama "images"
#    PREFIX "/"
#    FILES
#        images/NoDramaTranparent.PNG
#)

qt_add_executable(appNoDrama
    resources.qrc
    main.cpp
    createaccount.cpp
    infopage.h infopage.cpp
)

qt_add_qml_module(appNoDrama
    URI NoDrama
    VERSION 1.0
    QML_FILES main.qml 
    QML_FILES createAccount.qml
    QML_FILES infoPage.qml
)

set_target_properties(appNoDrama PROPERTIES
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
