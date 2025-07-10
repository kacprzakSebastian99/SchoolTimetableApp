import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DBModule
import Timetable

Window {
    id: addWindowTimetable
    title: qsTr("Plan zajęć")
    visible: false
    // visibility: Window.Hidden
    minimumWidth: 640
    minimumHeight: 480

    GeneticAlgorithm {
        id: ag
    }

    signal timetableRefresh()

    Column {
    RowLayout {
        spacing: 5

        Column {
            spacing: 5
            Label {
                text: "Nazwa planu zajęć: "
                font.pixelSize: 16
            }
        }
        Column {
            spacing: 5
            TextField {
                id: di1
                placeholderText: "np. Plan Lekcji 2025/2026"
                font.pixelSize: 16
                focus: true
            }
        }
    }
    Row {
        Button {
            text: "Dodaj"
            onClicked: {
                if(di1.text !== "")
                {
                    ag.geneticAlgorithmRun(di1.text);
                    di1.text = ""
                    timetableRefresh()
                    addWindowTimetable.close()
                }
                else
                {
                    fillAll.open();
                }
            }
        }
        Button {
            text: "Anuluj"
            onClicked: addWindowTimetable.close()
        }
    }

    }
    onClosing: {
        di1.text = ""
    }

    Dialog {
        id: fillAll
        anchors.centerIn: parent
        standardButtons: Dialog.Ok
        Text {
            text: "Wypełnij wszystkie pola!"
        }
    }
}
