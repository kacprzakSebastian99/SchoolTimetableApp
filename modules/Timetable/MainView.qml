import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule
import Timetable
import UIComponents

Item {

    AddWindowTimetable {
        id: addWindow
    }

    Containers {
        id: instance
    }

    property int timetableID: 0

    Connections {
        target: addWindow
        function onTimetableRefresh() {
            console.log("TIMETABLES REFRESH")
            instance.downloadTimetableData()
        }
    }

    Row {
        anchors.margins: 20
        anchors.left: parent.left

    ColumnLayout {
        AddButton {
            text: "GENERUJ PLAN"
            onClicked: {
                addWindow.show()
            }
        }

        Rectangle {
            implicitWidth: 400
            implicitHeight: 300
            border.color: "black"
            border.width: 2
            Column {
                anchors.fill: parent
                spacing: 5
                Row {
                    spacing: 5
                    Rectangle { width: 200; height: 30; border.color: "black";
                        Text { anchors.centerIn: parent; text: "Nazwa planu" } }
                }
                Column {
                    spacing: 5
                    Repeater {
                        model: instance.timetables
                        delegate: Row {
                            spacing: 5
                            Rectangle {
                                width: 400; height: 30; border.color: "black";
                                RowLayout {
                                       anchors.fill: parent
                                       spacing: 10

                                       Text {
                                           text: model.name
                                           Layout.alignment: Qt.AlignLeft
                                       }

                                       Item { Layout.fillWidth: true } // Rozciągający się pusty element, który popycha button na prawo

                                       Button {
                                           text: "Usuń"
                                           Layout.alignment: Qt.AlignRight
                                           onClicked: {
                                               instance.deleteTimetableData(model.id);
                                               instance.downloadTimetableData();
                                           }
                                       }
                                       Button {
                                           text: "Wczytaj"
                                           Layout.alignment: Qt.AlignCenter
                                           onClicked: {
                                                //activeTimetable = index;
                                               timetableID = index
                                               console.log("Index: " + index);
                                           }
                                       }
                                   }
                                // Text { anchors.centerIn: parent; text: model.name }
                                // Button { text: "Usuń"; onClicked: { instance.deleteTimetableData(model.id); instance.downloadTimetableData(); } }
                            }
                        }
                    }
                }
            }
        }
    }


    }

}
