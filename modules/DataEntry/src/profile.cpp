#include "profile.h"

Profile::Profile() {}

int Profile::id() const
{
    return m_id;
}

void Profile::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString Profile::name() const
{
    return m_name;
}

void Profile::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int Profile::classLevel() const
{
    return m_classLevel;
}

void Profile::setClassLevel(int newClassLevel)
{
    if (m_classLevel == newClassLevel)
        return;
    m_classLevel = newClassLevel;
    emit classLevelChanged();
}

QQmlListProperty<Subject> Profile::subjectsList()
{
    return QQmlListProperty<Subject>(this,
                                     &m_subjectsList,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}


QVector<Subject *> Profile::getSubjectsList() const
{
    return m_subjectsList;
}

void Profile::setSubjectList(const QVector<Subject *> &newSubjectsList)
{
    for(Subject *ptr : newSubjectsList)
    {
        m_subjectsList.append(ptr);
    }
}


