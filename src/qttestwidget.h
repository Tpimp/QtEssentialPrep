#ifndef QTTESTWIDGET_H
#define QTTESTWIDGET_H

#include <QObject>
class QtTestWidget : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_Question READ question WRITE setQuestion NOTIFY questionChanged MEMBER true)
    Q_PROPERTY(QString m_ImageSource READ imageSource WRITE setImage NOTIFY imageChanged MEMBER true)
    Q_PROPERTY(QString m_Answer1 READ answer1 WRITE setAnswer1 NOTIFY answer1Changed MEMBER true)
    Q_PROPERTY(QString m_Answer2 READ answer2 WRITE setAnswer2 NOTIFY answer2Changed MEMBER true)
    Q_PROPERTY(QString m_Answer3 READ answer3 WRITE setAnswer3 NOTIFY answer3Changed MEMBER true)
    Q_PROPERTY(QString m_Answer4 READ answer4 WRITE setAnswer4 NOTIFY answer4Changed MEMBER true)
    Q_PROPERTY(int m_CorrectAnswer READ correctAnswer WRITE setCorrectAnswer NOTIFY correctAnswerChanged MEMBER true)

public:
    QtTestWidget();
    QString question();
    QString imageSource();
    QString answer1();
    QString answer2();
    QString answer3();
    QString answer4();
    int correctAnswer();

signals:
    void questionChanged(QString question);
    void imageChanged(QString image_source);
    void answer1Changed(QString answer1);
    void answer2Changed(QString answer2);
    void answer3Changed(QString answer3);
    void answer4Changed(QString answer4);
    void correctAnswerChanged(int answer);

public slots:
    void setQuestion(QString question);
    void setImage(QString image_source);
    void setAnswer1(QString answer1);
    void setAnswer2(QString answer2);
    void setAnswer3(QString answer3);
    void setAnswer4(QString answer4);
    void setCorrectAnswer(int answer);

protected:
    QString m_Question;
    QString m_ImageSource;
    QString m_Answer1;
    QString m_Answer2;
    QString m_Answer3;
    QString m_Answer4;
    int     m_CorrectAnswer;
};

#endif // QTTESTWIDGET_H
