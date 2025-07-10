import QtQuick
import QtQuick.Controls

TabBar {
    width: parent.width
    height: 30
    // background: Rectangle {
    //     color: "#37C219"
    // }

    Repeater {
        anchors.fill: parent
        model: [{"title": "Plan"},
                {"title": "Wprowadź"},
                {"title": "Widok"}]

        delegate: TabButton {
            required property string title
            font.pixelSize: 16
            font.bold: true
            width: 150
            height: 35
            text: title
            onClicked: console.log("Clicked:", text)
        }
    }
}
