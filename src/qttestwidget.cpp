#include "qttestwidget.h"

QtTestWidget::QtTestWidget(QObject* parent) : QObject(parent)
{

}

QString QtTestWidget::answer1()
{
  return m_Answer1;
}
QString QtTestWidget::answer2()
{
    return m_Answer2;

}
QString QtTestWidget::answer3()
{
    return m_Answer3;
}
QString QtTestWidget::answer4()
{
    return m_Answer4;
}

int QtTestWidget::correctAnswer()
{
    return m_CorrectAnswer;
}

QString QtTestWidget::question()
{
    return m_Question;
}

QString QtTestWidget::imageSource()
{
    return m_ImageSource;
}


void QtTestWidget::setAnswer1(QString answer1)
{
  if(answer1.compare(m_Answer1) != 0)
  {
      m_Answer1 = answer1;
      emit answer1Changed(m_Answer1);
  }
}

void QtTestWidget::setAnswer2(QString answer2)
{
  if(answer2.compare(m_Answer2) != 0)
  {
      m_Answer2 = answer2;
      emit answer2Changed(m_Answer2);
  }
}

void QtTestWidget::setAnswer3(QString answer3)
{
  if(answer3.compare(m_Answer3) != 0)
  {
      m_Answer3 = answer3;
      emit answer3Changed(m_Answer3);
  }
}

void QtTestWidget::setAnswer4(QString answer4)
{
  if(answer4.compare(m_Answer4) != 0)
  {
      m_Answer4 = answer4;
      emit answer4Changed(m_Answer4);
  }
}

void QtTestWidget::setCorrectAnswer(int answer)
{
    if(answer != m_CorrectAnswer)
    {
        m_CorrectAnswer = answer;
        emit correctAnswerChanged(m_CorrectAnswer);
    }
}

void QtTestWidget::setImage(QString image_source)
{
    if(image_source.compare(m_ImageSource) != 0)
    {
        m_ImageSource = image_source;
        emit imageChanged(m_ImageSource);
    }
}


void QtTestWidget::setQuestion(QString question)
{
    if(question.compare(m_Question) != 0)
    {
        m_Question = question;
        emit questionChanged(m_Question);
    }
}
