#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QQmlListProperty>
#include <QVariantList>
#include <QVector>
#include <vector>
#include "subject.h"
// #include "classgroup.h"
#include "classroom.h"
#include "../DBModule/src/functiontemplates.h"

class ClassGroup; // forward declaration

class Teacher : public QObject, public FunctionTemplates
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged FINAL)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged FINAL)
    Q_PROPERTY(QString classTutor READ classTutor WRITE setClassTutor NOTIFY classTutorChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Subject> specjalization READ specjalization NOTIFY specjalizationChanged FINAL)
    Q_PROPERTY(QQmlListProperty<ClassGroup> taughtClasses READ taughtClasses NOTIFY taughtClassesChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Classroom> availableClassrooms READ availableClassrooms NOTIFY availableClassroomsChanged FINAL)
    Q_PROPERTY(QVariantList availability READ availability WRITE setAvailability NOTIFY availabilityChanged FINAL)
public:
    Teacher();
    int id() const;
    void setId(int newId);
    QString firstName() const;
    void setFirstName(const QString &newFirstName);

    QString lastName() const;
    void setLastName(const QString &newLastName);

    QString classTutor() const;
    void setClassTutor(const QString &newClassTutor);

    // QML
    QQmlListProperty<Subject> specjalization();
    QQmlListProperty<ClassGroup> taughtClasses();
    QQmlListProperty<Classroom> availableClassrooms();

    QVariantList availability() const;
    void setAvailability(const QVariantList &newAvailability);
    void setSpecjalization(const QVector<Subject*> &newSpecjalization);
    void setTaughtClasses(const QVector<ClassGroup*> &newTaughtClasses);
    void setAvailableClassrooms(const QVector<Classroom*> &newAvailableClassrooms);

    // C++
    QVector<Subject*> getSpecjalization() const;
    QVector<Classroom*> getAvailableClassrooms() const;
    std::vector<std::vector<int>> getAvailability() const;

signals:
    void idChanged();
    void firstNameChanged();

    void lastNameChanged();

    void classTutorChanged();

    void specjalizationChanged();

    void taughtClassesChanged();

    void availableClassroomsChanged();

    void availabilityChanged();

private:
    int m_id;
    QString m_firstName;
    QString m_lastName;
    QString m_classTutor;
    QVector<Subject*> m_specjalization;
    QVector<ClassGroup*> m_taughtClasses;
    QVector<Classroom*> m_availableClassrooms;
    std::vector<std::vector<int>> m_availability;
};

#endif // TEACHER_H
