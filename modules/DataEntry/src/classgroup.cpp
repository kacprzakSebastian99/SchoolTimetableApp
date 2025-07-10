#include "classgroup.h"

ClassGroup::ClassGroup() {}

int ClassGroup::id() const
{
    return m_id;
}

void ClassGroup::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString ClassGroup::name() const
{
    return m_name;
}

void ClassGroup::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int ClassGroup::profileID() const
{
    return m_profileID;
}

void ClassGroup::setProfileID(int newProfileID)
{
    if (m_profileID == newProfileID)
        return;
    m_profileID = newProfileID;
    emit profileIDChanged();
}

int ClassGroup::fixedLessonStartTime() const
{
    return m_fixedLessonStartTime;
}

void ClassGroup::setFixedLessonStartTime(int newFixedLessonStartTime)
{
    if (m_fixedLessonStartTime == newFixedLessonStartTime)
        return;
    m_fixedLessonStartTime = newFixedLessonStartTime;
    emit fixedLessonStartTimeChanged();
}

QString ClassGroup::mainClassroom() const
{
    return m_mainClassroom;
}

void ClassGroup::setMainClassroom(const QString &newMainClassroom)
{
    if (m_mainClassroom == newMainClassroom)
        return;
    m_mainClassroom = newMainClassroom;
    emit mainClassroomChanged();
}

void ClassGroup::setTeachers(const QVector<Teacher *> &newTeachers)
{
    if (m_teachers == newTeachers)
        return;
    m_teachers = newTeachers;
    emit teachersChanged();
}

QQmlListProperty<Teacher> ClassGroup::teachers()
{
    return QQmlListProperty<Teacher>(this,
                                     &m_teachers,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<Subgroup> ClassGroup::subgroups()
{
    return QQmlListProperty<Subgroup>(this,
                                     &m_subgroups,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QVector<Teacher *> ClassGroup::getTeachers() const
{
    return m_teachers;
}

int ClassGroup::classTeacherID() const
{
    return m_classTeacherID;
}

void ClassGroup::setClassTeacherID(int newClassTeacherID)
{
    if (m_classTeacherID == newClassTeacherID)
        return;
    m_classTeacherID = newClassTeacherID;
    emit classTeacherIDChanged();
}
