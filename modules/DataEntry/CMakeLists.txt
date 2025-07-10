project(DataEntry VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Core Sql Qml)

qt_add_qml_module(${PROJECT_NAME}lib
    STATIC
    URI DataEntry
    QML_FILES
        SubjectView.qml
        ProfileView.qml
        ClassroomView.qml
        TeacherView.qml
        ClassGroupView.qml
    SOURCES
        src/subject.h
        src/subject.cpp
        src/profile.h
        src/profile.cpp
        src/classroom.h
        src/classroom.cpp
        src/teacher.h
        src/teacher.cpp
        src/classgroup.h
        src/classgroup.cpp
        src/subgroup.h
        src/subgroup.cpp
)

target_include_directories(${PROJECT_NAME}lib PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME}lib
    PRIVATE Qt6::Quick Qt6::Core Qt6::Sql Qt6::Qml
)
