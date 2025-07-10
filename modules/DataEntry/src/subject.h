#ifndef SUBJECT_H
#define SUBJECT_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QVariantList>
#include <vector>

class Subject : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString shortcut READ shortcut WRITE setShortcut NOTIFY shortcutChanged FINAL)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(int numberOfHours READ numberOfHours WRITE setNumberOfHours NOTIFY numberOfHoursChanged FINAL)
    Q_PROPERTY(int block READ block WRITE setBlock NOTIFY blockChanged FINAL)
    Q_PROPERTY(QVariantList availability READ availability WRITE setAvailability NOTIFY availabilityChanged FINAL)
public:
    Subject();
    int id() const;
    void setId(int newId);
    QString name() const;
    void setName(const QString &newName);

    QString shortcut() const;
    void setShortcut(const QString &newShortcut);

    int type() const;
    void setType(const int &newType);

    int numberOfHours() const;
    void setNumberOfHours(int newNumberOfHours);

    int block() const;
    void setBlock(int newBlock);

    // Gettery i Settery QML
    QVariantList availability() const;
    void setAvailability(const QVariantList &newAvailability);

    // Gettery i Settery C++
    std::vector<std::vector<int>> getAvailability() const;


signals:
    void idChanged();
    void nameChanged();

    void shortcutChanged();

    void typeChanged();

    void numberOfHoursChanged();

    void blockChanged();

    void availabilityChanged();

private:
    int m_id;
    QString m_name;
    QString m_shortcut;
    int m_type;
    int m_numberOfHours;
    int m_block;
    std::vector<std::vector<int>> m_availability;
};

#endif // SUBJECT_H
