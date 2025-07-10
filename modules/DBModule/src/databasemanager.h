#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
public:
    static DatabaseManager& instance();
    void connectDB();
    void closeDB();
    QSqlDatabase& getDB();

    DatabaseManager();
    ~DatabaseManager();
private:
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
