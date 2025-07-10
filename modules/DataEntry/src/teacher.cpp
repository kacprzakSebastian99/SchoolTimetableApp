#include "teacher.h"

Teacher::Teacher() {}

int Teacher::id() const
{
    return m_id;
}

void Teacher::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString Teacher::firstName() const
{
    return m_firstName;
}

void Teacher::setFirstName(const QString &newFirstName)
{
    if (m_firstName == newFirstName)
        return;
    m_firstName = newFirstName;
    emit firstNameChanged();
}

QString Teacher::lastName() const
{
    return m_lastName;
}

void Teacher::setLastName(const QString &newLastName)
{
    if (m_lastName == newLastName)
        return;
    m_lastName = newLastName;
    emit lastNameChanged();
}

QString Teacher::classTutor() const
{
    return m_classTutor;
}

void Teacher::setClassTutor(const QString &newClassTutor)
{
    if (m_classTutor == newClassTutor)
        return;
    m_classTutor = newClassTutor;
    emit classTutorChanged();
}

QQmlListProperty<Subject> Teacher::specjalization()
{
    return QQmlListProperty<Subject>(this,
                                     &m_specjalization,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<ClassGroup> Teacher::taughtClasses()
{
    return QQmlListProperty<ClassGroup>(this,
                                     &m_taughtClasses,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<Classroom> Teacher::availableClassrooms()
{
    return QQmlListProperty<Classroom>(this,
                                     &m_availableClassrooms,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QVariantList Teacher::availability() const
{
    QVariantList convertData;
    for(const auto& row : m_availability)
    {
        QVariantList convertRow;
        for(const auto& item : row)
        {
            convertRow.append(QVariant::fromValue(item));
        }
        convertData.append(convertRow);
    }
    return convertData;
}

void Teacher::setAvailability(const QVariantList &newAvailability)
{
    std::vector<std::vector<int>> convertData;
    for(const auto& row : newAvailability)
    {
        std::vector<int> convertRow;
        QVariantList rowList = row.toList();
        for(const auto& item : rowList)
        {
            convertRow.push_back(item.toInt());
        }
        convertData.push_back(convertRow);
    }

    if (m_availability == convertData)
        return;
    m_availability = convertData;
    emit availabilityChanged();
}

void Teacher::setSpecjalization(const QVector<Subject *> &newSpecjalization)
{
    if (m_specjalization == newSpecjalization)
        return;
    m_specjalization = newSpecjalization;
    emit specjalizationChanged();
}

void Teacher::setTaughtClasses(const QVector<ClassGroup *> &newTaughtClasses)
{
    if (m_taughtClasses == newTaughtClasses)
        return;
    m_taughtClasses = newTaughtClasses;
    emit taughtClassesChanged();
}

void Teacher::setAvailableClassrooms(const QVector<Classroom *> &newAvailableClassrooms)
{
    if (m_availableClassrooms == newAvailableClassrooms)
        return;
    m_availableClassrooms = newAvailableClassrooms;
    emit availableClassroomsChanged();
}

QVector<Subject *> Teacher::getSpecjalization() const
{
    return m_specjalization;
}

QVector<Classroom *> Teacher::getAvailableClassrooms() const
{
    return m_availableClassrooms;
}

std::vector<std::vector<int> > Teacher::getAvailability() const
{
    return m_availability;
}


