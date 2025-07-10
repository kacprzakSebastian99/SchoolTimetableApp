import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule

Window {
    id: addWindowClassroom
    title: qsTr("Sala")
    visible: false
    // visibility: Window.Hidden
    minimumWidth: 860
    minimumHeight: 600

    Containers { id: instance }

    signal classroomsRefresh()

    PopupFillAll { id: fillAll }

    DialogAvailability { id: da }

    ListModel { id: classroomAvailability
        ListElement { availability: "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]" }
    }

    Column {
        RowLayout {
            spacing: 5

            Column {
                spacing: 5
                Label {
                    text: "Nazwa sali: "
                    font.pixelSize: 16
                }
                Label {
                    text: "Rodzaj sali: "
                    font.pixelSize: 16
                }
                Label {
                    text: "Dostępność: "
                    font.pixelSize: 16
                }
            }
            Column {
                spacing: 5
                TextField {
                    id: di1
                    placeholderText: "np. S207"
                    font.pixelSize: 16
                    focus: true
                }
                ComboBox {
                    id: di2
                    width: 250
                    currentIndex: -1
                    displayText: currentIndex === -1 ? "Wybierz typ" : model.get(currentIndex).text

                    model: ListModel {
                        id: model
                        ListElement { text: "Matematyczna/Fizyczna"; number: 1}
                        ListElement { text: "Biologiczna/Chemiczna"; number: 2}
                        ListElement { text: "Artystyczna"; number: 3}
                        ListElement { text: "Historyczna/Społeczna"; number: 4}
                        ListElement { text: "Techniczna/Zawodowa"; number: 5}
                        ListElement { text: "Sala Gimnastyczna/Boisko"; number: 6}
                        ListElement { text: "Ogólna"; number: 7}
                    }

                    delegate: ItemDelegate { text: model.text }
                }
                Button {
                    text: "Dostępność"
                    //Layout.fillWidth: true
                    onClicked: {
                        da.modelID = classroomAvailability
                        da.itemIndex = 0
                        da.open()
                    }
                }
            }
        }

        Row {
            Button {
                text: "Dodaj"
                onClicked: {
                    console.log("Dostepnosc: " + classroomAvailability.get(0).availability)
                    if(di1.text !== "" && di2.currentIndex !== -1)
                    {
                        var list = [];
                        for (var i = 0; i < classroomAvailability.count; i++) {
                            var availability = classroomAvailability.get(i);
                            console.log("Subject from QML:", JSON.stringify(availability)); // Debug
                            list.push(JSON.parse(JSON.stringify(availability))); // Konwersja na czysty JSON
                        }
                        instance.addClassroom(di1.text, di2.currentIndex, list);
                        di1.text = ""
                        di2.currentIndex = -1
                        classroomAvailability[0] = "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]"
                        classroomsRefresh()
                    }
                    else
                    {
                        fillAll.open();
                    }
                }
            }
            Button {
                text: "Anuluj"
                onClicked: addWindowClassroom.close()
            }
        }
    }

    onClosing: {
        di1.text = ""
        di2.currentIndex = -1
        classroomAvailability[0] = "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]"
    }
}
