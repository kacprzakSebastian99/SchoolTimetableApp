#ifndef CONTAINERS_H
#define CONTAINERS_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QPdfWriter>
#include <QPainter>
#include <QQuickItem>
#include <QQuickWindow>
#include <QUrl>
#include <QQuickItemGrabResult>

// #include "../DataEntry/src/subject.h"
// #include "../DataEntry/src/profile.h"
// #include "../DataEntry/src/classroom.h"
// #include "../DataEntry/src/teacher.h"
// #include "../DataEntry/src/classgroup.h"
#include "functiontemplates.h"

class Subject;
class Profile;
class Classroom;
class Teacher;
class ClassGroup;
class Timetable;

class Containers : public QObject, public FunctionTemplates
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QQmlListProperty<Subject> subjects READ subjects NOTIFY subjectsChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Profile> profiles READ profiles NOTIFY profilesChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Classroom> classrooms READ classrooms NOTIFY classroomsChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Teacher> teachers READ teachers NOTIFY teachersChanged FINAL)
    Q_PROPERTY(QQmlListProperty<ClassGroup> classGroups READ classGroups NOTIFY classGroupsChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Timetable> timetables READ timetables NOTIFY timetablesChanged FINAL)
public:
    Containers();
    ~Containers();

    static Containers& instance();

    // Gettery i Settery QML
    QQmlListProperty<Subject> subjects();
    QQmlListProperty<Profile> profiles();
    QQmlListProperty<Classroom> classrooms();
    QQmlListProperty<Teacher> teachers();
    QQmlListProperty<ClassGroup> classGroups();
    QQmlListProperty<Timetable> timetables();
    // Gettery C++
    QVector<Subject*> getSubjects() const;
    QVector<Profile*> getProfiles() const;
    QVector<Classroom*> getClassrooms() const;
    QVector<Teacher*> getTeachers() const;
    QVector<ClassGroup*> getClassGroups() const;
    // getTimetables ?

    // Dodawanie elementów QML i C++

    Q_INVOKABLE void addSubject(const QString &name, const QString &shortcut, const int &type);
    Q_INVOKABLE void addProfile(const QString &name, const int &classLevel, const QVariantList &subjectsList);
    Q_INVOKABLE void addClassroom(const QString &name, const int &type, const QVariantList &availability);
    Q_INVOKABLE void addTeacher(const QString &firstName, const QString &lastName, const QVariantList &specjalization, const QVariantList &availableClassrooms, const QVariantList &availability);
    Q_INVOKABLE void addClassGroup(const QString &name, const int &fixedLessonStartTime, const int &profileID, const int &classTeacherID, const QVariantList &teachersList);
    // Usuwanie elementów QML i C++
    // Pobieranie pojedyńczego elementu;

    // Pobieranie wszystkich danych z DB do containers
    Q_INVOKABLE void loadDataFromDB(); // Pobiera dane z DB do kontenerów
    Q_INVOKABLE void downloadSubjects();
    Q_INVOKABLE void downloadProfiles();
    Q_INVOKABLE void downloadClassrooms();
    Q_INVOKABLE void downloadTeachers();
    Q_INVOKABLE void downloadClassGroups();
    Q_INVOKABLE void downloadTimetableData();

    Q_INVOKABLE void saveToPDF(const QUrl &fileUrl, QQuickItem *item);

    // Usuwanie elementów
    Q_INVOKABLE void deleteSubject(int id);
    Q_INVOKABLE void deleteProfile(int id);
    Q_INVOKABLE void deleteClassroom(int id);
    Q_INVOKABLE void deleteTeacher(int id);
    Q_INVOKABLE void deleteClassGroup(int id);
    Q_INVOKABLE void deleteTimetableData(int id);


signals:
    void subjectsChanged();
    void profilesChanged();

    void classroomsChanged();

    void teachersChanged();

    void classGroupsChanged();

    void timetablesChanged();

private:
    static Containers* m_instance;

    QVector<Subject*> m_subjects;
    QVector<Profile*> m_profiles;
    QVector<Classroom*> m_classrooms;
    QVector<Teacher*> m_teachers;
    QVector<ClassGroup*> m_classGroups;
    QVector<Timetable*> m_timetables;

    QString getSubjectShortcut(QSqlDatabase& db, int subjectID);
    QString getTeacherName(QSqlDatabase& db, int teacherID);
    QString getClassroomName(QSqlDatabase& db, int classroomID);
    QString getClassGroupName(QSqlDatabase& db, int classGroupID);
};

#endif // CONTAINERS_H
