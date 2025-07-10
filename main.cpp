#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "modules/DBModule/src/databasemanager.h"
#include "modules/DBModule/src/containers.h"
#include "modules/Timetable/src/geneticalgorithm.h"
#include "modules/Timetable/src/gene.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    DatabaseManager db;
    db.connectDB();

    Containers& containers = Containers::instance();

    QQmlApplicationEngine engine;
    engine.addImportPath(QString("%1/modules")
                             .arg(QGuiApplication::applicationDirPath()));

    qmlRegisterSingletonInstance<Containers>("DBModule", 1, 0, "Containers", &Containers::instance());

    qmlRegisterType<GeneticAlgorithm>("Timetable", 1, 0, "GeneticAlgorithm");
    qmlRegisterType<Gene>("Gene", 1, 0, "Gene");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("PDv2", "Main");

    return app.exec();
}
