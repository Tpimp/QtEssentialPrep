import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 720

    title: qsTr("Qt Essential Prep")
    Connections{
        target:QuestionDelegate
        onAnswer1Changed:{
            questionPage.answer1.text = answer1;
        }
        onAnswer2Changed:{
            questionPage.answer2.text = answer2;
        }
        onAnswer3Changed:{
            questionPage.answer3.text = answer3;
        }
        onAnswer4Changed:{
            questionPage.answer4.text = answer4;
        }
        onQuestionChanged:{
            questionPage.question.text = question;
        }
    }
    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        QuestionPage {
           id:questionPage
           questionImage.source:"image://Images/test"
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
