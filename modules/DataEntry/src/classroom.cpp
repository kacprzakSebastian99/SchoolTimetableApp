#include "classroom.h"

Classroom::Classroom() {}

int Classroom::id() const
{
    return m_id;
}

void Classroom::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString Classroom::name() const
{
    return m_name;
}

void Classroom::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

int Classroom::type() const
{
    return m_type;
}

void Classroom::setType(const int &newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

QVariantList Classroom::availability() const
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

void Classroom::setAvailability(const QVariantList &newAvailability)
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

std::vector<std::vector<int> > Classroom::getAvailability() const
{
    return m_availability;
}
