#include "databasemanager.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager() {}

DatabaseManager::~DatabaseManager()
{
    if(db.isOpen())
        db.close();
}

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

void DatabaseManager::connectDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("PDdatabase.db");
    if(db.open())
        qDebug() << "Connected to the database.";
    else
        qDebug() << "Failed to connect to the database: " << db.lastError().text();
}

void DatabaseManager::closeDB()
{
    if(db.isOpen())
    {
        db.close();
        qDebug() << "Database closed.";
    }
}

QSqlDatabase &DatabaseManager::getDB()
{
    return db;
}

