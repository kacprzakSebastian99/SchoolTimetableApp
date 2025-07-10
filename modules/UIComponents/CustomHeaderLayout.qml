import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import UIComponents

StackLayout {
    width: parent.width
    currentIndex: 0
    property int activePage: 0

    TabBar {
        implicitWidth: parent.width
        implicitHeight: 30
        // background: Rectangle {
        //     color: "#7742BF"
        // }

        Repeater {
            anchors.fill: parent
            model: [{"title": "Plany zajęć", "viewID": 0}]//,
                    //{"title": "Wyczyść liste", "viewID": 0}]//,

            delegate: TabButton {
                required property string title
                required property int viewID
                font.pixelSize: 16
                font.bold: true
                width: 150
                height: 30
                // background: Rectangle {
                //     color: "lightgreen"   // Kolor tła
                //     radius: 10        // Zaokrąglenie rogów
                //     border.color: "white"
                //     border.width: 2
                // }
                text: title
                onClicked: {
                    activePage = viewID
                    console.log("Clicked:", text, "CI:", activePage)
                }
            }
        }
    }

    TabBar {
        implicitWidth: parent.width
        implicitHeight: 30
        // background: Rectangle {
        //     color: "#123456"
        // }

        Repeater {
            anchors.fill: parent
            model: [{"title": "Przedmiot", "viewID": 1},
                    {"title": "Profil", "viewID": 2},
                    {"title": "Sala", "viewID": 3},
                    {"title": "Nauczyciel", "viewID": 4},
                    {"title": "Klasa", "viewID": 5}]

            delegate: TabButton {
                required property string title
                required property int viewID
                font.pixelSize: 16
                font.bold: true
                width: 150
                height: 35
                text: title
                onClicked: {
                    activePage = viewID
                    console.log("Clicked:", text, "CI:", activePage)
                }
            }
        }
    }


    TabBar {
        implicitWidth: parent.width
        implicitHeight: 30
        // background: Rectangle {
        //     color: "#38D6E4"
        // }

        Repeater {
            anchors.fill: parent
            model: [{"title": "Klasy", "viewID": 6},
                    {"title": "Nauczyciela", "viewID": 6},
                    {"title": "Sali", "viewID": 6}]//,
                    // {"title": "Wiele okien", "viewID": 6},
                    // {"title": "Siatka", "viewID": 6}]

            delegate: TabButton {
                required property string title
                required property int viewID
                font.pixelSize: 16
                font.bold: true
                width: 150
                height: 35
                text: title
                onClicked: {
                    activePage = viewID
                    console.log("Clicked:", text, "CI:", activePage)
                }
            }
        }
    }

}

