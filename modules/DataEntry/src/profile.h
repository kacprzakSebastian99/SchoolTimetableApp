#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QQmlListProperty>
#include <vector>
#include "subject.h"
#include "../DBModule/src/functiontemplates.h"

class Profile : public QObject, public FunctionTemplates
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int classLevel READ classLevel WRITE setClassLevel NOTIFY classLevelChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Subject> subjectsList READ subjectsList NOTIFY subjectsListChanged FINAL)
public:
    Profile();
    int id() const;
    void setId(int newId);
    QString name() const;
    void setName(const QString &newName);

    int classLevel() const;
    void setClassLevel(int newClassLevel);

    // QML
    QQmlListProperty<Subject> subjectsList();

    // C++
    QVector<Subject*> getSubjectsList() const;

    void setSubjectList(const QVector<Subject*> &newSubjectsList);



signals:
    void idChanged();
    void nameChanged();

    void classLevelChanged();

    void subjectsListChanged();

private:
    int m_id;
    QString m_name;
    int m_classLevel;
    QVector<Subject*> m_subjectsList;
};

#endif // PROFILE_H
