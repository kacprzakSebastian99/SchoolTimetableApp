import QtQuick
import QtQuick.Controls

Rectangle {
    id: addButton
    property alias text:  buttonText.text

    signal clicked()

    implicitWidth: 200
    implicitHeight: 50
    border.color: "black"
    border.width: 1
    radius: 5
    Text {
        id: buttonText
        text: "Dodaj text"
        font.pixelSize: 16
        anchors.centerIn: parent
        // horizontalAlignment: Text.AlignHCenter
        // verticalAlignment: Text.AlignVCenter
    }
    MouseArea {
        anchors.fill: parent
        onClicked: addButton.clicked()
    }
}
