#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qttestwidget.h"
#include "qtquestionimageprovider.h"
#include "qttesttypeloader.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "qttestmanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QtTestWidget question_delegate(&app);
    QtQuestionImageProvider *image_provider = new QtQuestionImageProvider();
    image_provider->loadImage(app.applicationDirPath() + "/tests/example.jpg", "test");
    QQmlApplicationEngine engine;
    /*QJsonObject object;
    object.insert("Type", "Licenses");
    QJsonArray questions;
    QJsonObject question_one;
    question_one.insert("Q","Which import statement in the above code snippet adds the ColumnLayout object to the QML Engine?");
    question_one.insert("I","/tests/example.jpg");
    question_one.insert("A1","import QtQuick 2.7");
    question_one.insert("A2","import QtQuick.Controls 2.1");
    question_one.insert("A3","import QtQuick.Layouts 1.1");
    question_one.insert("A4","None of the Above");
    question_one.insert("CA", 2);
    questions.append(question_one);
    object.insert("Questions",questions);
    QJsonDocument doc;
    doc.setObject(object);
    QFile temp("template.json");
    temp.open(QIODevice::WriteOnly);
    temp.write(doc.toJson());*/
    QtTestTypeLoader loader(&app);
    QtTestManager manager(loader,question_delegate,&app);
    engine.rootContext()->setContextProperty("QuestionLoader",&loader);
    //loader.loadQuestionSet(app.applicationDirPath(), "/tests/Qt-Tq-Licenses.json");
    engine.rootContext()->setContextProperty("TestManager",&manager);
    engine.rootContext()->setContextProperty("QuestionDelegate",&question_delegate);
    engine.rootContext()->setContextProperty("PWD",app.applicationDirPath() );
    engine.addImageProvider("Images",image_provider);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
