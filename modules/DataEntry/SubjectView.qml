import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule
import UIComponents

Item {

    AddWindowSubject {
        id: addWindow
    }

    Containers {
        id: instance
    }

    Connections {
        target: addWindow
        function onSubjectsRefresh() {
            console.log("SUBJECTS REFRESH")
            instance.downloadSubjects()
        }
    }

    ColumnLayout {
        AddButton {
            text: "DODAJ PRZEDMIOT"
            onClicked: {
                addWindow.show()
            }
        }

        Button {
            text: "Odśwież dane"
            onClicked: instance.downloadSubjects()
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
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Przedmiot" } }
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Skrót" } }
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Typ" } }
                }
                Column {
                    spacing: 5
                    Repeater {
                        model: instance.subjects
                        delegate: Row {
                            spacing: 5
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.name } }
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.shortcut } }
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.type } }
                        }
                    }
                }
            }
        }
    }
}
