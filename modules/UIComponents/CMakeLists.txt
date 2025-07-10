project(UIComponents VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Core Sql Qml)

qt_add_qml_module(${PROJECT_NAME}lib
    STATIC
    URI UIComponents
    QML_FILES
        CustomMenuBar.qml
        CustomHeaderLayout.qml
        PlanStackLayout.qml
        AddButton.qml
        AddWindowSubject.qml
        AddWindowProfile.qml
        AddWindowClassroom.qml
        AddWindowTeacher.qml
        AddWindowClassGroup.qml
        DialogAvailability.qml
        PopupFillAll.qml
        AddWindowTimetable.qml
)

target_include_directories(${PROJECT_NAME}lib PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME}lib
    PRIVATE Qt6::Quick Qt6::Core Qt6::Sql Qt6::Qml
)
