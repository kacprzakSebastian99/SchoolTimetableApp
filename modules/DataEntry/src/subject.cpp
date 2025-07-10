#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "subject.h"

Subject::Subject() {}

int Subject::id() const
{
    return m_id;
}

void Subject::setId(int newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString Subject::name() const
{
    return m_name;
}

void Subject::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

QString Subject::shortcut() const
{
    return m_shortcut;
}

void Subject::setShortcut(const QString &newShortcut)
{
    if (m_shortcut == newShortcut)
        return;
    m_shortcut = newShortcut;
    emit shortcutChanged();
}

int Subject::type() const
{
    return m_type;
}

void Subject::setType(const int &newType)
{
    if (m_type == newType)
        return;
    m_type = newType;
    emit typeChanged();
}

int Subject::numberOfHours() const
{
    return m_numberOfHours;
}

void Subject::setNumberOfHours(int newNumberOfHours)
{
    if (m_numberOfHours == newNumberOfHours)
        return;
    m_numberOfHours = newNumberOfHours;
    emit numberOfHoursChanged();
}

int Subject::block() const
{
    return m_block;
}

void Subject::setBlock(int newBlock)
{
    if (m_block == newBlock)
        return;
    m_block = newBlock;
    emit blockChanged();
}

QVariantList Subject::availability() const
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

void Subject::setAvailability(const QVariantList &newAvailability)
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

std::vector<std::vector<int> > Subject::getAvailability() const
{
    return m_availability;
}
