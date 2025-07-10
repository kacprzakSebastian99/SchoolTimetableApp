#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H


#include <QQmlEngine>
#include <utility>
#include <tuple>
#include "gene.h"
// #include "../DataEntry/src/classgroup.h"
// #include "../DataEntry/src/profile.h"
// #include "../DataEntry/src/classroom.h"
// #include "../DBModule/src/containers.h"

#define DAYS_SIZE 5
#define HOURS_SIZE 8 // pozniej pobrac z klasy timetable wartosc zamiast tego

// class ClassGroup;
// class Profile;
// class Classroom;
class Containers;

class Individual
{
    QML_ELEMENT
    Q_PROPERTY(chromosome_t chromosome READ chromosome WRITE setChromosome NOTIFY chromosomeChanged FINAL)
    Q_PROPERTY(int fitness READ fitness WRITE setFitness NOTIFY fitnessChanged FINAL)
    Q_PROPERTY(int subjectFitness READ subjectFitness WRITE setSubjectFitness NOTIFY subjectFitnessChanged FINAL)
    Q_PROPERTY(int teacherFitness READ teacherFitness WRITE setTeacherFitness NOTIFY teacherFitnessChanged FINAL)
    Q_PROPERTY(int classroomFitness READ classroomFitness WRITE setClassroomFitness NOTIFY classroomFitnessChanged FINAL)
    Q_PROPERTY(int windowFitness READ windowFitness WRITE setWindowFitness NOTIFY windowFitnessChanged FINAL)
    Q_PROPERTY(int distributionFitness READ distributionFitness WRITE setDistributionFitness NOTIFY distributionFitnessChanged FINAL)
    Q_PROPERTY(int blockFitness READ blockFitness WRITE setBlockFitness NOTIFY blockFitnessChanged FINAL)
    Q_PROPERTY(int availabilityFitness READ availabilityFitness WRITE setAvailabilityFitness NOTIFY availabilityFitnessChanged FINAL)
    Q_PROPERTY(std::vector<std::vector<int>> missingSubjects READ missingSubjects WRITE setMissingSubjects NOTIFY missingSubjectsChanged FINAL)
    // Q_PROPERTY(std::vector<std::tuple<int, int, int, Gene>> mismatches READ mismatches WRITE setMismatches NOTIFY mismatchesChanged FINAL)
public:
    Individual(chromosome_t chromosome, const Containers &classesData);
    chromosome_t chromosome() const;
    void setChromosome(const chromosome_t &newChromosome);
    int fitness() const;
    void setFitness(int newFitness);

    int subjectFitness() const;
    void setSubjectFitness(int newSubjectFitness);

    int teacherFitness() const;
    void setTeacherFitness(int newTeacherFitness);

    int classroomFitness() const;
    void setClassroomFitness(int newClassroomFitness);

    int windowFitness() const;
    void setWindowFitness(int newWindowFitness);

    int distributionFitness() const;
    void setDistributionFitness(int newDistributionFitness);

    int blockFitness() const;
    void setBlockFitness(int newBlockFitness);

    int availabilityFitness() const;
    void setAvailabilityFitness(int newAvailabilityFitness);

    std::vector<std::vector<int>> missingSubjects() const;
    void setMissingSubjects(const std::vector<std::vector<int>> &newMissingSubjects);

    int cal_fitness(const Containers &classesData);
    std::tuple<int, int, std::vector<int>> cal_subject_block_fitness(const Containers &classesData, const int &classGroupProfileID, std::vector<std::tuple<int, int, int>> subjectLocation);//const std::unordered_map<int, std::pair<int, int>> &subjectCounter);
    int random_num(int start, int end);
    Gene mutated_genes(const std::vector<int> &missingSubjects, const std::vector<std::vector<Gene>> &classGroupGenes);
    Individual mate(Individual parent2, const std::vector<std::vector<std::vector<Gene>>> &Genes, const Containers &classesData);


    // chromosome_t resetDistribution(const Containers &classesData, chromosome_t &ind);

    // std::vector<std::tuple<int, int, int, Gene> > mismatches() const;
    // void setMismatches(const std::vector<std::tuple<int, int, int, Gene> > &newMismatches);

// signals:
//     void mismatchesChanged();

signals:
    void availabilityFitnessChanged();

private:
    chromosome_t m_chromosome;
    int m_fitness;
    int m_subjectFitness;
    int m_teacherFitness;
    int m_classroomFitness;
    int m_windowFitness;
    int m_distributionFitness;
    int m_blockFitness;
    int m_availabilityFitness;
    std::vector<std::vector<int > > m_missingSubjects;
    // std::vector<std::tuple<int, int, int, Gene> > m_mismatches; // typeOfFitness mismatch, d, h, Gene
};

#endif // INDIVIDUAL_H
