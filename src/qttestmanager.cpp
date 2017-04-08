#include "qttestmanager.h"
#include <QJsonArray>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonValue>
#include "qttesttypeloader.h"
#include "qttestwidget.h"
#include <QDebug>
QtTestManager::QtTestManager(QtTestTypeLoader &loader,QtTestWidget & delegate, QObject *parent) :
    QObject(parent), m_Loader(loader), m_Delegate(delegate)
{}


void QtTestManager::startNewTest(QStringList list)
{
    if(list.isEmpty())
        return;
    // clear existing list queue
    m_Questions.clear();
    foreach(QString type, list){
        QJsonArray questions = m_Loader.getQuestionsByType(type);
        foreach(QJsonValue val, questions){
            if(val.isObject()){
                QJsonObject question = val.toObject();
                QJsonObject randomized = generateRandomizedQuestionOrder(question);
                m_Questions.append(randomized);
            }
        }
    }
    randomizeQuestions();
    m_CurrentQuestion = 0;
    setNextQuestion();
    emit readyToStart();

}

QJsonObject QtTestManager::generateRandomizedQuestionOrder(QJsonObject &question)
{
    QJsonObject ret_obj;
    if(question.contains("I")){ // if has an image
        ret_obj["I"] = question.value("I").toString();
    }
    ret_obj["Q"] = question.value("Q").toString();
    int correct = question.value("CA").toInt();
    int rand_order = (qrand() % 4);
    switch(correct){
    case 0:{
        switch(rand_order)
        {
            case 0: break;
            case 1:
                //swapped correct answer to position 1
                ret_obj["A2"] = question.value("A1").toString();
                ret_obj["A3"] = question.value("A4").toString();
                ret_obj["A1"] = question.value("A2").toString();
                ret_obj["A4"] = question.value("A3").toString();
                ret_obj["CA"] = 1;
                break;

            case 2:
                //swapped correct answer to position 2
                ret_obj["A3"] = question.value("A1").toString();
                ret_obj["A4"] = question.value("A4").toString();
                ret_obj["A2"] = question.value("A2").toString();
                ret_obj["A1"] = question.value("A3").toString();
                ret_obj["CA"] = 2;
                break;

            case 3:
                //swapped correct answer to position 3
                ret_obj["A4"] = question.value("A1").toString();
                ret_obj["A1"] = question.value("A4").toString();
                ret_obj["A3"] = question.value("A2").toString();
                ret_obj["A2"] = question.value("A3").toString();
                ret_obj["CA"] = 3;
                break;

            default:break; // leave it
        }
        break;
    }
    case 1:{
        switch(rand_order)
        {
            case 0:
                //swapped correct answer to position 0
                ret_obj["A1"] = question.value("A2").toString();
                ret_obj["A2"] = question.value("A4").toString();
                ret_obj["A3"] = question.value("A3").toString();
                ret_obj["A4"] = question.value("A1").toString();
                ret_obj["CA"] = 0;
                break;

            case 1:break; // leave it
            case 2:
                //swapped correct answer to position 2
                ret_obj["A2"] = question.value("A1").toString();
                ret_obj["A4"] = question.value("A4").toString();
                ret_obj["A3"] = question.value("A2").toString();
                ret_obj["A1"] = question.value("A3").toString();
                ret_obj["CA"] = 2;
                break;

            case 3:
                //swapped correct answer to position 3
                ret_obj["A2"] = question.value("A3").toString();
                ret_obj["A3"] = question.value("A1").toString();
                ret_obj["A1"] = question.value("A4").toString();
                ret_obj["A4"] = question.value("A2").toString();
                ret_obj["CA"] = 3;
                break;

            default:break; // leave it
        }
        break;
    }
    case 2:{
        switch(rand_order)
        {
            case 0:
                //swapped correct answer to position 0
                ret_obj["A1"] = question.value("A3").toString();
                ret_obj["A2"] = question.value("A2").toString();
                ret_obj["A3"] = question.value("A4").toString();
                ret_obj["A4"] = question.value("A1").toString();
                ret_obj["CA"] = 0;
                break;

            case 1:
                //swapped correct answer to position 1
                ret_obj["A2"] = question.value("A3").toString();
                ret_obj["A4"] = question.value("A4").toString();
                ret_obj["A3"] = question.value("A2").toString();
                ret_obj["A1"] = question.value("A1").toString();
                ret_obj["CA"] = 1;
                break;

            case 2:break; // leave it
            case 3:
                //swapped correct answer to position 3
                ret_obj["A2"] = question.value("A1").toString();
                ret_obj["A3"] = question.value("A2").toString();
                ret_obj["A1"] = question.value("A4").toString();
                ret_obj["A4"] = question.value("A3").toString();
                ret_obj["CA"] = 3;
                break;

            default:break; // leave it
        }
        break;
    }
    case 3:{
        switch(rand_order)
        {
            case 0:
                //swapped correct answer to position 0
                ret_obj["A1"] = question.value("A4").toString();
                ret_obj["A2"] = question.value("A2").toString();
                ret_obj["A3"] = question.value("A3").toString();
                ret_obj["A4"] = question.value("A1").toString();
                ret_obj["CA"] = 0;
                break;

            case 1:
                //swapped correct answer to position 1
                ret_obj["A4"] = question.value("A3").toString();
                ret_obj["A2"] = question.value("A4").toString();
                ret_obj["A3"] = question.value("A2").toString();
                ret_obj["A1"] = question.value("A1").toString();
                ret_obj["CA"] = 1;
                break;

            case 2:
                //swapped correct answer to position 3
                ret_obj["A2"] = question.value("A1").toString();
                ret_obj["A3"] = question.value("A4").toString();
                ret_obj["A1"] = question.value("A2").toString();
                ret_obj["A4"] = question.value("A3").toString();
                ret_obj["CA"] = 2;
                break;

            case 3:break; // leave it
            default:break; // leave it
        }
        break;
        }
        default:break;
    }
    return ret_obj;
}

void QtTestManager::randomizeQuestions()
{
    int times_to_randomize = m_Questions.count();
    for(int index(0); index < times_to_randomize; index++){
        int left = qrand() % (m_Questions.count()-1);
        int right = qrand() % (m_Questions.count()-1);
        m_Questions.move(left,right);
    }
}

void QtTestManager::setNextQuestion()
{
    QJsonObject current = m_Questions.at(m_CurrentQuestion++);
    QString question = current["Q"].toString();
    QString A1 = current["A1"].toString();
    QString A2 = current["A2"].toString();
    QString A3 = current["A3"].toString();
    QString A4 = current["A4"].toString();
    int CA = current["CA"].toInt();
    QString image;
    if(current.contains("I")){
        image = current["I"].toString();
        m_Delegate.setImage(image);
    }
    else{
        m_Delegate.setImage("");
    }
    m_Delegate.setQuestion(question);
    m_Delegate.setAnswer1(A1);
    m_Delegate.setAnswer2(A2);
    m_Delegate.setAnswer3(A3);
    m_Delegate.setAnswer4(A4);
    m_Delegate.setCorrectAnswer(CA);
}

void QtTestManager::submitAnswer(int answer)
{
    int ca = m_Delegate.correctAnswer();
    if(ca != answer){
        qDebug() << "Wrong Answer Question : " << m_Delegate.question();
        switch(ca){
            case 0:
                qDebug() << "Correct Answer : " << m_Delegate.answer1();
                break;
            case 1:
                qDebug() << "Correct Answer : " << m_Delegate.answer2();
                break;
            case 2:
                qDebug() << "Correct Answer : " << m_Delegate.answer3();
                break;
            case 3:
                qDebug() << "Correct Answer : " << m_Delegate.answer4();
                break;
            default:break;
        }
    }
    if(m_CurrentQuestion < m_Questions.count()){
        setNextQuestion();
    }
    else{
        // add up winner
    }
}

