#ifndef QTQUESTIONIMAGEPROVIDER_H
#define QTQUESTIONIMAGEPROVIDER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QImage>
#include <QQuickImageProvider>

class QtQuestionImageProvider : public QQuickImageProvider
{
public:
    QtQuestionImageProvider();
    ~QtQuestionImageProvider();
    bool loadImage(QString image_source, QString name);
    bool loadDirectory(QString directory);
    bool clearImages();
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize)
    {
        QImage image;
        if(m_Images.contains(id)){
            image = *m_Images.value(id);
        }
        return image;
    }

protected:
    QMap<QString,QImage*>  m_Images;
};

#endif // QTQUESTIONIMAGEPROVIDER_H
