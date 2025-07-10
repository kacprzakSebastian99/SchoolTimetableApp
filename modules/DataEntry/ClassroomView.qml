import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule
import UIComponents

Item {

    AddWindowClassroom {
        id: addWindow
    }

    Containers {
        id: instance
    }

    Connections {
        target: addWindow
        function onClassroomsRefresh() {
            console.log("CLASSROOMS REFRESH")
            instance.downloadClassrooms()
        }
    }

    ColumnLayout {
        AddButton {
            text: "DODAJ SALĘ"
            onClicked: {
                addWindow.show()
            }
        }

        Button {
            text: "Odśwież dane"
            onClicked: instance.downloadClassrooms()
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
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Sala" } }
                    // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Poziom" } }
                    // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Przedmioty" } }
                }
                Column {
                    spacing: 5
                    Repeater {
                        model: instance.classrooms
                        delegate: Row {
                            spacing: 5
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.name } }
                            // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.classLevel } }
                            // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.name } }
                        }
                    }
                }
            }
        }
    }
}
