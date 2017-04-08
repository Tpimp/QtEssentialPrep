#include "qttesttypeloader.h"
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDir>

QtTestTypeLoader::QtTestTypeLoader(QObject *parent) : QObject(parent), m_QuestionCount(0)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
}

void QtTestTypeLoader::clearTypes()
{
    m_QuestionCount = 0;
    m_QuestionDocuments.clear();
    emit clearedTypes();
}

void QtTestTypeLoader::loadQuestionSet(QString pwd,QString question_path)
{
    QFile file(pwd+question_path);
    if(file.exists()){
        file.open(QIODevice::ReadOnly);
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        // validate
        // emit errors if they exist
        QJsonObject obj = doc.object();
        QString question_type = obj["Type"].toString();
        if(obj.contains("Questions")){

            QJsonValue questions_val = obj["Questions"];
            if(!questions_val.isNull())
            {
                QJsonArray questions = questions_val.toArray();
                foreach(QJsonValue q_val,questions){
                    if(q_val.isObject()){
                        QJsonObject obj = q_val.toObject();
                        if(obj.contains("I")){
                            QString image_path = obj["I"].toString();
                            if(!image_path.isEmpty()){
                                emit imageFound(pwd+image_path);
                            }
                        }
                    }
                }
                m_QuestionDocuments.insert(question_type, questions);
                m_QuestionCount += questions.count();
                emit loadedType(questions.count(),question_type);
            }
        }
    }
}

void QtTestTypeLoader::loadRootQuestionDirectory(QString question_dir)
{
    // for each directory
    // search for .json files -> load those as Questions
    // search for all images requested
    // @PWD/image_source (could be directory path just file name)
    QDir pwd(question_dir);
    if(pwd.exists())
    {
        QStringList filter;
        filter.append(".json");
        QStringList files = pwd.entryList(filter, QDir::Files);
        foreach(QString question_db_path, files){
            loadQuestionSet(pwd.path(),question_db_path);
        }
    }
    QStringList sub_dirs = pwd.entryList(QDir::Dirs);
    foreach(QString dir,sub_dirs){
        if(dir.compare("..") != 0 && dir.compare(".") != 0){
            loadRootQuestionDirectory(pwd.path()+ dir);
        }
    }
}

QJsonObject QtTestTypeLoader::fetchQuestion(int question_number)
{
    QJsonObject obj;
    if(question_number >= 0 &&  question_number < m_QuestionCount){
        // valid request
        int current_q = 0;
        foreach(QJsonArray q_array, m_QuestionDocuments){
            if((current_q + q_array.count()) >= question_number ){ // inside this array
                obj = q_array.at(question_number-current_q).toObject();
                break;
            }
        }
    }
    return obj;
}

QJsonArray QtTestTypeLoader::getQuestionsByType(QString type)
{
    if(m_QuestionDocuments.contains(type))
        return m_QuestionDocuments.value(type);
    return QJsonArray();
}

QJsonObject QtTestTypeLoader::getRandomQuestion()
{
    return fetchQuestion((qrand() % m_QuestionCount));
}

QStringList QtTestTypeLoader::getTypes()
{
    return m_QuestionDocuments.keys();
}

int QtTestTypeLoader::questionCount()
{
    return m_QuestionCount;
}
