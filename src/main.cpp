#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "qttestwidget.h"
#include "qtquestionimageprovider.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QtTestWidget question_delegate;
    QtQuestionImageProvider *image_provider = new QtQuestionImageProvider();
    image_provider->loadImage(app.applicationDirPath() + "/tests/example.jpg", "test");
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("QuestionDelegate",&question_delegate);
    engine.addImageProvider("Images",image_provider);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
