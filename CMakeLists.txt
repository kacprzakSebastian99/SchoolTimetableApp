cmake_minimum_required(VERSION 3.16)

project(PDv2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.9 REQUIRED COMPONENTS Core Quick Sql Qml)

qt_standard_project_setup(REQUIRES 6.9)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

qt_add_executable(appPDv2
    main.cpp
)

add_subdirectory(modules/DBModule)
add_subdirectory(modules/DataEntry)
add_subdirectory(modules/Timetable)
add_subdirectory(modules/UIComponents)

qt_add_qml_module(appPDv2
    URI PDv2
    VERSION 1.0
    QML_FILES
        Main.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appPDv2 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appPDv2
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

find_package(OpenMP REQUIRED)

if(OpenMP_CXX_FOUND)
    target_link_libraries(appPDv2 PUBLIC OpenMP::OpenMP_CXX)
endif()

target_link_libraries(appPDv2
    PRIVATE
        Qt6::Quick
        Qt6::Core
        Qt6::Sql
        Qt6::Qml
    DBModulelibplugin
    DataEntrylibplugin
    Timetablelibplugin
    UIComponentslibplugin
)

target_include_directories(appPDv2 PRIVATE
    ${CMAKE_SOURCE_DIR}/modules/DBModule/src
    ${CMAKE_SOURCE_DIR}/modules/DataEntry/src
    ${CMAKE_SOURCE_DIR}/modules/Timetable/src
    ${CMAKE_SOURCE_DIR}/modules/UIComponents/src
)


# target_include_directories(appPDv2 PRIVATE ${CMAKE_SOURCE_DIR}/modules/DataEntry/src)


include(GNUInstallDirs)
install(TARGETS appPDv2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
