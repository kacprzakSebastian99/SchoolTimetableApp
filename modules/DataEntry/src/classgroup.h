#ifndef CLASSGROUP_H
#define CLASSGROUP_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QQmlListProperty>
#include <QVector>
// #include "teacher.h"
#include "subgroup.h"
#include "../DBModule/src/functiontemplates.h"

class Teacher; // forward declaration

class ClassGroup : public QObject, public FunctionTemplates
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int profileID READ profileID WRITE setProfileID NOTIFY profileIDChanged FINAL)
    Q_PROPERTY(int fixedLessonStartTime READ fixedLessonStartTime WRITE setFixedLessonStartTime NOTIFY fixedLessonStartTimeChanged FINAL)
    Q_PROPERTY(int classTeacherID READ classTeacherID WRITE setClassTeacherID NOTIFY classTeacherIDChanged FINAL)
    Q_PROPERTY(QString mainClassroom READ mainClassroom WRITE setMainClassroom NOTIFY mainClassroomChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Teacher> teachers READ teachers NOTIFY teachersChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Subgroup> subgroups READ subgroups NOTIFY subgroupsChanged FINAL)
public:
    ClassGroup();
    int id() const;
    void setId(int newId);
    QString name() const;
    void setName(const QString &newName);

    int profileID() const;
    void setProfileID(int newProfileID);

    int fixedLessonStartTime() const;
    void setFixedLessonStartTime(int newFixedLessonStartTime);

    int classTeacherID() const;
    void setClassTeacherID(int newClassTeacherID);

    QString mainClassroom() const;
    void setMainClassroom(const QString &newMainClassroom);

    void setTeachers(const QVector<Teacher*> &newTeachers);

    // QML
    QQmlListProperty<Teacher> teachers();

    QQmlListProperty<Subgroup> subgroups();

    // C++
    QVector<Teacher*> getTeachers() const;

signals:
    void idChanged();
    void nameChanged();

    void profileIDChanged();

    void fixedLessonStartTimeChanged();

    void classTeacherIDChanged();

    void mainClassroomChanged();

    void teachersChanged();

    void subgroupsChanged();

private:
    int m_id;
    QString m_name;
    int m_profileID;
    int m_fixedLessonStartTime;
    int m_classTeacherID;
    QString m_mainClassroom;
    QVector<Teacher*> m_teachers;
    QVector<Subgroup*> m_subgroups;
};

#endif // CLASSGROUP_H
