#ifndef QTTESTTYPELOADER_H
#define QTTESTTYPELOADER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>

class QtTestTypeLoader : public QObject
{

    Q_OBJECT
public:
    explicit QtTestTypeLoader(QObject *parent = 0);

    Q_INVOKABLE void loadQuestionSet(QString pwd, QString question_path);
    void loadRootQuestionDirectory(QString question_dir);
    QJsonObject fetchQuestion(int question_number);

    int questionCount();
    QJsonObject getRandomQuestion();
    QJsonArray getQuestionsByType(QString type);
    QStringList getTypes();
    void clearTypes();
signals:
    void imageFound(QString path); // asks to items into the image provider
    void loadedType(int count, QString type);
    void clearedTypes();
public slots:


protected:
    QMap<QString,QJsonArray> m_QuestionDocuments;
    int                      m_QuestionCount;

};

#endif // QTTESTTYPELOADER_H
