project(Timetable VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Core Sql Qml)

qt_add_qml_module(${PROJECT_NAME}lib
    STATIC
    URI Timetable
    QML_FILES
        MainView.qml
        TimetableView.qml
    SOURCES
        src/timetable.h
        src/timetable.cpp
        src/gene.h
        src/gene.cpp
        src/individual.h
        src/individual.cpp
        src/geneticalgorithm.h
        src/geneticalgorithm.cpp
        src/tempbruteforcealgo.h
        src/tempbruteforcealgo.cpp
)

target_include_directories(${PROJECT_NAME}lib PRIVATE
    src
    ${CMAKE_CURRENT_SOURCE_DIR}/../DBModule/src
    # ${CMAKE_CURRENT_SOURCE_DIR}/../DataEntry/src
)

target_link_libraries(${PROJECT_NAME}lib
    PRIVATE Qt6::Quick Qt6::Core Qt6::Sql Qt6::Qml
    # DBModulelibplugin
    # DataEntrylibplugin
    # UIComponentslibplugin
)
