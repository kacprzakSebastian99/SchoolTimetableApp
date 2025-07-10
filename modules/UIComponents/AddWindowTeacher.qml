import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule

Window {
    id: addWindowTeacher
    title: qsTr("Nauczyciel")
    visible: false
    // visibility: Window.Hidden
    minimumWidth: 860
    minimumHeight: 600

    Containers { id: instance }

    function loadSubjectsClassrooms() {
        allSubjects.model.clear();
        for (var i = 0; i < instance.subjects.length; i++) {
            allSubjects.model.append({"id": instance.subjects[i].id, "name": instance.subjects[i].name});
        }
        console.log("Załadowano " + instance.subjects.length + " przedmiotów");
        allClassrooms.model.clear();
        for (var i = 0; i < instance.classrooms.length; i++) {
            allClassrooms.model.append({"id": instance.classrooms[i].id, "name": instance.classrooms[i].name});
        }
        console.log("Załadowano " + instance.classrooms.length + " sal");
    }

    onVisibleChanged: {
        if(visible)
        {
            loadSubjectsClassrooms();
        }
    }

    signal teachersRefresh()

    PopupFillAll { id: fillAll }

    DialogAvailability { id: da }

    ListModel { id: teacherAvailability
        ListElement { availability: "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]" }
    }

    Column {
        RowLayout {
            spacing: 5

            Column {
                spacing: 5
                Label {
                    text: "Imię: "
                    font.pixelSize: 16
                }
                Label {
                    text: "Nazwisko: "
                    font.pixelSize: 16
                }
                Label {
                    text: "Dostępność: "
                    font.pixelSize: 16
                }
                // Label {
                //     text: "Specjalizacja: "
                //     font.pixelSize: 16
                // }
                // Label {
                //     text: "Sale lekcyjne: "
                //     font.pixelSize: 16
                // }
            }
            Column {
                spacing: 5
                TextField {
                    id: di1
                    placeholderText: "np. Jan"
                    font.pixelSize: 16
                    focus: true
                }
                TextField {
                    id: di2
                    placeholderText: "np. Kowalski"
                    font.pixelSize: 16
                }
                Button {
                    text: "Dostępność"
                    //Layout.fillWidth: true
                    onClicked: {
                        da.modelID = teacherAvailability
                        da.itemIndex = 0
                        da.open()
                    }
                }
            }
        }

        Label {
            text: "Specjalizacja: "
            font.pixelSize: 16
        }

        Row {
            padding: 10
            spacing: 10
            Rectangle {
                width: 200
                height: 100
                radius: 10
                border.color: "black"
                border.width: 2

                ListView {
                    id: allSubjects
                    width: parent.width
                    height: 80//100
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
                                    specjalization.model.append({id: model.id, name: model.name});
                                    allSubjects.model.remove(index)
                                }
                            }
                        }
                    }
                }
            }
            Rectangle {
                width: 200
                height: 100
                radius: 10
                border.color: "black"
                border.width: 2

                ListView {
                    id: specjalization
                    width: parent.width
                    height: 80//100
                    model: ListModel {}

                    delegate: Item {
                        width: 200
                        height: 30

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
                                Button {
                                    //width: 190
                                    text: "X"
                                    Layout.fillWidth: true
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
                                            // Dodaj do drugiej listy
                                            allSubjects.model.append({id: model.id, name: model.name});
                                            specjalization.model.remove(index)
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        Label {
            text: "Sale lekcyjne: "
            font.pixelSize: 16
        }
        // sale lekcyjne
        Row {
            padding: 10
            spacing: 10

            Rectangle {
                width: 200
                height: 100
                radius: 10
                border.color: "black"
                border.width: 2

                ListView {
                    id: allClassrooms
                    width: parent.width
                    height: 80//100
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
                                    teacherClassrooms.model.append({id: model.id, name: model.name});
                                    allClassrooms.model.remove(index)
                                }
                            }
                        }
                    }
                }
            }
            Rectangle {
                width: 200
                height: 100
                radius: 10
                border.color: "black"
                border.width: 2

                ListView {
                    id: teacherClassrooms
                    width: parent.width
                    height: 80//100
                    model: ListModel {}

                    delegate: Item {
                        width: 200
                        height: 30

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
                                Button {
                                    //width: 190
                                    text: "X"
                                    Layout.fillWidth: true
                                    MouseArea {
                                        anchors.fill: parent
                                        onClicked: {
                                            // Dodaj do drugiej listy
                                            allClassrooms.model.append({id: model.id, name: model.name});
                                            teacherClassrooms.model.remove(index)
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
                    if(di1.text !== "" && di2.text !== "")
                    {
                        var specList = [];
                        for (var i = 0; i < specjalization.model.count; i++) {
                            var spec = specjalization.model.get(i);
                            allSubjects.model.append({id: specjalization.model.get(i).id, name: specjalization.model.get(i).name});
                            console.log("Spec from QML:", JSON.stringify(spec)); // Debug
                            specList.push(JSON.parse(JSON.stringify(spec))); // Konwersja na czysty JSON
                        }
                        var roomList = [];
                        for (var i = 0; i < teacherClassrooms.model.count; i++) {
                            var room = teacherClassrooms.model.get(i);
                            allClassrooms.model.append({id: teacherClassrooms.model.get(i).id, name: teacherClassrooms.model.get(i).name});
                            console.log("Spec from QML:", JSON.stringify(room)); // Debug
                            roomList.push(JSON.parse(JSON.stringify(room))); // Konwersja na czysty JSON
                        }
                        var availabilityList = [];
                        for (var i = 0; i < teacherAvailability.count; i++) {
                            var availability = teacherAvailability.get(i);
                            console.log("Subject from QML:", JSON.stringify(availability)); // Debug
                            availabilityList.push(JSON.parse(JSON.stringify(availability))); // Konwersja na czysty JSON
                        }
                        instance.addTeacher(di1.text, di2.text, specList, roomList, availabilityList);
                        di1.text = ""
                        di2.text = ""
                        specjalization.model.clear()
                        teacherClassrooms.model.clear()
                        teacherAvailability[0] = "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]"
                        da.reset()
                        loadSubjectsClassrooms()
                        teachersRefresh()
                    }
                    else
                    {
                        fillAll.open();
                    }
                }
            }
            Button {
                text: "Anuluj"
                onClicked: addWindowTeacher.close()
            }
        }
    }

    onClosing: {
        di1.text = ""
        di2.text = ""
        specjalization.model.clear()
        teacherClassrooms.model.clear()
        teacherAvailability[0] = "[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]"
    }
}
