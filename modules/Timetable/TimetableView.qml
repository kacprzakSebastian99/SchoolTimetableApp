import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs
import DataEntry
import DBModule
import Timetable
import UIComponents


Item {
    id: displayTimetable
    visible: false
    //anchors.centerIn: parent
    //anchors.fill: parent

    property int ttID: 0

    onVisibleChanged: {
        readClassGroups();
        cg.cgName = ""
        modelTimetableData.clear()
    }

    Containers {
        id: instance
    }

    GeneticAlgorithm { id: ga }

    ListModel { id: modelTimetableData }
    ListModel { id: modelClassGroupData }

    ListModel { id: modelHoursData
        ListElement { hour: "1\n08:00-08:45"}
        ListElement { hour: "2\n08:55-09:40"}
        ListElement { hour: "3\n09:50-10:35"}
        ListElement { hour: "4\n10:50-11:35"}
        ListElement { hour: "5\n11:45-12:30"}
        ListElement { hour: "6\n12:50-13:35"}
        ListElement { hour: "7\n13:45-14:30"}
        ListElement { hour: "8\n14:40-15:25"}
    }
    ListModel { id: modelDayData
        ListElement { day: "PON"}
        ListElement { day: "WT"}
        ListElement { day: "ŚR"}
        ListElement { day: "CZW"}
        ListElement { day: "PT"}
    }


    function readClassGroups(){
        modelClassGroupData.clear();
        for(var i = 0; i < instance.classGroups.length; i++){
            modelClassGroupData.append(instance.classGroups[i]);
            console.log(instance.classGroups[i].name);
        }
    }

    function readCSVtimetable(target, cid) {
        target.clear();
        console.log("TTID: " + ttID);
        if (instance.timetables.length === 0) {
            console.error("Brak danych w instance.timetables");
            return;
        }

        var timetableData = instance.timetables[ttID].getTimetableData();

        if (cid < 0 || cid >= timetableData.length) {
            console.error("Nieprawidłowy CID:", cid);
            return;
        }

        var timetableDisplay = timetableData[cid]; // Pobieramy konkretną klasę
        let splitDays = timetableDisplay.split("\n"); // Podział na dni tygodnia

        for (let i = 0; i < splitDays.length; i++) {
            let splitHours = splitDays[i].split(","); // Podział na godziny

            for (let j = 0; j < splitHours.length; j++) {
                let splitLesson = splitHours[j].split(":");
                if (splitLesson.length < 2) continue; // Pominięcie błędnych wpisów

                let subjectID = splitLesson[0];
                let splitLesson2 = splitLesson[1].split(";");

                if (splitLesson2.length < 2) continue; // Pominięcie błędnych wpisów

                let teacherID = splitLesson2[0];
                let splitLesson3 = splitLesson2[1].split("#");

                if (splitLesson3.length < 2) continue; // Pominięcie błędnych wpisów

                let classroomID = splitLesson3[0];
                let classGroupID = splitLesson3[1];

                target.append({ "subjectID": subjectID, "teacherID": teacherID, "classroomID": classroomID, "classGroupID": classGroupID });
            }
        }
    }


    ColumnLayout {

        Row {

        Rectangle {
            id: buttonCB
            width: 200; height: 50
            //anchors.bottom: timetableWrapper.top//classNameRectangle.top
            border.color: "black"
            border.width: 1
            radius: 5
            Item {
                id: cg
                property int cgID: 0
                property string cgName: ""
            }
            ComboBox {
                id: classGroupCB
                width: 190
                height: 40
                anchors.centerIn: parent
                displayText: currentIndex === -1 ? "Wybierz klase" : model.get(currentIndex).name
                font.pointSize: 14

                model: modelClassGroupData

                delegate: ItemDelegate {
                    width: 180; height: 40
                    text: model.name
                    onClicked: {
                        modelTimetableData.clear()
                        classGroupCB.currentIndex = index
                        cg.cgName = modelClassGroupData.count > 0 ? String(modelClassGroupData.get(index).name) : ""
                        cg.cgID = modelClassGroupData.count > 0 ? Number(modelClassGroupData.get(index).id) : 0
                        readCSVtimetable(modelTimetableData, index)
                    }
                }
            }
        }

        FileDialog {
                id: fileDialog
                title: "Wybierz lokalizację dla PDF"
                fileMode: FileDialog.SaveFile
                nameFilters: ["Pliki PDF (*.pdf)"]

                onAccepted: {
                    console.log("Zapis do:", fileDialog.selectedFile);
                    instance.saveToPDF(fileDialog.selectedFile, timetableWrapper)
                }
        }

        Rectangle {
            id: pfdSaveRectangle
            width: 200; height: 50
            //anchors.bottom: timetableWrapper.top
            //anchors.left: buttonCB.right
            border.color: "black"
            border.width: 1
            radius: 5

            Text {
                text: "Zapisz do PDF"
                font.pointSize: 20
                font.bold: true
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    fileDialog.open()
                    //console.log("DATA: " + ga.timetableData[0][0][0].subjectID);
                }
            }
        }

        }

        Rectangle {
            id: timetableWrapper
            width: 1080; height: 550
            //anchors.centerIn: parent
            border.color: "black"
            border.width: 1
            radius: 1

            Rectangle {
                id: classNameRectangle
                width: 120
                height: 50
                anchors.left: parent.left
                anchors.top: parent.top
                border.color: "black"
                border.width: 1
                radius: 1
                Text {
                    id: classGroupNameText
                    text: cg.cgName !== "" ? "KLASA " + cg.cgName : "KLASA "
                    font.pointSize: 15
                    font.bold: true
                }
            }

            Rectangle {
                id: hoursRectangle
                anchors.left: classNameRectangle.right
                anchors.top: timetableWrapper.top //timetableViewId.top
                width: 960
                Row {
                    Repeater {
                        model: modelHoursData
                        delegate: Rectangle {
                            width: 960 * 0.125
                            height: 50
                            border.color: "black"
                            border.width: 1
                            radius: 1
                            Text {
                                text: hour
                                font.pointSize: 12
                                font.bold: true
                                anchors.centerIn: parent
                            }
                        }
                    }
                }
            }

            Rectangle {
                id: daysRectangle
                anchors.top: classNameRectangle.bottom
                anchors.left: timetableWrapper.left//timetableViewId.left
                Column {
                    id: dayGrid
                    visible: true
                    width: 120; height: 500

                    Repeater {
                        model: modelDayData
                        delegate: Rectangle {
                            width: parent.width
                            height: 100
                            border.color: "black"
                            border.width: 1
                            radius: 1
                            Text {
                                text: day
                                font.pointSize: 20
                                font.bold: true
                                anchors.centerIn: parent
                            }
                        }
                    }
                }
            }

            Rectangle {
                id: gridWrapper
                anchors.right: classNameRectangle.right
                anchors.bottom: classNameRectangle.bottom
                GridView {
                    id: grid
                    visible: true
                    width: 8 * cellWidth; height: 5 * cellHeight
                    cellWidth: 120; cellHeight: 100

                    Component {
                        id: lessonDelegate
                        Rectangle {
                            id: wrapper
                            width: 120
                            height: 100
                            border.color: "black"
                            border.width: 1
                            radius: 1
                            //color: "darkgoldenrod"
                            Column {
                                spacing:  10
                                Row {
                                    Text {
                                        id: classroom
                                        text: classroomID
                                        font.pointSize: 10
                                    }
                                }
                                Row {
                                    Text {
                                        id: subject
                                        text: subjectID
                                        font.bold: true
                                        font.pointSize: 20
                                    }
                                }
                                Row {
                                    Text {
                                        id: teacher
                                        text: teacherID
                                        wrapMode: Text.Wrap
                                        font.pointSize: 10
                                    }
                                }
                            }
                        }
                    }
                    model: modelTimetableData
                    delegate: lessonDelegate
                }
            }
        }//end wrapper
    }
}

