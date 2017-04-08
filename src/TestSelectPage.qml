import QtQuick 2.7
import QtQuick.Controls 2.1
Item {
    property alias types: typeModel
    property real questionCount:0
    property alias start:start
    id: topItem
    ListModel{
        id: typeModel
        // type Model contains a name and a question count for each test type
    }
    function addTest(count, name){
        typeModel.append({"name":name,"count":count,  "selected":false});
    }
    function clearList(){
        typeModel.clear();
    }
    function getSelected(){
        var type_names = [];
        var type_count = typeModel.count;
        var current = 0;
        while(current < type_count){
            var item_at = typeModel.get(current);
            if(item_at.selected == true){
                type_names.push(item_at.name);
            }
            current++;
        }
        return type_names;

    }

    Rectangle{
        id:seclectionGrid
        border.width:4
        radius:4
        anchors.left: parent.left
        anchors.right:parent.right
        anchors.top:parent.top
        height:parent.height *.85
        color:"lightblue"
        Rectangle{
            anchors.top:parent.top
            anchors.margins: 4
            anchors.horizontalCenter: parent.horizontalCenter
            height:48
            width:parent.width/2.1
            color:"darkgrey"
            border.width: 2
            radius:4
            Text{
                anchors.fill: parent
                anchors.margins: 4
                font.pixelSize: 32
                color:"white"
                text:qsTr("Choose Question List")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        GridView{
            anchors.fill: parent

            model:types
            anchors.margins: 16
            delegate: Rectangle{
                color: selected ? "green" : "orange"
                height: topItem.height/3.5
                width: height
                border.width:2
                border.color: "white"
                Text{
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    text: name + "\n" + count
                    color:selected ? "white":"black"
                    font.pixelSize: 28
                }
                MouseArea{
                    anchors.fill: parent
                    onClicked:{
                        model.selected = !model.selected;
                        if(model.selected){
                            questionCount += model.count
                        }
                        else{
                            questionCount -= model.count
                        }
                    }
                }
            }
        }

    }
    Rectangle{
        border.width: 3
        radius:2
        color:"blue"
        height:topItem.height*.16
        anchors.left: parent.left
        anchors.right:parent.right
        anchors.bottom:parent.bottom
        Row{
            anchors.fill: parent
            anchors.margins:4
            Rectangle{
                border.width: 2
                color:"lightgrey"
                width: topItem.width/2.2
                anchors.top: parent.top
                anchors.bottom:parent.bottom
                anchors.margins: 8
                Text{
                    anchors.fill:parent
                    text:"Selected Question Count: " + questionCount
                    font.pixelSize: parent.height * .38
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    anchors.leftMargin: 6
                }
            }
            spacing: (topItem.width/5)
            Button {
                id: start
                width: topItem.width/4
                anchors.verticalCenter: parent.verticalCenter
                height:80
                text: qsTr("Start")
            }
        }
    }
}
