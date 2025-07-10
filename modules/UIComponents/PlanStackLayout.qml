import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import Timetable
import UIComponents

StackLayout {
    width: parent.width
    //currentIndex: 0

    MainView { id: mv}

    SubjectView {}
    ProfileView {}
    ClassroomView {}
    TeacherView {}
    ClassGroupView {}

    TimetableView {
        ttID: mv.timetableID
    }
}
