import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import DataEntry
import UIComponents

ApplicationWindow {
    title: qsTr("Praca dyplomowa")
    visible: true
    //visibility: Window.Maximized
    width: 640
    height: 480
    // minimumWidth: 860
    // minimumHeight: 600

    menuBar: CustomMenuBar {
        id: bar
    }

    header: CustomHeaderLayout {
        id: headerId
        currentIndex: bar.currentIndex
    }

    // footer: TabBar {}

    PlanStackLayout {
        currentIndex: headerId.activePage
    }

}
