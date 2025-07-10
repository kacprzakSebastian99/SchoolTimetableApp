#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QQmlEngine>
#include <QObject>
#include <QVariantList>
#include <iostream>
#include <sstream>
#include <string>
// #include <fstream>
#include "individual.h"
#include "timetable.h"
#include "gene.h"
#include "containers.h"

// #include "../DBModule/src/containers.h"

#define POPULATION_SIZE 40 // population must be even // 40

bool operator<(const Individual &ind1, const Individual &ind2);

using vectorGene3D_t = std::vector<std::vector<std::vector<Gene>>>;
using vectorGene2D_t = std::vector<std::vector<Gene>>;

class GeneticAlgorithm : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(vectorGene3D_t genes READ genes WRITE setGenes NOTIFY genesChanged FINAL)
    Q_PROPERTY(vectorGene3D_t initialGenes READ getInitialGenes WRITE setInitialGenes NOTIFY initialGenesChanged FINAL)
    Q_PROPERTY(chromosome_t timetableData READ timetableData NOTIFY timetableDataChanged FINAL)

public:
    GeneticAlgorithm();

    int random_num(int start, int end);
    vectorGene3D_t create_genes(const Containers &classesData);
    chromosome_t create_gnome(const Containers &classesData);

    Q_INVOKABLE void geneticAlgorithmRun(const QString &newTimetableName);
    // Q_INVOKABLE void geneticAlgorithmRun(const Containers &classesData);
    // chromosome_t backtracking(chromosome_t cuttentBest);

    vectorGene3D_t genes() const;
    void setGenes(const vectorGene3D_t &newGenes);

    vectorGene3D_t getInitialGenes() const;
    void setInitialGenes(const vectorGene3D_t &newInitialGenes);

    // QQmlListProperty<chromosome_t> timetableVector();
    chromosome_t timetableData() const;
    void setTimetableData(const QString &newName, const chromosome_t &newTimetableData);



signals:

    void genesChanged();
    void initialGenesChanged();

    void timetableDataChanged();

private:
    vectorGene3D_t m_genes;
    vectorGene3D_t m_initialGenes;
    chromosome_t m_timetableData;
};

#endif // GENETICALGORITHM_H
