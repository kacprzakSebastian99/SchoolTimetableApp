import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: fillAll
    anchors.centerIn: parent
    implicitWidth: 150
    implicitHeight: 50
    ColumnLayout {
        Text {
            text: "Wypełnij wszystkie pola!"
        }
        Button {
            text: "OK"
            onClicked: {
                fillAll.close()
            }
        }
    }
}
