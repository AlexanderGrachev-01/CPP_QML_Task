import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Dialogs 1.0

Window {
    width: 640
    height: 700
    visible: true
    color: "#1b1a1c"
    title: qsTr("File Comparison")

    ColumnLayout {
        id: routes
        anchors.top: parent.top
        anchors.topMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter

        FindFolderRectangle {
            id: firstPath
            textPath: "Select the first folder"
            onTextPathChanged: {
                console.log(textPath + " from qml")
                folderComparator.firstPath = textPath
                console.log(folderComparator.firstPath + " from c++")
            }
        }
        FindFolderRectangle {
            id: secondPath
            textPath: "Select the second folder"
            onTextPathChanged:  {
                console.log(textPath + " from qml")
                folderComparator.secondPath = textPath
                console.log(folderComparator.secondPath + " from c++")
            }
        }

    }

    Label {
        anchors.bottom: routes.top
        anchors.bottomMargin: 2
        anchors.left: routes.left
        anchors.leftMargin: 3
        text: qsTr("Path")
        color: "#80FFE8"
    }

    Rectangle {
        id: resultList
        width: 500
        height: 400
        anchors.top: routes.bottom
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#303036"
        border.color: "#050401"

        Label {
            id: resText
            width: parent.width - 20
            height: parent.height - 20
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            color: "#80FFE8"
            clip: true
            text: qsTr("No results")
        }
    }

    Label {
        anchors.bottom: resultList.top
        anchors.bottomMargin: 2
        anchors.left: resultList.left
        anchors.leftMargin: 3
        text: qsTr("Result")
        color: "#80FFE8"
    }

    Button {
        id: findEqualButton
        width: 100
        height: 36
        anchors.top: resultList.bottom
        anchors.topMargin: 20
        anchors.left: resultList.left
        text: qsTr("Find equal")
        background: Rectangle {
            color: "#FCDC4D"
            border.color: "#050401"
        }
        onClicked: {
            folderComparator.findEqualFiles()
            console.log(folderComparator.matchingResult)
            resText.text = folderComparator.matchingResult
        }
    }
}
