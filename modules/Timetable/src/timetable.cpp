#include "timetable.h"
//#include "../DBModule/src/functiontemplates.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>
#include <QString>
#include "../DBModule/src/containers.h"
#include "../DBModule/src/databasemanager.h"
#include "../DataEntry/src/subject.h"
#include "../DataEntry/src/profile.h"
#include "../DataEntry/src/classroom.h"
#include "../DataEntry/src/teacher.h"
#include "../DataEntry/src/classgroup.h"

Timetable::Timetable() {}



int Timetable::id() const
{
    return m_id;
}

void Timetable::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString Timetable::name() const
{
    return m_name;
}

void Timetable::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QDateTime Timetable::date() const
{
    return m_date;
}

void Timetable::setDate(const QDateTime &newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

int Timetable::maxNumberOfLessons() const
{
    return m_maxNumberOfLessons;
}

void Timetable::setMaxNumberOfLessons(int newMaxNumberOfLessons)
{
    if (m_maxNumberOfLessons == newMaxNumberOfLessons)
        return;
    m_maxNumberOfLessons = newMaxNumberOfLessons;
    emit maxNumberOfLessonsChanged();
}

QQmlListProperty<QTime> Timetable::lessonHours()
{
    return QQmlListProperty<QTime>(this,
                                   &m_lessonHours);//,
                                   // &append,
                                   // &count,
                                   // &at,
                                   // &clear,
                                   // &replace,
                                   // &removeLast);
}

QList<QString> Timetable::getTimetableData() const
{
    // przetwarzenie id na nazwy

    return m_timetableData;
}

void Timetable::setTimetableData(const QList<QString> &newTimetableData)//, const QString &newName, const QString &newLessonHours)
{
    if (m_timetableData == newTimetableData)
        return;
    m_timetableData = newTimetableData;
    emit timetableDataChanged();
}
