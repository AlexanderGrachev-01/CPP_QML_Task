import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs 1.0

Rectangle {
    width: 500
    height: 40
    color: "#303036"
    border.color: "#050401"

    property string textPath: "Select a folder"

    Button {
        id: browseButton
        width: 64
        height: parent.height
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("browse")
        background: Rectangle {
            color: "#68686f"
            border.color: "#050401"
        }
        onClicked: fileDialog.open()
    }

    Label {
        id: folderLabel
        width: parent.width - browseButton.width
        color: "#80FFE8"
        clip: true
        text: qsTr(textPath)
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 10
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a folder"
        folder: shortcuts.home
        selectFolder: true
        onAccepted: {
            textPath = fileDialog.fileUrl.toString()
        }
        onRejected: {
            console.log("Canceled")
        }
    }
}
