#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QDateTime>
#include <QTime>
#include <QQmlListProperty>
#include <QVariantList>
#include <QList>
#include <QVector>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "gene.h"
#include "geneticalgorithm.h"
//#include "../DBModule/src/functiontemplates.h"

//class FunctionTemplates;

class Timetable : public QObject//, public FunctionTemplates
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged FINAL)
    Q_PROPERTY(int maxNumberOfLessons READ maxNumberOfLessons WRITE setMaxNumberOfLessons NOTIFY maxNumberOfLessonsChanged FINAL)
    Q_PROPERTY(QQmlListProperty<QTime> lessonHours READ lessonHours NOTIFY lessonHoursChanged FINAL)
    Q_PROPERTY(QList<QString> timetableData READ getTimetableData WRITE setTimetableData NOTIFY timetableDataChanged FINAL)
public:
    Timetable();

    int id() const;
    void setId(int newId);
    QString name() const;
    void setName(const QString &newName);

    QDateTime date() const;
    void setDate(const QDateTime &newDate);

    int maxNumberOfLessons() const;
    void setMaxNumberOfLessons(int newMaxNumberOfLessons);

    // Gettery i Settery QML
    QQmlListProperty<QTime> lessonHours();
    // dodać setter dla lessonHours

    // Gettery i Settery C++
    Q_INVOKABLE QList<QString> getTimetableData() const;
    void setTimetableData(const QList<QString> &newTimetableData);//, const QString &newName, const QString &newLessonHours);



signals:
    void idChanged();
    void nameChanged();

    void dateChanged();

    void maxNumberOfLessonsChanged();

    void lessonHoursChanged();

    void timetableDataChanged();

private:
    int m_id;
    QString m_name;
    QDateTime m_date;
    int m_maxNumberOfLessons;
    QVector<QTime*> m_lessonHours;
    QList<QString> m_timetableData;
};

#endif // TIMETABLE_H
