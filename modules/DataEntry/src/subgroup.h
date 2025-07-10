#ifndef SUBGROUP_H
#define SUBGROUP_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QVariantList>

class Subgroup : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged FINAL)
    Q_PROPERTY(int classGroupID READ classGroupID WRITE setClassGroupID NOTIFY classGroupIDChanged FINAL)
    Q_PROPERTY(int subjectID READ subjectID WRITE setSubjectID NOTIFY subjectIDChanged FINAL)
    Q_PROPERTY(int teacherID READ teacherID WRITE setTeacherID NOTIFY teacherIDChanged FINAL)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
public:
    Subgroup();
    int id() const;
    void setId(int newId);
    int classGroupID() const;
    void setClassGroupID(int newClassGroupID);

    int subjectID() const;
    void setSubjectID(int newSubjectID);

    int teacherID() const;
    void setTeacherID(int newTeacherID);

    QString name() const;
    void setName(const QString &newName);

signals:
    void idChanged();
    void classGroupIDChanged();

    void subjectIDChanged();

    void teacherIDChanged();

    void nameChanged();

private:
    int m_id;
    int m_classGroupID;
    int m_subjectID;
    int m_teacherID;
    QString m_name;
};

#endif // SUBGROUP_H
