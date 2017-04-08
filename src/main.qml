import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: myWindow
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
    Connections{
        target:QuestionLoader
        onLoadedType:{
            selectPage.addTest(count,type);
        }
        onClearedTypes:{
            selectPage.clearList();
        }
    }
    Connections{
        target:TestManager
        onReadyToStart:{
            swipeView.currentIndex = 1;
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        TestSelectPage{
            id:selectPage
            height: myWindow.height
            width: myWindow.width
            start.onClicked:{
                // begin a new test
                var selected_items = selectPage.getSelected();
                TestManager.startNewTest(selected_items)
            }
        }

        QuestionPage {
           id:questionPage
           height: myWindow.height
           width: myWindow.width
           questionImage.source:"image://Images/test"
           button.onClicked: {
               if(answer1.checked){
                   answer1.checked = false;
                   TestManager.submitAnswer(0);
               }
               if(answer2.checked){
                   answer2.checked = false;
                   TestManager.submitAnswer(1);
               }
               if(answer3.checked){
                   answer3.checked = false;
                   TestManager.submitAnswer(2);
               }
               if(answer4.checked){
                   answer4.checked = false;
                   TestManager.submitAnswer(3);
               }
           }
        }
    }
    Component.onCompleted: {
        QuestionLoader.loadQuestionSet(PWD,"/questions/License/Qt-Tq-Licenses.json");
    }
}
