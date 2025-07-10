#include "geneticalgorithm.h"
#include "individual.h"
#include "timetable.h"
#include "../DBModule/src/containers.h"
#include "../DataEntry/src/classgroup.h"
#include "../DataEntry/src/classroom.h"
#include "../DataEntry/src/profile.h"
#include "../DataEntry/src/subject.h"
#include "../DataEntry/src/teacher.h"
#include <iostream>
#include <chrono>
#include <iomanip>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVariantList>
#include <QString>
#include "../DBModule/src/databasemanager.h"

GeneticAlgorithm::GeneticAlgorithm() {}

bool operator<(const Individual &ind1, const Individual &ind2)
{
    // return ind1.fitness() < ind2.fitness() && //ind1.subjectFitness() < ind2.subjectFitness() &&
        // ind1.distributionFitness() < ind2.distributionFitness();
    // return ind1.fitness() < ind2.fitness() && ind1.subjectFitness() < ind2.subjectFitness();
    return ind1.fitness() < ind2.fitness();
}

int GeneticAlgorithm::random_num(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (rand()%range);
    return random_int;
}

vectorGene3D_t GeneticAlgorithm::create_genes(const Containers &classesData)
{
    size_t classGroupSize = classesData.getClassGroups().size();
    vectorGene3D_t Genes; // klasy
    vectorGene2D_t subjectVector; // przedmioty
    std::vector<Gene> classroomVector; // sale
    Gene newGene, emptyGene;
    // emptyGene.subjectID = 0;
    // emptyGene.teacherID = 0;
    // emptyGene.classroomID = 0;


    // INITIAL GENES 1
    vectorGene3D_t initGenes(classGroupSize);

    for(int c = 0; c < classGroupSize; ++c)
    {
        newGene.classGroupID = classesData.getClassGroups()[c]->id();
        int profileID = classesData.getClassGroups()[c]->profileID();
        const Profile* classGroupProfile = nullptr;
        for(const Profile* p : classesData.getProfiles())
        {
            if(p->id() == profileID)
            {
                classGroupProfile = p;
                break;
            }
        }

        int subjectListSize = classGroupProfile->getSubjectsList().size();
        int teacherListSize = classesData.getClassGroups()[c]->getTeachers().size();
        // qDebug() << "TSIZE: " << teacherListSize << "SSIZE: " << subjectListSize;
        // INITIAL GENES 2
        initGenes[c].resize(subjectListSize);

        for(int s = 0; s < subjectListSize; ++s)
        {
            newGene.subjectID = classGroupProfile->getSubjectsList()[s]->id();
            // qDebug() << "SID: " << newGene.subjectID;
            for(int t = 0; t < teacherListSize; ++t)
            {
                for(const auto& sp : classesData.getClassGroups()[c]->getTeachers()[t]->getSpecjalization())
                {
                    if(sp->id() == newGene.subjectID)
                    {
                        newGene.teacherID = classesData.getClassGroups()[c]->getTeachers()[t]->id();
                        // qDebug() << "TID: " << newGene.teacherID;
                        for(const auto& r : classesData.getClassGroups()[c]->getTeachers()[t]->getAvailableClassrooms())
                        {
                            newGene.classroomID = r->id();
                            classroomVector.push_back(newGene);
                            // qDebug() << "CID: " << newGene.classroomID;
                        }
                        // INITIAL GENES 3
                        newGene.classroomID = classesData.getClassGroups()[c]->getTeachers()[t]->getAvailableClassrooms().first()->id();
                        for(int i = 0; i < classGroupProfile->getSubjectsList()[s]->numberOfHours(); ++i)
                        {
                            initGenes[c][s].push_back(newGene);
                        }
                    }
                }
            }
            subjectVector.push_back(classroomVector);
            classroomVector.clear();
        }
        emptyGene.classGroupID = classesData.getClassGroups()[c]->id();
        for(size_t eg = 0; eg < 3; ++eg)
            subjectVector.push_back(std::vector<Gene>(1, emptyGene));
        Genes.push_back(subjectVector);
        subjectVector.clear();
    }
    setInitialGenes(initGenes);
    // debug print
    qDebug() << "INITGENES_SIZE: ";// << initGenes.size() << " " << initGenes[0].size() << " " << initGenes[0][0].size();
    std::vector<int> capacity(initGenes.size(), 0);
    for(int i = 0; i < initGenes.size(); i++)
        for(int j = 0; j < initGenes[i].size(); j++)
            for(int k = 0; k < initGenes[i][j].size(); k++)
                capacity[i] += 1;
    for(int l = 0; l < initGenes.size(); l++)
        std::cout << capacity[l] << std::endl;

    //setInitialGenes(Genes);
    return Genes;
}

chromosome_t GeneticAlgorithm::create_gnome(const Containers &classesData)
{
    chromosome_t gnome;
    size_t classGroupSize = classesData.getClassGroups().size();
    gnome.resize(classGroupSize);
    for(size_t c = 0; c < classGroupSize; ++c)
    {
        gnome[c].resize(DAYS_SIZE);
        for(size_t d = 0; d < DAYS_SIZE; ++d)
            gnome[c][d].resize(HOURS_SIZE);
    }

    Gene emptyGene;
    std::vector<int> distributionPerDay(classGroupSize);
    vectorGene3D_t initGenes = getInitialGenes();



    for(size_t c = 0; c < classGroupSize; ++c)
    {
        emptyGene.classGroupID = classesData.getClassGroups()[c]->id(); //
        int weekHours = 0;// = initGenes[c].size();

        for(size_t s = 0; s < initGenes[c].size(); ++s)
        {
            for(size_t cr = 0; cr < initGenes[c][s].size(); ++cr)
            {
                weekHours++;
            }
        }

        int modulo = weekHours % DAYS_SIZE;
        // qDebug() << "WEEKHOURS_MODULO: " << weekHours << " / " << modulo;
        for(size_t i = 0; i < DAYS_SIZE; ++i)
        {
            distributionPerDay[i] = (weekHours - modulo) / DAYS_SIZE;
        }
        for(size_t j = 0; j < modulo; ++j)
        {
            int r = random_num(0, 4);
            distributionPerDay[r] += 1;
        }

        for(size_t d = 0; d < DAYS_SIZE; ++d)
        {
            for(size_t h = 0; h < HOURS_SIZE; ++h)
            {
                if(h < distributionPerDay[d] && !initGenes[c].empty())
                {
                    int r = random_num(0, initGenes[c].size() - 1);
                    gnome[c][d][h] = initGenes[c][r].front();
                    initGenes[c][r].erase(initGenes[c][r].begin());
                    if(initGenes[c][r].empty())
                    {
                        initGenes[c].erase(initGenes[c].begin() + r);
                    }
                }
                else
                    gnome[c][d][h] = emptyGene;
            }
        }
    }
    return gnome;
}

void GeneticAlgorithm::geneticAlgorithmRun(const QString &newTimetableName)
{
    Containers &classesData = Containers::instance();

    auto start = std::chrono::high_resolution_clock::now();

    srand((unsigned)(time(0)));

    vectorGene3D_t Genes = create_genes(classesData);

    int generation = 0;

    std::vector<Individual> population;

    bool found = false;

    // Stagnation 1
    // const int stagnationLimit = 100;//10
    // const int resetPercentage = 0;//70
    // int stagnationCounter;
    // int bestFitnessInLastGeneration = INT_MAX;
    int lowestFitness = 500;

    // Create initial population
    for(int p = 0; p < POPULATION_SIZE; ++p)
    {
        chromosome_t gnome = create_gnome(classesData);
        population.push_back(Individual(gnome, classesData));
        std::cout << "Inicjalization of the population: " << p << std::endl;
    }

    while(!found)
    {
        sort(population.begin(), population.end());

        if(population[0].fitness() <= 0) //0
        {
            found = true;
            break;
        }

        // Stagnation 2
        // if(population[0].fitness() < bestFitnessInLastGeneration)
        // {
        //     bestFitnessInLastGeneration = population[0].fitness();
        //     stagnationCounter = 0;
        // }
        // else
        //     ++stagnationCounter;

        // if(stagnationCounter >= stagnationLimit) {
        //     std::cout << "RESETTTING PART OF POPULATION." << std::endl;
        //     int resetCount = (resetPercentage * POPULATION_SIZE) / 100;
        //     for(int i = POPULATION_SIZE - resetCount; i < POPULATION_SIZE; ++i)
        //     {
        //         chromosome_t gnome = create_gnome(classesData);
        //         population[i] = Individual(gnome, classesData);
        //     }
        //     stagnationCounter = 0;
        // }

        std::vector<Individual> new_generation;

        // int e = population[0].fitness() > 40 ? 10 : 40;
        // int rp = population[0].fitness() > 40 ? 90 : 60;
        int e = 0;
        int rp = 0;

        if(population[0].fitness() > 40){
            e = 10;
            rp = 90;
        }
        else if(population[0].fitness() > 30){
            e = 30;
            rp = 70;
        }
        else if(population[0].fitness() > 20){
            e = 50;
            rp = 50;
        }
        else if(population[0].fitness() > 10){
            e = 70;
            rp = 30;
        }
        else if(population[0].fitness() >= 0){
            e = 85;//e = 90;
            rp = 15;//rp = 10;
        }

        int s = (e * POPULATION_SIZE) / 100;// 10
        for(int i = 0; i < s; ++i)
        {
            new_generation.push_back(population[i]);
            //std::cout << "Perform Elitism: " << i << " of " << s << std::endl;
        }

        s = (rp * POPULATION_SIZE) / 100;// 90
        for(int  i = 0; i < s; ++i)
        {
            // Stagnation 3
            if(population[i].fitness() < lowestFitness)
                lowestFitness = population[i].fitness();

            //draw limit
            int rMAX = POPULATION_SIZE - 1;
            // if(population[0].fitness() < 5)
            //     rMAX = (15 * POPULATION_SIZE) / 100;


            // Tournament Selection
            int tournamentSize = 3;
            Individual parent1 = population[random_num(0, population.size() - 1)];
            for(int i = 0; i < tournamentSize; ++i)
            {
                int r = random_num(0, rMAX);//int r = random_num(0, population.size() - 1);
                if(population[r].fitness() < parent1.fitness())
                    parent1 = population[r];
            }
            Individual parent2 = population[random_num(0, population.size() - 1)];
            for(int i = 0; i < tournamentSize; ++i)
            {
                int r = random_num(0, rMAX);//int r = random_num(0, population.size() - 1);
                if(population[r].fitness() < parent2.fitness())
                    parent2 = population[r];
            }

            {
            // Individual parent1 = population[0];
            // if(population[0].fitness() < 10)
            //     parent1 = population[0];
            // else
            // {
            //     parent1 = population[random_num(0, population.size() - 1)];
            //     for(int i = 0; i < tournamentSize; ++i)
            //     {
            //         int r = random_num(0, population.size() - 1);
            //         if(population[r].fitness() < parent1.fitness())
            //             parent1 = population[r];
            //     }
            // }
            // Individual parent2 = population[0];
            // if(population[0].fitness() != 1)
            // {
            //     parent2 = population[random_num(0, population.size() - 1)];
            //     for(int i = 0; i < tournamentSize; ++i)
            //     {
            //         int r = random_num(0, population.size() - 1);
            //         if(population[r].fitness() < parent2.fitness())
            //             parent2 = population[r];
            //     }
            // }
            // else
            //     parent2 = population[0];
            // if(population[0].fitness() == 1)
            //     parent2 = population[0];
            }
            Individual offspring = parent1.mate(parent2, Genes, classesData);
            new_generation.push_back(offspring);
            std::cout << "Creating of a new population: " << std::setw(2) << std::setfill('0') << i << " of " << s
                      << " GENERATION: " << generation << " LF: " << lowestFitness << std::endl;
        }
        // std::cout << " GENERATION: " << generation << " LF: " << lowestFitness << std::endl;
        population = new_generation;
        generation++;
    }
    setTimetableData(newTimetableName, population[0].chromosome());

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    int total_sec = duration.count();

    int hours = total_sec / 3600;
    int minutes = (total_sec % 3600) / 60;
    int seconds = total_sec % 60;

    std::cout << "TOTAL TIME: "
              << std::setw(2) << std::setfill('0') << hours << ":"
              << std::setw(2) << std::setfill('0') << minutes << ":"
              << std::setw(2) << std::setfill('0') << seconds << std::endl;

    // PRINT SOLUTION AS ARRAY OF ID
    std::cout << "GENERACJA: " << generation << " FOUND SOLUTION" << std::endl;
    std::cout << std::endl << "PLAN KLAS" << std::endl;
    std::cout << std::endl << "PRZEDMIOTY" << std::endl;
    for (int cf = 0; cf < 5; cf++) {
        std::cout << "KLASA: " << cf + 4 << std::endl;
        for (int cd = 0; cd < 5; cd++) {
            std::cout << "DZIEN: " << cd + 1 << " | ";
            for (int ch = 0; ch < 8; ch++) {
                std::cout << population[0].chromosome()[cf][cd][ch].subjectID << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "NAUCZYCIELE" << std::endl;
    for (int cf = 0; cf < 5; cf++) {
        std::cout << "KLASA: " << cf + 4 << std::endl;
        for (int cd = 0; cd < 5; cd++) {
            std::cout << "DZIEN: " << cd + 1 << " | ";
            for (int ch = 0; ch < 8; ch++) {
                std::cout << population[0].chromosome()[cf][cd][ch].teacherID << "  ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << "SALE" << std::endl;
    for (int cf = 0; cf < 5; cf++) {
        std::cout << "KLASA: " << cf + 4 << std::endl;
        for (int cd = 0; cd < 5; cd++) {
            std::cout << "DZIEN: " << cd + 1 << " | ";
            for (int ch = 0; ch < 8; ch++) {
                std::cout << population[0].chromosome()[cf][cd][ch].classroomID << "  ";
            }
        }
        std::cout << std::endl;
    }
}

// chromosome_t GeneticAlgorithm::backtracking(chromosome_t cuttentBest)
// {

// }

vectorGene3D_t GeneticAlgorithm::getInitialGenes() const
{
    return m_initialGenes;
}

void GeneticAlgorithm::setInitialGenes(const vectorGene3D_t &newInitialGenes)
{
    if (m_initialGenes == newInitialGenes)
        return;
    m_initialGenes = newInitialGenes;
    emit initialGenesChanged();
}

// QQmlListProperty<chromosome_t> GeneticAlgorithm::timetableVector()
// {
//     return QQmlListProperty<chromosome_t>(this,
//                                      &m_timetableData);//,
//                                      // &append,
//                                      // &count,
//                                      // &at,
//                                      // &clear,
//                                      // &replace,
//                                      // &removeLast);
// }


vectorGene3D_t GeneticAlgorithm::genes() const
{
    return m_genes;
}

void GeneticAlgorithm::setGenes(const vectorGene3D_t &newGenes)
{
    if (m_genes == newGenes)
        return;
    m_genes = newGenes;
    emit genesChanged();
}

chromosome_t GeneticAlgorithm::timetableData() const
{
    return m_timetableData;
}

void GeneticAlgorithm::setTimetableData(const QString &newName, const chromosome_t &newTimetableData)
{
    // if (m_timetableData == newTimetableData)
    //     return;

    std::string classGroupsTimeTable;

    // //classGroups
    // for(int c = 0; c < newTimetableData.size(); c++){
    //     std::string weekLine = "";
    //     for(int d = 0; d < newTimetableData[c].size(); d++){
    //         std::string dayLine = "";
    //         for(int h = 0; h < newTimetableData[c][d].size(); h++){
    //             dayLine += std::to_string(newTimetableData[c][d][h].subjectID) + ":" + std::to_string(newTimetableData[c][d][h].teacherID) + ";" + std::to_string(newTimetableData[c][d][h].classroomID) + ",";
    //         }
    //         weekLine += dayLine + "\n";
    //     }
    //     classGroupsTimeTable += weekLine + "|";
    // }

    //classGroups
    for(int c = 0; c < newTimetableData.size(); c++){
        std::string weekLine = "";
        for(int d = 0; d < newTimetableData[c].size(); d++){
            std::string dayLine = "";
            for(int h = 0; h < newTimetableData[c][d].size(); h++){
                dayLine += std::to_string(newTimetableData[c][d][h].subjectID) + ":" + std::to_string(newTimetableData[c][d][h].teacherID) + ";" + std::to_string(newTimetableData[c][d][h].classroomID) + "#" + std::to_string(newTimetableData[c][d][h].classGroupID);// + ",";
                if(h != newTimetableData[c][d].size() - 1)
                     dayLine += ",";
            }
            if(d != newTimetableData[c].size() - 1)
                weekLine += dayLine + "\n";
            else
                weekLine += dayLine;
        }
        if(c != newTimetableData.size() - 1)
            classGroupsTimeTable += weekLine + "|";
        else
            classGroupsTimeTable += weekLine;
    }

    QSqlDatabase db = DatabaseManager::instance().getDB();

    QSqlQuery query(db);

    query.exec("CREATE TABLE IF NOT EXISTS timetables (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, timetableData TEXT)");
    query.prepare("INSERT INTO timetables (name, timetableData) VALUES (:name, :timetableData)");

    query.bindValue(":name", newName);
    query.bindValue(":timetableData", QString::fromStdString(classGroupsTimeTable));
    query.exec();

    //m_timetableData = newTimetableData;
    //std::cout << "SIZE: " << m_timetableData.size() << std::endl;
    emit timetableDataChanged();
}


























