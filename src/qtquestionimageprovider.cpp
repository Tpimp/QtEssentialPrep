#include "qtquestionimageprovider.h"
#include <QFile>

QtQuestionImageProvider::QtQuestionImageProvider() :QQuickImageProvider(QQuickImageProvider::Image)
{}

bool QtQuestionImageProvider::clearImages()
{
    foreach(QImage* image, m_Images){
        delete image;
    }
    m_Images.clear();

}

bool QtQuestionImageProvider::loadDirectory(QString directory)
{

}

bool QtQuestionImageProvider::loadImage(QString image_source, QString name)
{
    QFile file(image_source);
    if(file.exists()){
        QImage* image = new QImage(image_source);
        m_Images.insert(name,image);
    }
}



QtQuestionImageProvider::~QtQuestionImageProvider()
{
    if(!m_Images.isEmpty())
        clearImages();
}
