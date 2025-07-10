import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule
import UIComponents

Item {

    AddWindowProfile {
        id: addWindow
    }

    Containers {
        id: instance
    }

    Connections {
        target: addWindow
        function onProfileRefresh() {
            console.log("PROFILE REFRESH")
            instance.downloadProfiles()
        }
    }

    ColumnLayout {
        AddButton {
            text: "DODAJ PROFIL"
            onClicked: {
                addWindow.show()
            }
        }

        Button {
            text: "Odśwież dane"
            onClicked: instance.downloadProfiles()
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
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Profil" } }
                    Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Poziom" } }
                    // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: "Przedmioty" } }
                }
                Column {
                    spacing: 5
                    Repeater {
                        model: instance.profiles
                        delegate: Row {
                            spacing: 5
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.name } }
                            Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.classLevel } }
                            // Rectangle { width: 100; height: 30; border.color: "black"; Text { anchors.centerIn: parent; text: model.name } }
                        }
                    }
                }
            }
        }
    }
}
