import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule

Window {
    id: addWindowProfile
    title: qsTr("Profil")
    visible: false
    // visibility: Window.Hidden
    minimumWidth: 860
    minimumHeight: 600

    Containers { id: instance }

    function loadSubjects() {
        allSubjects.model.clear();
        for (var i = 0; i < instance.subjects.length; i++) {
            allSubjects.model.append({"id": instance.subjects[i].id, "name": instance.subjects[i].name, "shortcut": instance.subjects[i].shortcut, "type": instance.subjects[i].type});
        }
        console.log("Załadowano " + instance.subjects.length + " przedmiotów");
    }

    onVisibleChanged: {
        if(visible)
        {
            loadSubjects();
        }
    }

    signal profileRefresh()

    PopupFillAll { id: fillAll }

    Column {
        RowLayout {
            spacing: 5

            Column {
                spacing: 5
                Label {
                    text: "Nazwa profilu: "
                    font.pixelSize: 16
                }
                // Label {
                //     text: "Poziom klasy: "
                //     font.pixelSize: 16
                // }
                Label {
                    text: "Przypisz przedmioty do profilu: "
                    font.pixelSize: 16
                }
            }
            Column {
                spacing: 5
                TextField {
                    id: di1
                    placeholderText: "np. Klasa 4 Ogólny"
                    font.pixelSize: 16
                    focus: true
                }
                // TextField {
                //     id: di2
                //     placeholderText: "np. 4"
                //     font.pixelSize: 16
                // }
            }
        }

        Row {
            padding: 10
            spacing: 10
            Rectangle {
                width: 200
                height: 300
                radius: 10
                border.color: "black"
                border.width: 2

                ListView {
                    id: allSubjects
                    width: parent.width
                    height: parent.height//300
                    model: ListModel {}

                    delegate: Item {
                        width: 200
                        height: 25

                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.width - 10
                            height: 20
                            border.color: "black"
                            Text {
                                anchors.centerIn: parent
                                text: model.name
                            }
                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    // Dodaj do drugiej listy
                                    profileSubjects.model.append({id: model.id, name: model.name, shortcut: model.shortcut, type: model.type, hours: 0, block: 0, availability: "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]"});
                                    allSubjects.model.remove(index)
                                }
                            }
                        }
                    }
                }
            }
            Rectangle {
                width: 550
                height: 300
                radius: 10
                border.color: "black"
                border.width: 2

                ListView {
                    id: profileSubjects
                    width: parent.width
                    height: parent.height//300
                    model: ListModel {}

                    delegate: Item {
                        width: 550
                        height: 30

                        DialogAvailability {
                            id: da
                        }

                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.width - 10
                            height: 25
                            border.color: "black"

                            RowLayout {
                                width: parent.width
                                Text {
                                    //width: 150
                                    text: model.name
                                    Layout.fillWidth: true
                                }
                                TextField {
                                    id: di3
                                    //width: 50
                                    implicitHeight: 20
                                    placeholderText: "Liczba godzin"
                                    font.pixelSize: 10
                                    Layout.fillWidth: true
                                    onTextChanged: {
                                        model.hours = Number(text)
                                    }
                                }
                                TextField {
                                    id: di4
                                    //width: 50
                                    implicitHeight: 20
                                    placeholderText: "Godziny w bloku"
                                    font.pixelSize: 10
                                    Layout.fillWidth: true
                                    onTextChanged: {
                                        model.block = Number(text)
                                    }
                                }
                                Button {
                                    text: "Dostępność"
                                    Layout.fillWidth: true
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
                                            da.objectID = profileSubjects
                                            da.itemIndex = index
                                            // console.log("PI:" + da.itemIndex)
                                            da.open()
                                            console.log("SubjectID: " + model.id)
                                            console.log("Liczba godzin: " + model.hours)
                                            console.log("Godziny w bloku: " + model.block)
                                        }
                                    }
                                }
                                Button {
                                    //width: 190
                                    text: "X"
                                    Layout.fillWidth: true
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
                                            // Dodaj do drugiej listy
                                            allSubjects.model.append({id: model.id, name: model.name, shortcut: model.shortcut, type: model.type, hours: 0, block: 0, availability: "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]"});
                                            profileSubjects.model.remove(index)
                                        }
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }

        Row {
            Button {
                text: "Dodaj"
                onClicked: {
                    console.log("Dostepnosc: " + profileSubjects.model.get(0).availability)
                    if(di1.text !== "")// && di2.text !== "")
                    {
                        var list = [];
                        for (var i = 0; i < profileSubjects.model.count; i++) {
                            var subject = profileSubjects.model.get(i);
                            console.log("Subject from QML:", JSON.stringify(subject)); // Debug
                            list.push(JSON.parse(JSON.stringify(subject))); // Konwersja na czysty JSON
                        }
                        instance.addProfile(di1.text, list);
                        di1.text = ""
                        //di2.text = ""
                        profileSubjects.model.clear()
                        loadSubjects()
                        profileRefresh()
                    }
                    else
                    {
                        fillAll.open();
                    }
                }
            }
            Button {
                text: "Anuluj"
                onClicked: addWindowProfile.close()
            }
        }
    }

    onClosing: {
        di1.text = ""
        profileSubjects.model.clear()
    }
}
