import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule

Window {
    id: addWindowSubject
    title: qsTr("Przedmiot")
    visible: false
    // visibility: Window.Hidden
    minimumWidth: 640
    minimumHeight: 480

    Containers {
        id: instance
    }

    signal subjectsRefresh()

    Column {
    RowLayout {
        spacing: 5

        Column {
            spacing: 5
            Label {
                text: "Nazwa przedmiotu: "
                font.pixelSize: 16
            }
            Label {
                text: "Skrót: "
                font.pixelSize: 16
            }
            Label {
                text: "Typ: "
                font.pixelSize: 16
            }
        }
        Column {
            spacing: 5
            TextField {
                id: di1
                placeholderText: "np. Matematyka"
                font.pixelSize: 16
                focus: true
            }
            TextField {
                id: di2
                placeholderText: "np. MAT"
                font.pixelSize: 16
            }
            ComboBox {
                id: di3
                width: 250
                currentIndex: -1
                displayText: currentIndex === -1 ? "Wybierz typ" : model.get(currentIndex).text

                model: ListModel {
                    id: model
                    ListElement { text: "Ścisły"; number: 1}
                    ListElement { text: "Humanistyczny"; number: 2}
                    ListElement { text: "Artystyczny"; number: 3}
                    ListElement { text: "Społeczny"; number: 4}
                    ListElement { text: "Techniczny/Zawodowy"; number: 5}
                    ListElement { text: "Wychowawczy/Fizyczny"; number: 6}
                    ListElement { text: "Niezdefiniowany"; number: 7}
                }

                delegate: ItemDelegate { text: model.text }
            }

        }

    }
    Row {
        Button {
            text: "Dodaj"
            onClicked: {
                if(di1.text !== "" && di2.text !== "" && di3.currentIndex !== -1)
                {
                    instance.addSubject(di1.text, di2.text, di3.model.get(di3.currentIndex).number);
                    di1.text = ""
                    di2.text = ""
                    di3.currentIndex = -1
                    subjectsRefresh()
                }
                else
                {
                    fillAll.open();
                }
            }
        }
        Button {
            text: "Anuluj"
            onClicked: addWindowSubject.close()
        }
    }

    }
    onClosing: {
        di1.text = ""
        di2.text = ""
        di3.currentIndex = -1
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
