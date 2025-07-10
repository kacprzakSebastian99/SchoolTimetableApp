#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>
#include <QString>
#include "containers.h"
#include "databasemanager.h"
#include "../DataEntry/src/subject.h"
#include "../DataEntry/src/profile.h"
#include "../DataEntry/src/classroom.h"
#include "../DataEntry/src/teacher.h"
#include "../DataEntry/src/classgroup.h"
#include "../Timetable/src/timetable.h"

Containers* Containers::m_instance = nullptr;

Containers::Containers() {
    loadDataFromDB(); // Załaduj dane zaraz po uruchomieniu programu
    // downloadSubjects();
    // downloadProfiles();
    // downloadClassrooms();
    // downloadTeachers();
    // downloadClassGroups();
}

Containers::~Containers()
{
    for(Subject* subject : m_subjects)
        delete subject;

    m_subjects.clear();

    for(Profile* profile : m_profiles)
        delete profile;

    m_profiles.clear();

    for(Classroom* classroom : m_classrooms)
        delete classroom;

    m_classrooms.clear();

    for(Teacher* teacher : m_teachers)
        delete teacher;

    m_teachers.clear();

    for(ClassGroup* classGroup : m_classGroups)
        delete classGroup;

    m_classGroups.clear();
}

Containers &Containers::instance()
{
    if(m_instance == nullptr)
    {
        m_instance = new Containers();
    }
    return *m_instance;
}

QQmlListProperty<Subject> Containers::subjects()
{
    // return QQmlListProperty<Subject>(this, m_subjects);
    return QQmlListProperty<Subject>(this,
                                     &m_subjects,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<Profile> Containers::profiles()
{
    return QQmlListProperty<Profile>(this,
                                     &m_profiles,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<Classroom> Containers::classrooms()
{
    return QQmlListProperty<Classroom>(this,
                                     &m_classrooms,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<Teacher> Containers::teachers()
{
    return QQmlListProperty<Teacher>(this,
                                     &m_teachers,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<ClassGroup> Containers::classGroups()
{
    return QQmlListProperty<ClassGroup>(this,
                                     &m_classGroups,
                                     &append,
                                     &count,
                                     &at,
                                     &clear,
                                     &replace,
                                     &removeLast);
}

QQmlListProperty<Timetable> Containers::timetables()
{
    return QQmlListProperty<Timetable>(this,
                                        &m_timetables,
                                        &append,
                                        &count,
                                        &at,
                                        &clear,
                                        &replace,
                                        &removeLast);
}

QVector<Subject *> Containers::getSubjects() const
{
    return m_subjects;
}

QVector<Profile *> Containers::getProfiles() const
{
    return m_profiles;
}

QVector<Classroom *> Containers::getClassrooms() const
{
    return m_classrooms;
}

QVector<Teacher *> Containers::getTeachers() const
{
    return m_teachers;
}

QVector<ClassGroup *> Containers::getClassGroups() const
{
    return m_classGroups;
}

void Containers::addSubject(const QString &name, const QString &shortcut, const int &type)
{
    Subject* newSubject = new Subject();
    newSubject->setName(name);
    newSubject->setShortcut(shortcut);
    newSubject->setType(type);

    QSqlDatabase db = DatabaseManager::instance().getDB();

    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS subjects (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, shortcut TEXT, type INTEGER)");
    query.prepare("INSERT INTO subjects (id, name, shortcut, type) VALUES (:id, :name, :shortcut, :type)");

    query.bindValue(":name", name);
    query.bindValue(":shortcut", shortcut);
    query.bindValue(":type", type);
    query.exec();

    m_subjects.append(newSubject);
    // emit subjectsChanged();
}

void Containers::addProfile(const QString &name, const int &classLevel, const QVariantList &subjectsList)
{
    Profile* newProfile = new Profile();
    newProfile->setName(name);
    newProfile->setClassLevel(classLevel);

    QSqlDatabase db = DatabaseManager::instance().getDB();

    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS profiles (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, classLevel INTEGER)");
    query.prepare("INSERT INTO profiles (id, name, classLevel) VALUES (:id, :name, :classLevel)");

    query.bindValue(":name", name);
    query.bindValue(":classLevel", classLevel);
    query.exec();

    query.prepare("SELECT id FROM profiles WHERE name = :name");
    query.bindValue(":name", name);
    query.exec();
    int profileID = 0;

    if(query.next())
        profileID = query.value(0).toInt();

    // PROFILE-SUBJECTS
    query.exec("CREATE TABLE IF NOT EXISTS profiles_subjects (id INTEGER PRIMARY KEY AUTOINCREMENT, profileID INTEGER, subjectID INTEGER, numberOfHours INTEGER, block INTEGER, availability TEXT)");

    QVector<Subject*> tmp;
    //QVariantList convertedList = subjectsList.toList();
    //qDebug() << "Converted subjectsList size:" << convertedList.size();
    for(const QVariant &item : subjectsList)
    {
        QVariantMap map = item.toMap();

        // qDebug() << "Mapping Subject Data:";
        // qDebug() << "ID:" << map["id"].toInt();
        // qDebug() << "Name:" << map["name"].toString();
        // qDebug() << "Shortcut:" << map["shortcut"].toString();
        // qDebug() << "Type:" << map["type"].toInt();
        // qDebug() << "Number of Hours:" << map["hours"].toInt();
        // qDebug() << "Block:" << map["block"].toInt();
        // qDebug() << "Availability (JSON String):" << map["availability"].toString();

        // QJsonDocument doc1 = QJsonDocument::fromJson(map["availability"].toString().toUtf8());
        // QVariantList availabilityList = doc1.array().toVariantList();

        // qDebug() << "Parsed Availability:" << availabilityList;


        Subject* newSubject = new Subject();
        newSubject->setId(map["id"].toInt());
        newSubject->setName(map["name"].toString());
        newSubject->setShortcut(map["shortcut"].toString());//dodac
        newSubject->setType(map["type"].toInt());//dodac
        newSubject->setNumberOfHours(map["hours"].toInt());
        newSubject->setBlock(map["block"].toInt());
        QJsonDocument doc = QJsonDocument::fromJson(map["availability"].toString().toUtf8());
        newSubject->setAvailability(doc.array().toVariantList());// sprawdzic

        tmp.append(newSubject);

        query.prepare("INSERT INTO profiles_subjects (profileID, subjectID, numberOfHours, block, availability) VALUES (:profileID, :subjectID, :numberOfHours, :block, :availability)");

        query.bindValue(":profileID", profileID);
        query.bindValue(":subjectID", map["id"].toInt());
        query.bindValue(":numberOfHours", map["hours"].toInt());
        query.bindValue(":block", map["block"].toInt());
        query.bindValue(":availability", map["availability"].toString());
        //query.exec();

        if (!query.exec()) {
            qDebug() << "Błąd zapytania INSERT:" << query.lastError().text();
        }
    }

    newProfile->setSubjectList(tmp);

    m_profiles.append(newProfile);
    // emit profilesChanged();
}

void Containers::addClassroom(const QString &name, const int &type, const QVariantList &availability)
{
    Classroom* newClassroom = new Classroom();
    newClassroom->setName(name);
    newClassroom->setType(type);

    QVariantMap map = availability[0].toMap();
    QJsonDocument doc = QJsonDocument::fromJson(map["availability"].toString().toUtf8());

    newClassroom->setAvailability(doc.array().toVariantList());

    QSqlDatabase db = DatabaseManager::instance().getDB();

    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS classrooms (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, type INTEGER, availability TEXT)");
    query.prepare("INSERT INTO classrooms (name, type, availability) VALUES (:name, :type, :availability)");

    query.bindValue(":name", name);
    query.bindValue(":type", type);
    query.bindValue(":availability", map["availability"].toString());
    query.exec();

    m_classrooms.append(newClassroom);
    // emit classroomsChanged();
}

void Containers::addTeacher(const QString &firstName, const QString &lastName, const QVariantList &specjalization, const QVariantList &availableClassrooms, const QVariantList &availability)
{
    Teacher* newTeacher = new Teacher();
    newTeacher->setFirstName(firstName);
    newTeacher->setLastName(lastName);

    QVariantMap map = availability[0].toMap();
    QJsonDocument doc = QJsonDocument::fromJson(map["availability"].toString().toUtf8());

    newTeacher->setAvailability(doc.array().toVariantList());

    QSqlDatabase db = DatabaseManager::instance().getDB();

    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS teachers (id INTEGER PRIMARY KEY AUTOINCREMENT, firstName TEXT, lastName TEXT, availability TEXT)");
    query.prepare("INSERT INTO teachers (firstName, lastName, availability) VALUES (:firstName, :lastName, :availability)");

    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":availability", map["availability"].toString());
    query.exec();

    query.exec("SELECT last_insert_rowid()");

    int teacherID = 0;
    if (query.next()) {
        teacherID = query.value(0).toInt();
    }

    // TEACHERS_CLASSROOMS
    query.exec("CREATE TABLE IF NOT EXISTS teachers_subjects (id INTEGER PRIMARY KEY AUTOINCREMENT, teacherID INTEGER, subjectID INTEGER)");

    QVector<Subject*> tmpSubjects;

    for(const QVariant &item : specjalization)
    {
        QVariantMap map = item.toMap();

        Subject* newSubject = new Subject();
        newSubject->setId(map["id"].toInt());
        newSubject->setName(map["name"].toString());

        tmpSubjects.append(newSubject);

        query.prepare("INSERT INTO teachers_subjects (teacherID, subjectID) VALUES (:teacherID, :subjectID)");

        query.bindValue(":teacherID", teacherID);
        query.bindValue(":subjectID", map["id"].toInt());
        query.exec();
    }
    newTeacher->setSpecjalization(tmpSubjects);

    // TEACHERS_SUBJECTS
    query.exec("CREATE TABLE IF NOT EXISTS teachers_classrooms (id INTEGER PRIMARY KEY AUTOINCREMENT, teacherID INTEGER, classroomID INTEGER)");

    QVector<Classroom*> tmpClassrooms;

    for(const QVariant &item : availableClassrooms)
    {
        QVariantMap map = item.toMap();

        Classroom* newClassroom = new Classroom();
        newClassroom->setId(map["id"].toInt());
        newClassroom->setName(map["name"].toString());

        tmpClassrooms.append(newClassroom);

        query.prepare("INSERT INTO teachers_classrooms (teacherID, classroomID) VALUES (:teacherID, :classroomID)");

        query.bindValue(":teacherID", teacherID);
        query.bindValue(":classroomID", map["id"].toInt());
        query.exec();
    }
    newTeacher->setAvailableClassrooms(tmpClassrooms);

    m_teachers.append(newTeacher);
    // emit teachersChanged();
}

void Containers::addClassGroup(const QString &name, const int &fixedLessonStartTime, const int &profileID, const int &classTeacherID, const QVariantList &teachersList)
{
    ClassGroup* newClassGroup = new ClassGroup();
    newClassGroup->setName(name);
    newClassGroup->setProfileID(profileID);
    newClassGroup->setFixedLessonStartTime(fixedLessonStartTime);
    newClassGroup->setClassTeacherID(classTeacherID);

    QSqlDatabase db = DatabaseManager::instance().getDB();

    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS classGroups (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, profileID INTEGER, classTeacherID INTEGER, fixedLessonStartTime INTEGER)");
    query.prepare("INSERT INTO classGroups (name, profileID, classTeacherID, fixedLessonStartTime) VALUES (:name, :profileID, :classTeacherID, :fixedLessonStartTime)");

    query.bindValue(":name", name);
    query.bindValue(":profileID", profileID);
    query.bindValue(":fixedLessonStartTime", fixedLessonStartTime);
    query.bindValue(":classTeacherID", classTeacherID);
    query.exec();

    query.exec("SELECT last_insert_rowid()");

    int classGroupID = 0;
    if (query.next()) {
        classGroupID = query.value(0).toInt();
    }

    // TEACHERS_CLASSGROUPS
    query.exec("CREATE TABLE IF NOT EXISTS teachers_classGroups (id INTEGER PRIMARY KEY AUTOINCREMENT, teacherID INTEGER, classGroupID INTEGER)");

    QVector<Teacher*> tmpTeachers;

    for(const QVariant &item : teachersList)
    {
        QVariantMap map = item.toMap();

        Teacher* newTeacher = new Teacher();
        newTeacher->setId(map["id"].toInt());
        newTeacher->setFirstName(map["firstName"].toString());
        newTeacher->setLastName(map["lastName"].toString());

        tmpTeachers.append(newTeacher);

        query.prepare("INSERT INTO teachers_classGroups (teacherID, classGroupID) VALUES (:teacherID, :classGroupID)");
        query.bindValue(":teacherID", map["id"].toInt());
        query.bindValue(":classGroupID", classGroupID);

        query.exec();
    }
    newClassGroup->setTeachers(tmpTeachers);

    m_classGroups.append(newClassGroup);
    downloadTeachers(); // najprostrza opcja mniej kodu, ponownie pobieranie danych z DB
    //emit classGroupsChanged();
}

void Containers::loadDataFromDB()
{
    downloadSubjects();
    downloadProfiles();
    downloadClassrooms();
    downloadTeachers();
    downloadClassGroups();

    downloadTimetableData();
}

void Containers::downloadSubjects()
{
    QSqlDatabase db = DatabaseManager::instance().getDB();
    QSqlQuery query(db);

    // Czyszczenie obecnych danych (unikamy duplikatów)
    qDeleteAll(m_subjects);
    m_subjects.clear();

    // Pobieranie danych z bazy
    query.exec("SELECT id, name, shortcut, type FROM subjects");

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString shortcut = query.value(2).toString();
        int type = query.value(3).toInt();

        Subject* newSubject = new Subject();
        newSubject->setId(id);
        newSubject->setName(name);
        newSubject->setShortcut(shortcut);
        newSubject->setType(type);

        m_subjects.append(newSubject);
    }

    emit subjectsChanged(); // Powiadomienie QML o zmianie danych
}

void Containers::downloadProfiles()
{
    QSqlDatabase db = DatabaseManager::instance().getDB();
    QSqlQuery query(db);

    qDeleteAll(m_profiles);
    m_profiles.clear();

    query.prepare(R"(
        SELECT id, name, classLevel
        FROM profiles
    )");
    query.exec();

    while(query.next())
    {
        Profile* newProfile = new Profile();
        newProfile->setId(query.value(0).toInt());
        newProfile->setName(query.value(1).toString());
        newProfile->setClassLevel(query.value(2).toInt());

        int profileID = query.value(0).toInt();

        QVector<Subject*> tmpSubjects;

        QSqlQuery querySub(db);
        querySub.prepare(R"(
        SELECT s.id, s.name, s.shortcut, s.type, ps.numberOfHours, ps.block, ps.availability
        FROM profiles_subjects ps
        JOIN subjects s ON ps.subjectID = s.id
        WHERE ps.profileID = :profileID
        )");

        querySub.bindValue(":profileID", profileID);
        querySub.exec();

        while (querySub.next()) {
            Subject* newSubject = new Subject();
            newSubject->setId(querySub.value(0).toInt());
            newSubject->setName(querySub.value(1).toString());
            newSubject->setShortcut(querySub.value(2).toString());
            newSubject->setType(querySub.value(3).toInt());
            newSubject->setNumberOfHours(querySub.value(4).toInt());
            newSubject->setBlock(querySub.value(5).toInt());
            newSubject->setAvailability(QJsonDocument::fromJson(querySub.value(6).toString().toUtf8()).array().toVariantList());

            tmpSubjects.append(newSubject);
        }

        newProfile->setSubjectList(tmpSubjects);

        m_profiles.append(newProfile);
    }
    emit profilesChanged();
}

void Containers::downloadClassrooms()
{
    QSqlDatabase db = DatabaseManager::instance().getDB();
    QSqlQuery query(db);

    // Czyszczenie obecnych danych (unikamy duplikatów)
    qDeleteAll(m_classrooms);
    m_classrooms.clear();

    // Pobieranie danych z bazy
    query.exec("SELECT id, name, type, availability FROM classrooms");

    while (query.next()) {
        Classroom* newClassroom = new Classroom();
        newClassroom->setId(query.value(0).toInt());
        newClassroom->setName(query.value(1).toString());
        newClassroom->setType(query.value(2).toInt());
        newClassroom->setAvailability(QJsonDocument::fromJson(query.value(3).toString().toUtf8()).array().toVariantList());

        m_classrooms.append(newClassroom);
    }
    emit classroomsChanged(); // Powiadomienie QML o zmianie danych
}

void Containers::downloadTeachers()
{
    QSqlDatabase db = DatabaseManager::instance().getDB();
    QSqlQuery query(db);

    // Czyszczenie obecnych danych (unikamy duplikatów)
    qDeleteAll(m_teachers);
    m_teachers.clear();

    query.prepare(R"(
        SELECT id, firstName, lastName, availability
        FROM teachers
    )");
    query.exec();

    while(query.next())
    {
        Teacher* newTeacher = new Teacher();
        newTeacher->setId(query.value(0).toInt());
        newTeacher->setFirstName(query.value(1).toString());
        newTeacher->setLastName(query.value(2).toString());
        newTeacher->setAvailability(QJsonDocument::fromJson(query.value(3).toString().toUtf8()).array().toVariantList());

        int teacherID = query.value(0).toInt();

        // specjalization
        QVector<Subject*> tmpSubjects;

        QSqlQuery querySub(db);
        querySub.prepare(R"(
            SELECT s.id, s.name, s.shortcut, s.type
            FROM teachers_subjects ts
            JOIN subjects s ON ts.subjectID = s.id
            WHERE ts.teacherID = :teacherID
        )");

        querySub.bindValue(":teacherID", teacherID);
        querySub.exec();

        while(querySub.next())
        {
            Subject* newSubject = new Subject();
            newSubject->setId(querySub.value(0).toInt());
            newSubject->setName(querySub.value(1).toString());
            newSubject->setShortcut(querySub.value(2).toString());
            newSubject->setType(querySub.value(3).toInt());

            tmpSubjects.append(newSubject);
        }
        newTeacher->setSpecjalization(tmpSubjects);

        // taughtClasses
        QVector<ClassGroup*> tmpClassGroup;

        QSqlQuery queryGroup(db);
        queryGroup.prepare(R"(
            SELECT cg.id, cg.name
            FROM teachers_classGroups tcg
            JOIN classGroups cg ON tcg.classGroupID = cg.id
            WHERE tcg.teacherID = :teacherID
        )");

        queryGroup.bindValue(":teacherID", teacherID);
        queryGroup.exec();

        while(queryGroup.next())
        {
            ClassGroup* newClassGroup = new ClassGroup();
            newClassGroup->setId(queryGroup.value(0).toInt());
            newClassGroup->setName(queryGroup.value(1).toString());

            tmpClassGroup.append(newClassGroup);
        }
        newTeacher->setTaughtClasses(tmpClassGroup);

        // availableClassrooms
        QVector<Classroom*> tmpClassrooms;

        QSqlQuery queryRoom(db);
        queryRoom.prepare(R"(
            SELECT r.id, r.name
            FROM teachers_classrooms tc
            JOIN classrooms r ON tc.classroomID = r.id
            WHERE tc.teacherID = :teacherID
        )");

        queryRoom.bindValue(":teacherID", teacherID);
        queryRoom.exec();

        while(queryRoom.next())
        {
            Classroom* newClassroom = new Classroom();
            newClassroom->setId(queryRoom.value(0).toInt());
            newClassroom->setName(queryRoom.value(1).toString());

            tmpClassrooms.append(newClassroom);
        }
        newTeacher->setAvailableClassrooms(tmpClassrooms);

        m_teachers.append(newTeacher);
    }
    emit teachersChanged();
}

void Containers::downloadClassGroups()
{
    QSqlDatabase db = DatabaseManager::instance().getDB();
    QSqlQuery query(db);

    qDeleteAll(m_classGroups);
    m_classGroups.clear();

    query.prepare(R"(
        SELECT id, name, profileID, classTeacherID, fixedLessonStartTime
        FROM classGroups
    )");
    query.exec();

    while(query.next())
    {
        ClassGroup* newClassGroup = new ClassGroup();
        newClassGroup->setId(query.value(0).toInt());
        newClassGroup->setName(query.value(1).toString());
        newClassGroup->setProfileID(query.value(2).toInt());
        newClassGroup->setClassTeacherID(query.value(3).toInt());
        newClassGroup->setFixedLessonStartTime(query.value(4).toInt());

        int classGroupID = query.value(0).toInt();

        // classGroupTeachers
        QVector<Teacher*> tmpTeachers;

        QSqlQuery queryTeacher(db); //w ag porównujemy tylko id więc reszta danych zbedna
        queryTeacher.prepare(R"(
            SELECT t.id
            FROM teachers_classGroups tcg
            JOIN teachers t ON tcg.teacherID = t.id
            WHERE tcg.classGroupID = :classGroupID
        )");

        queryTeacher.bindValue(":classGroupID", classGroupID);
        queryTeacher.exec();

        while(queryTeacher.next())
        {
            Teacher* newTeacher = new Teacher();
            newTeacher->setId(queryTeacher.value(0).toInt());

            int teacherID = queryTeacher.value(0).toInt();

            QSqlQuery querySpec(db);

            querySpec.prepare("SELECT subjectID FROM teachers_subjects WHERE teacherID = :teacherID");
            querySpec.bindValue(":teacherID", teacherID);
            querySpec.exec();

            QVector<Subject*> tmpSpec;

            while(querySpec.next())
            {
                Subject* newSubject = new Subject();
                newSubject->setId(querySpec.value(0).toInt());
                tmpSpec.append(newSubject);
            }
            newTeacher->setSpecjalization(tmpSpec);

            QSqlQuery queryRoom(db);

            queryRoom.prepare("SELECT classroomID FROM teachers_classrooms WHERE teacherID = :teacherID");
            queryRoom.bindValue(":teacherID", teacherID);
            queryRoom.exec();

            QVector<Classroom*> tmpClassroom;

            while(queryRoom.next())
            {
                Classroom* newClassroom = new Classroom();
                newClassroom->setId(queryRoom.value(0).toInt());
                tmpClassroom.append(newClassroom);
            }
            newTeacher->setAvailableClassrooms(tmpClassroom);

            tmpTeachers.append(newTeacher);
        }
        newClassGroup->setTeachers(tmpTeachers);

        m_classGroups.append(newClassGroup);
    }
    emit classGroupsChanged();
}

// void Containers::downloadTimetableData()
// {
//     QSqlDatabase db = DatabaseManager::instance().getDB();

//     QSqlQuery query(db);

//     query.exec("SELECT id, name, timetableData FROM timetables");



//     while(query.next()) {
//         int id = query.value(0).toInt();
//         QString name = query.value(1).toString();
//         std::string timeTable = query.value(2).toString().toStdString();

//         Timetable* newTimetable = new Timetable();
//         newTimetable->setId(id);
//         newTimetable->setName(name);

//         //QString timeTable = query.value(0).toString();

//         QList<QString> timetableVector;

//         //while(query.next()) {
//             //QString timeTable = query.value(0).toString();
//             std::stringstream ssWeek(timeTable);
//             std::string tmpDay;
//             QString newWeek = "";
//             while(std::getline(ssWeek, tmpDay, '\n')){
//                 std::stringstream ssDay(tmpDay);
//                 std::string tmpHour;
//                 QString newDay = "";
//                 while(std::getline(ssDay, tmpHour, ',')){
//                     int sID, tID, rID;
//                     size_t delimiter_1 = tmpHour.find(':');
//                     size_t delimiter_2 = tmpHour.find(';');
//                     if(delimiter_1 != std::string::npos){
//                         sID = std::stoi(tmpHour.substr(0, delimiter_1));
//                     }
//                     if(delimiter_1 != std::string::npos && delimiter_2 != std::string::npos){
//                         tID = std::stoi(tmpHour.substr(delimiter_1 + 1, delimiter_2 - delimiter_1 - 1));
//                     }
//                     if(delimiter_2 != std::string::npos){
//                         rID = std::stoi(tmpHour.substr(delimiter_2 + 1));
//                     }

//                     QSqlQuery subjectQuery(db);

//                     subjectQuery.prepare("SELECT name, shortcut FROM subjects WHERE id = :sid");
//                     subjectQuery.bindValue(":sid", sID);
//                     subjectQuery.exec();

//                     QString subjectName;
//                     QString shortcut;

//                     while(subjectQuery.next()){
//                         subjectName = subjectQuery.value(0).toString();
//                         shortcut = subjectQuery.value(1).toString();
//                     }

//                     QSqlQuery teacherQuery(db);

//                     teacherQuery.prepare("SELECT firstName, lastName FROM teachers WHERE id = :tid");
//                     teacherQuery.bindValue(":tid", tID);
//                     teacherQuery.exec();

//                     QString firstName;
//                     QString lastName;

//                     while(teacherQuery.next()){
//                         firstName = teacherQuery.value(0).toString();
//                         lastName = teacherQuery.value(1).toString();
//                     }

//                     QSqlQuery classroomQuery(db);

//                     classroomQuery.prepare("SELECT name FROM classrooms WHERE id = :rid");
//                     classroomQuery.bindValue(":rid", rID);
//                     classroomQuery.exec();

//                     QString classroomName;

//                     while(classroomQuery.next()){
//                         classroomName = classroomQuery.value(0).toString();
//                     }

//                     newDay += shortcut + ":" + firstName + " " + lastName + ";" + classroomName + ",";
//                 }
//                 newWeek += newDay + "\n";
//             }
//             timetableVector.append(newWeek);
//         //}
//         newTimetable->setTimetableData(timetableVector);
//         m_timetables.append(newTimetable);
//     }

//     //m_timetableData = timetableVector;
//     emit timetablesChanged();
// }





void Containers::downloadTimetableData()
{
    QSqlDatabase db = DatabaseManager::instance().getDB();
    QSqlQuery query(db);

    qDeleteAll(m_timetables);
    m_timetables.clear();

    if (!query.exec("SELECT id, name, timetableData FROM timetables")) {
        qWarning() << "Błąd zapytania SQL:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString timeTable = query.value(2).toString();  // Już w QString

        // Tworzymy nowy obiekt Timetable
        Timetable* newTimetable = new Timetable();
        newTimetable->setId(id);
        newTimetable->setName(name);

        QList<QString> timetableVector;
        QStringList ClassGroupTT = timeTable.split("|", Qt::SkipEmptyParts);

        for (const QString& classGroup : ClassGroupTT) {
            QStringList weekDays = classGroup.split("\n", Qt::SkipEmptyParts);//QStringList weekDays = timeTable.split("\n", Qt::SkipEmptyParts);
            QString newWeek = ""; //zm

            for (const QString& day : weekDays) {
                QStringList hours = day.split(",", Qt::SkipEmptyParts);
                QString newDay = "";

                // for (const QString& hour : hours) {
                //     QStringList lessonParts = hour.split(":");
                //     if (lessonParts.size() < 2) continue;  // Brak wystarczających danych

                //     int sID = lessonParts[0].toInt();
                //     QStringList teacherAndRoom = lessonParts[1].split(";");
                //     int tID = teacherAndRoom.size() > 0 ? teacherAndRoom[0].toInt() : -1;
                //     int rID = teacherAndRoom.size() > 1 ? teacherAndRoom[1].toInt() : -1;

                //     // Pobranie danych z bazy
                //     QString shortcut = getSubjectShortcut(db, sID);
                //     QString teacherName = getTeacherName(db, tID);
                //     QString classroomName = getClassroomName(db, rID);

                //     newDay += shortcut + ":" + teacherName + ";" + classroomName + ",";
                // }
                for (const QString& hour : hours) {
                    QStringList lessonParts = hour.split(":");
                    if (lessonParts.size() < 2) continue;  // Brak wystarczających danych

                    int sID = lessonParts[0].toInt();
                    QStringList teacherAndRoom = lessonParts[1].split(";");
                    if (teacherAndRoom.size() < 2) continue;  // Brak sali lekcyjnej

                    int tID = teacherAndRoom[0].toInt();
                    QStringList roomAndGroup = teacherAndRoom[1].split("#");
                    int rID = roomAndGroup.size() > 0 ? roomAndGroup[0].toInt() : -1;
                    int cGroupID = roomAndGroup.size() > 1 ? roomAndGroup[1].toInt() : -1;

                    // Pobranie danych z bazy
                    QString shortcut = getSubjectShortcut(db, sID);
                    QString teacherName = getTeacherName(db, tID);
                    QString classroomName = getClassroomName(db, rID);
                    QString classGroupName = getClassGroupName(db, cGroupID);

                    newDay += shortcut + ":" + teacherName + ";" + classroomName + "#" + classGroupName + ",";
                }
                newWeek += newDay + "\n";
            }
            timetableVector.append(newWeek);
        }
        newTimetable->setTimetableData(timetableVector);
        m_timetables.append(newTimetable);
    }

    emit timetablesChanged();
}

void Containers::saveToPDF(const QUrl &fileUrl, QQuickItem *item)
{
    QString filePath = fileUrl.toLocalFile();  // Konwersja QUrl do QString
    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive))
        filePath += ".pdf";

    QSharedPointer<QQuickItemGrabResult> grabResult = item->grabToImage();

    QObject::connect(grabResult.data(), &QQuickItemGrabResult::ready, [filePath, grabResult]() {
        QImage img = grabResult->image();
        if (!img.isNull()) {
            QPdfWriter pdfWriter(filePath);

            // Ustawienie poziomej orientacji strony A4
            pdfWriter.setPageSize(QPageSize(QPageSize::A4));
            QPageLayout layout = pdfWriter.pageLayout();
            layout.setOrientation(QPageLayout::Landscape);  // Ustawienie na poziomą orientację
            pdfWriter.setPageLayout(layout);

            pdfWriter.setResolution(300); // 300 DPI dla wysokiej jakości
            QSizeF pageSize = pdfWriter.pageLayout().fullRectPoints().size();

            int pdfWidth = int(pageSize.width() * pdfWriter.resolution() / 74.0);
            int pdfHeight = int(pageSize.height() * pdfWriter.resolution() / 74.0);

            QPainter pdfPainter(&pdfWriter);

            img = img.scaled(pdfWidth, pdfHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            pdfPainter.drawImage(QRect(0, 0, pdfWidth, pdfHeight), img);

            pdfPainter.end();

            qDebug() << "Zapisano fragment do pliku PDF w orientacji poziomej:" << filePath;
        } else {
            qWarning() << "Nie udało się uchwycić obrazu komponentu!";
        }
    });
}

void Containers::deleteSubject(int id)
{

}

void Containers::deleteProfile(int id)
{

}

void Containers::deleteClassroom(int id)
{

}

void Containers::deleteTeacher(int id)
{

}

void Containers::deleteClassGroup(int id)
{

}

void Containers::deleteTimetableData(int id)
{
    QSqlDatabase db = DatabaseManager::instance().getDB();

    QSqlQuery query(db);
    query.prepare("DELETE FROM timetables WHERE id = :id");
    query.bindValue(":id", id);
    query.exec();
}

// Pomocnicze funkcje SQL
QString Containers::getSubjectShortcut(QSqlDatabase& db, int subjectID) {
    if (subjectID < 0) return "N/A";

    QSqlQuery query(db);
    query.prepare("SELECT shortcut FROM subjects WHERE id = :sid");
    query.bindValue(":sid", subjectID);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}

QString Containers::getTeacherName(QSqlDatabase& db, int teacherID) {
    if (teacherID < 0) return "N/A";

    QSqlQuery query(db);
    query.prepare("SELECT firstName, lastName FROM teachers WHERE id = :tid");
    query.bindValue(":tid", teacherID);
    if (query.exec() && query.next()) {
        return query.value(0).toString() + " " + query.value(1).toString();
    }
    return "";
}

QString Containers::getClassroomName(QSqlDatabase& db, int classroomID) {
    if (classroomID < 0) return "N/A";

    QSqlQuery query(db);
    query.prepare("SELECT name FROM classrooms WHERE id = :rid");
    query.bindValue(":rid", classroomID);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}

QString Containers::getClassGroupName(QSqlDatabase &db, int classGroupID)
{
    if (classGroupID < 0) return "N/A";

    QSqlQuery query(db);
    query.prepare("SELECT name FROM classGroups WHERE id = :cgid");
    query.bindValue(":cgid", classGroupID);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}










// void Containers::downloadTimetableData()
// {
//     QSqlDatabase db = DatabaseManager::instance().getDB();
//     QSqlQuery query(db);

//     query.exec("SELECT id, name, timetableData FROM timetables");

//     while (query.next()) {
//         int id = query.value(0).toInt();
//         QString name = query.value(1).toString();
//         QString rawTimetableData = query.value(2).toString();

//         Timetable* newTimetable = new Timetable();
//         newTimetable->setId(id);
//         newTimetable->setName(name);

//         // Podział na plany dla poszczególnych klas (według '|')
//         QStringList classTimetables = rawTimetableData.split('|', Qt::SkipEmptyParts);

//         for (const QString& classData : classTimetables) {


//             QList<QString> timetableVector;

//             std::stringstream ssWeek(classData.toStdString());
//             std::string tmpDay;
//             QString newWeek = "";

//             while (std::getline(ssWeek, tmpDay, '\n')) {
//                 std::stringstream ssDay(tmpDay);
//                 std::string tmpHour;
//                 QString newDay = "";

//                 while (std::getline(ssDay, tmpHour, ',')) {
//                     int sID = 0, tID = 0, rID = 0;
//                     size_t delimiter_1 = tmpHour.find(':');
//                     size_t delimiter_2 = tmpHour.find(';');

//                     if (delimiter_1 != std::string::npos) {
//                         sID = std::stoi(tmpHour.substr(0, delimiter_1));
//                     }
//                     if (delimiter_1 != std::string::npos && delimiter_2 != std::string::npos) {
//                         tID = std::stoi(tmpHour.substr(delimiter_1 + 1, delimiter_2 - delimiter_1 - 1));
//                     }
//                     if (delimiter_2 != std::string::npos) {
//                         rID = std::stoi(tmpHour.substr(delimiter_2 + 1));
//                     }

//                     QSqlQuery subjectQuery(db);
//                     subjectQuery.prepare("SELECT subjectName, shortcut FROM subjects WHERE id = :sid");
//                     subjectQuery.bindValue(":sid", sID);
//                     subjectQuery.exec();

//                     QString subjectName, shortcut;
//                     if (subjectQuery.next()) {
//                         subjectName = subjectQuery.value(0).toString();
//                         shortcut = subjectQuery.value(1).toString();
//                     }

//                     QSqlQuery teacherQuery(db);
//                     teacherQuery.prepare("SELECT firstName, lastName FROM teachers WHERE id = :tid");
//                     teacherQuery.bindValue(":tid", tID);
//                     teacherQuery.exec();

//                     QString firstName, lastName;
//                     if (teacherQuery.next()) {
//                         firstName = teacherQuery.value(0).toString();
//                         lastName = teacherQuery.value(1).toString();
//                     }

//                     QSqlQuery classroomQuery(db);
//                     classroomQuery.prepare("SELECT classroomName FROM classrooms WHERE id = :rid");
//                     classroomQuery.bindValue(":rid", rID);
//                     classroomQuery.exec();

//                     QString classroomName;
//                     if (classroomQuery.next()) {
//                         classroomName = classroomQuery.value(0).toString();
//                     }

//                     newDay += shortcut + ":" + firstName + " " + lastName + ";" + classroomName + ",";
//                 }

//                 newWeek += newDay + "\n";
//             }

//             timetableVector.append(newWeek);
//             newTimetable->setTimetableData(timetableVector);
//         }
//         m_timetables.append(newTimetable);
//     }

//     emit timetablesChanged();
// }
