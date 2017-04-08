import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

Item {
    id: item1
    width: 1280
    height: 720
    property alias button: button
    property alias answer1:answerDelegate
    property alias answer2:answerDelegate2
    property alias answer3:answerDelegate3
    property alias answer4:answerDelegate4
    property alias questionImage:questionImage
    property alias question:questionText
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
    }

    Rectangle {
        color:"lightblue"
        id: questionItem
        y: 4
        height: parent.height * .5
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8
        Image{
            id: questionImage
            anchors.left: parent.left
            anchors.right:parent.right
            anchors.top:parent.top
            height:parent.height*.7
            anchors.margins: 4
            source:""
            fillMode: Image.PreserveAspectFit
        }
        Text{
            id: questionText
            anchors.left: parent.left
            anchors.right:parent.right
            anchors.top:questionImage.bottom
            anchors.bottom:parent.bottom
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignTop
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            font.pixelSize: 28
            anchors.margins:8
            text:"Which import statement in the above code snippet adds the ColumnLayout object to the QML Engine?"

        }

    }

    Column {
        id: column
        anchors.top: questionItem.bottom
        anchors.topMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 161
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.left: parent.left
        anchors.leftMargin: 8

        spacing: 20

        RadioDelegate {
            id: answerDelegate
            text: "import QtQuick 2.7"
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.columnSpan: 3
            Layout.rowSpan: 3
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RadioDelegate {
            id: answerDelegate2
            text: "import QtQuick.Controls 2.1"
            Layout.rowSpan: 3
            Layout.columnSpan: 3
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RadioDelegate {
            id: answerDelegate3
            text: "import QtQuick.Layouts 1.1"
            Layout.rowSpan: 3
            Layout.columnSpan: 3
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RadioDelegate {
            id: answerDelegate4
            text: "None of the Above"
            Layout.rowSpan: 3
            Layout.columnSpan: 3
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    Button {
        id: button
        x: 930
        width: 328
        text: qsTr("Submit")
        anchors.right: parent.right
        anchors.rightMargin: 22
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 33
        anchors.top: column.bottom
        anchors.topMargin: 42
    }
}


