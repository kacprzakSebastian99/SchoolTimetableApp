#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QVariantList>
#include <vector>

class Classroom : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged FINAL)
    Q_PROPERTY(QVariantList availability READ availability WRITE setAvailability NOTIFY availabilityChanged FINAL)
public:
    Classroom();
    int id() const;
    void setId(int newId);
    QString name() const;
    void setName(const QString &newName);

    int type() const;
    void setType(const int &newType);

    // QML
    QVariantList availability() const;
    void setAvailability(const QVariantList &newAvailability);

    // C++
    std::vector<std::vector<int>> getAvailability() const;

signals:
    void idChanged();
    void nameChanged();

    void typeChanged();

    void availabilityChanged();

private:
    int m_id;
    QString m_name;
    int m_type;
    std::vector<std::vector<int>> m_availability;
};

#endif // CLASSROOM_H
