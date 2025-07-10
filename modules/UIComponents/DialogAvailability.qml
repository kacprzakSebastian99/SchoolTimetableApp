import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: addAvailabilityArray
    anchors.centerIn: parent

    property var objectID: null
    property var itemIndex: null
    property var modelID: null

    ColumnLayout {
        Text {
            text: "Ustaw dostępne godziny:"
        }
        // Nagłówek - dni tygodnia (dopasowany do GridView)
        RowLayout {
            spacing: 2
            Item { width: 30 } // Puste miejsce na numery godzin
            Repeater {
                model: ["Pon", "Wt", "Śr", "Czw", "Pt"]
                Label {
                    text: modelData
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    Layout.preferredWidth: gridView.cellWidth
                }
            }
        }
        RowLayout {
            spacing: 5

            // Numery godzin + dostępność
            ColumnLayout {
                spacing: 1

                // Numery godzin (1-8)
                Repeater {
                    model: 8
                    Label {
                        text: index + 1
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        Layout.preferredHeight: gridView.cellHeight
                        Layout.preferredWidth: 30 // Dopasowanie szerokości
                    }
                }
            }


            Rectangle {
                // id: addAvailabilityArray
                width: 150
                height: 128

                ListModel { id: availabilityValues }

                // Automatyczne dodanie elementów do modelu
                Component.onCompleted: {
                    for (let i = 0; i < 40; i++) {
                        availabilityValues.append({ color: "green", value: 1 });
                    }
                }

                GridView {
                    id: gridView
                    anchors.fill: parent
                    cellWidth: parent.width * 0.2
                    cellHeight: parent.height * 0.125
                    model: availabilityValues

                    delegate: Rectangle {
                        width: gridView.cellWidth
                        height: gridView.cellHeight
                        color: model.color
                        border.color: "black"

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                let newColor = model.color === "green" ? "red" : "green";
                                let newValue = model.value === 1 ? 0 : 1;
                                availabilityValues.setProperty(index, "color", newColor);
                                availabilityValues.setProperty(index, "value", newValue);
                            }
                        }
                    }
                }
            }
        }
        Button {
            text: "OK"
            onClicked: saveAvailability()
        }
    }

    function saveAvailability() {
        var valuesArray = [];
        for (var i = 0; i < availabilityValues.count; i++) {
            valuesArray.push(availabilityValues.get(i).value);
        }
        var jsonAvailability = JSON.stringify(valuesArray);

        if (modelID !== null) {
            modelID.setProperty(itemIndex, "availability", jsonAvailability);
        }
        else if (itemIndex !== null) {
            objectID.model.setProperty(itemIndex, "availability", jsonAvailability);
        }
        // console.log("Zapisano dostępność:", jsonAvailability);
        //console.log("Dostepnosc: " +  objectID.model.get(itemIndex).availability)
        addAvailabilityArray.close();
    }
    function reset() {
        availabilityValues.clear();
        for (let i = 0; i < 40; i++) {
            availabilityValues.append({ color: "green", value: 1 });
        }
    }
}


