import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import DBModule

Window {
    id: addWindowClassGroup
    title: qsTr("Klasa")
    visible: false
    // visibility: Window.Hidden
    minimumWidth: 860
    minimumHeight: 600

    Containers { id: instance }

    // Connections {
    //     target: instance
    //     onTeachersChanged: {
    //         loadProfileTeachers();
    //     }
    // }

    signal classGroupsRefresh()

    onVisibleChanged: {
        if(visible)
        {
            loadProfilesTeachers();
        }
    }

    ListModel { id: chosenTeachers }

    ListModel { id: classGroupTeachers }

    PopupFillAll { id: fillAll }

    Column {
        RowLayout {
            spacing: 5

            Column {
                spacing: 5
                Label {
                    text: "Nazwa klasy: "
                    font.pixelSize: 16
                }
                // Label {
                //     text: "Stała godzina \nrozpoczęcia lekcji: "
                //     font.pixelSize: 16
                // }
                Label {
                    text: "Profil: "
                    font.pixelSize: 16
                }
                // Label {
                //     text: "Wychowawca: "
                //     font.pixelSize: 16
                // }
            }
            Column {
                spacing: 5
                TextField {
                    id: di1
                    placeholderText: "np. 7A"
                    font.pixelSize: 16
                    focus: true
                }
                // TextField {
                //     id: di2
                //     placeholderText: "np. 1"
                //     font.pixelSize: 16
                // }
                ComboBox {
                    id: di3
                    width: 250
                    currentIndex: -1
                    displayText: currentIndex === -1 ? "Wybierz profil" : model.get(currentIndex).name

                    model: ListModel {}
                    delegate: ItemDelegate { text: model.name }

                    onCurrentIndexChanged: {
                        allSubjects.model.clear();
                        chosenTeachers.clear();
                        for (var i = 0; i < instance.profiles[currentIndex].subjectsList.length; i++) {
                            allSubjects.model.append({"id": instance.profiles[currentIndex].subjectsList[i].id, "name": instance.profiles[currentIndex].subjectsList[i].name});
                            chosenTeachers.append({"id": 0});
                        }
                    }
                }
                // ComboBox {
                //     id: di4
                //     width: 250
                //     currentIndex: -1
                //     displayText: currentIndex === -1 ? "Wybierz wychowawcę" : model.get(currentIndex).firstName + " " + model.get(currentIndex).lastName

                //     model: ListModel {}
                //     delegate: ItemDelegate { text: model.firstName + " " + model.lastName }
                // }
            }
        }

        Row {
            padding: 10
            spacing: 10
            Rectangle {
                width: 400
                height: 300
                radius: 10
                border.color: "black"
                border.width: 2



                ListView {
                    id: allSubjects
                    width: parent.width
                    height: 280//300
                    model: ListModel {}

                    delegate: Item {
                        width: 400
                        height: 25

                        property var mIndex: model.index

                        Rectangle {
                            anchors.centerIn: parent
                            width: parent.width - 10
                            height: 20
                            border.color: "black"
                            RowLayout {
                                width: parent.width
                                Text {
                                    //anchors.centerIn: parent
                                    text: model.name //+ " " + model.index
                                    Layout.fillWidth: true
                                }
                                ComboBox {
                                    id: cb
                                    Layout.fillWidth: true
                                    currentIndex: -1
                                    displayText: currentIndex === -1 ? "Wybierz Nauczyciela" : model.get(currentIndex).firstName + " " + model.get(currentIndex).lastName

                                    model: ListModel {}
                                    delegate: ItemDelegate {
                                        text: model.firstName + " " + model.lastName
                                    }

                                    onCurrentIndexChanged: {
                                        console.log("Przypisywana wartość id:", model.get(currentIndex).id);
                                        console.log("Przypisywana currentIndex:", mIndex);
                                        chosenTeachers.setProperty(mIndex, "id", Number(model.get(currentIndex).id));
                                    }

                                    Component.onCompleted: {
                                        cb.model.clear();
                                        for (var j = 0; j < instance.teachers.length; j++) {
                                            for (var k = 0; k < instance.teachers[j].specjalization.length; k++) {
                                                //console.log("MODEL: " + allSubjects.model.get(mIndex).name)
                                                //console.log("SPEC: " + instance.teachers[j].specjalization[k].name)
                                                if (allSubjects.model.get(mIndex).name === instance.teachers[j].specjalization[k].name)
                                                {
                                                    cb.model.append({"id": instance.teachers[j].id, "firstName": instance.teachers[j].firstName, "lastName": instance.teachers[j].lastName});
                                                    classGroupTeachers.append({"id": instance.teachers[j].id});
                                                    //console.log("Dodano nauczyciela: " + instance.teachers[j].firstName + " " + instance.teachers[j].lastName);
                                                }
                                            }
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
                    if(di1.text !== "" && di2.text !== "" && di3.currentIndex !== -1 && di4.currentIndex !== -1)
                    {
                        console.log("chosenTeacherSIZE", chosenTeachers.count);
                        removeDuplicates(chosenTeachers);
                        console.log("chosenTeacherSIZE_UNIQUE", chosenTeachers.count);
                        var teacherList = [];
                        for (var i = 0; i < chosenTeachers.count; i++) {
                            var teacher = chosenTeachers.get(i);
                            console.log("Teacher from QML:", JSON.stringify(teacher)); // Debug
                            teacherList.push(JSON.parse(JSON.stringify(teacher))); // Konwersja na czysty JSON
                        }
                        instance.addClassGroup(di1.text, di2.text, di3.model.get(di3.currentIndex).id, di4.model.get(di4.currentIndex).id, teacherList);
                        di1.text = ""
                        di2.text = ""
                        di3.currentIndex = -1
                        di4.currentIndex = -1
                        classGroupTeachers.clear()
                        chosenTeachers.clear()
                        classGroupsRefresh()
                    }
                    else
                    {
                        fillAll.open();
                    }
                }
            }
            Button {
                text: "Anuluj"
                onClicked: addWindowClassGroup.close()
            }
        }
    }

    onClosing: {
        di1.text = ""
        di2.text = ""
        di3.currentIndex = -1
        di4.currentIndex = -1
        classGroupTeachers.clear()
    }

    function loadProfilesTeachers()
    {
        di3.model.clear();
        for (var i = 0; i < instance.profiles.length; i++) {
            di3.model.append({"id": instance.profiles[i].id, "name": instance.profiles[i].name});
        }
        console.log("Załadowano " + instance.profiles.length + " profili");
        di4.model.clear();
        for (var i = 0; i < instance.teachers.length; i++) {
            //var teacherSpecList = []
            // for (var i = 0; i < instance.teachers.specjalization.length; i++) {
            //     // dodac/sprawdzić czy może być wychowawca/czy naucza godzine wychowawcza
            // }
            di4.model.append({"id": instance.teachers[i].id, "firstName": instance.teachers[i].firstName, "lastName": instance.teachers[i].lastName});
        }
        console.log("Załadowano " + instance.teachers.length + " wychowawców");
    }

    function removeDuplicates(target) {
            var uniqueItems = [];
            for (var i = 0; i < target.count; ++i) {
                var item = target.get(i);
                // Sprawdzamy, czy dany element już istnieje w uniqueItems na podstawie `id`
                if (!uniqueItems.some(function(e) { return e.id === item.id; })) {
                    uniqueItems.push(item);
                }
            }

            // Czyszczenie modelu i dodawanie unikalnych elementów
            target.clear();
            for (var j = 0; j < uniqueItems.length; ++j) {
                target.append(uniqueItems[j]);
            }
        }


}
