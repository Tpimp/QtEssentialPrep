#ifndef QTTESTMANAGER_H
#define QTTESTMANAGER_H

#include <QObject>
#include <QStringList>
#include <QList>
#include <QJsonObject>
class QtTestTypeLoader;
class QtTestWidget;
class QtTestManager : public QObject
{
    Q_OBJECT
public:
    explicit QtTestManager(QtTestTypeLoader & loader, QtTestWidget& delegate, QObject *parent = 0);
    Q_INVOKABLE void startNewTest(QStringList list);
signals:
    void readyToStart();
    void currentChanged(qreal current);
public slots:
    void submitAnswer(int answer);

protected:
    QtTestTypeLoader& m_Loader;
    QtTestWidget&     m_Delegate;
    QList<QJsonObject> m_Questions;
    qreal m_CurrentQuestion;
    void   randomizeQuestions();
    void   setNextQuestion();
    static QJsonObject generateRandomizedQuestionOrder(QJsonObject & question);
};

#endif // QTTESTMANAGER_H
