#include "subgroup.h"

Subgroup::Subgroup() {}

int Subgroup::id() const
{
    return m_id;
}

void Subgroup::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

int Subgroup::classGroupID() const
{
    return m_classGroupID;
}

void Subgroup::setClassGroupID(int newClassGroupID)
{
    if (m_classGroupID == newClassGroupID)
        return;
    m_classGroupID = newClassGroupID;
    emit classGroupIDChanged();
}

int Subgroup::subjectID() const
{
    return m_subjectID;
}

void Subgroup::setSubjectID(int newSubjectID)
{
    if (m_subjectID == newSubjectID)
        return;
    m_subjectID = newSubjectID;
    emit subjectIDChanged();
}

int Subgroup::teacherID() const
{
    return m_teacherID;
}

void Subgroup::setTeacherID(int newTeacherID)
{
    if (m_teacherID == newTeacherID)
        return;
    m_teacherID = newTeacherID;
    emit teacherIDChanged();
}

QString Subgroup::name() const
{
    return m_name;
}

void Subgroup::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}
