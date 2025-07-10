import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule
import UIComponents

Item {

    AddWindowTeacher {
        id: addWindow
    }

    Containers {
        id: instance
    }

    Connections {
        target: addWindow
        function onTeachersRefresh() {
            console.log("TEACHERS REFRESH")
            instance.downloadTeachers()
        }
    }

    ColumnLayout {
        AddButton {
            text: "DODAJ NAUCZYCIELA"
            onClicked: {
                addWindow.show()
            }
        }

        Button {
            text: "Odśwież dane"
            onClicked: instance.downloadTeachers()
        }

        Rectangle {
            implicitWidth: 400
            implicitHeight: 400
            border.color: "black"
            border.width: 2
            Column {
                anchors.fill: parent
                spacing: 5
                Row {
                    spacing: 5
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Imię i nazwisko" } }
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Nauczane klasy" } }
                    // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Przedmioty" } }
                }
                Column {
                    spacing: 5
                    Repeater {
                        model: instance.teachers
                        delegate: Row {
                            spacing: 5
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.firstName + " " + model.lastName } }
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.taughtClasses.length > 0 ? model.taughtClasses[0].name : "BRAK"} }
                            // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.name } }
                        }
                    }
                }
            }
        }
    }
}
