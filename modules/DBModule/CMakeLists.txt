project(DBModule VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Core Sql Qml)

qt_add_qml_module(${PROJECT_NAME}lib
    STATIC
    URI DBModule
    SOURCES
        src/databasemanager.h
        src/databasemanager.cpp
        src/containers.h
        src/containers.cpp
        src/functiontemplates.h
        src/functiontemplates.cpp
)

target_include_directories(${PROJECT_NAME}lib PRIVATE
    src
    #${CMAKE_CURRENT_SOURCE_DIR}/../Timetable/src
)

target_link_libraries(${PROJECT_NAME}lib
    PRIVATE Qt6::Quick Qt6::Core Qt6::Sql Qt6::Qml
)
