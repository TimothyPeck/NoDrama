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

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    set(icon_res "${CMAKE_CURRENT_SOURCE_DIR}/images/res.rc")
endif()

set(PROJECT_SOURCES
        resources.qrc
        main.cpp
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
        ${icon_res}
    )
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
##########          Deployment
###############################################################################
if(WIN32)
    set(COMPONENT_NAME_MAIN "NoDrama")
    set(COMPONENT_NAME_DEPENDENCIES "RuntimeLibs")

    include(GNUInstallDirs)
    install(TARGETS NoDrama DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${COMPONENT_NAME_MAIN})

    set(CMAKE_INSTALL_RUNTIME_COMPONENT ${COMPONENT_NAME_DEPENDENCIES})
    include(InstallRequiredSystemLibraries)

    set(CPACK_GENERATOR "IFW")

    set(CPACK_VERSION_MAJOR "1")
    set(CPACK_VERSION_MINOR "0")

    set(CPACK_IFW_PACKAGE_NAME "NoDrama")
    set(CPACK_IFW_PACKAGE_TITLE "NoDrama Installer")
    set(CPACK_IFW_PACKAGE_PUBLISHER "He-Arc - NoDrama")
    set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Aero")

    find_program(WINDEPLOYQT windeployqt HINTS "${_qt_bin_dir}")
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake.in" "${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake" @ONLY)

    set(CPACK_PRE_BUILD_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/deploy-qt-windows.cmake)

    include(CPack)
    include(CPackIFW)

    CPACK_ADD_COMPONENT(${COMPONENT_NAME_MAIN})

    cpack_ifw_configure_component(${COMPONENT_NAME_MAIN} ESSENTIAL FORCED_INSTALLATION)

    message("Made installer")
endif()

###############################################################################
##########           GOOGLE
###############################################################################

set(CMAKE_CXX_STANDARD 17)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TESTS_SOURCES
    tests.cpp
)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core Sql Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql Quick)

message("Testing project")

add_executable(tests ${TESTS_SOURCES})
#add_executable(tests tests.cpp ${LibA_TESTS} ${LibB_TESTS} #${LibC_TESTS})
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(tests gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
enable_testing()



###############################################################################
##########           DOXYGEN
###############################################################################

find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
endif()

get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.. ABSOLUTE)

set(doxyfile ${PARENT_DIR}/Doxyfile)

add_custom_target(BuildDoc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating Doxygen documentation"
    VERBATIM
)
