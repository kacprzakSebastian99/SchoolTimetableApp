#include "individual.h"
#include <iostream>
#include <unordered_map>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "../DataEntry/src/classgroup.h"
#include "../DataEntry/src/profile.h"
#include "../DataEntry/src/classroom.h"
#include "../DBModule/src/containers.h"

Individual::Individual(chromosome_t chromosome, const Containers &classesData)
{
    setChromosome(chromosome);
    setFitness(cal_fitness(classesData));
}

chromosome_t Individual::chromosome() const
{
    return m_chromosome;
}

void Individual::setChromosome(const chromosome_t &newChromosome)
{
    if (m_chromosome == newChromosome)
        return;
    m_chromosome = newChromosome;
}

int Individual::fitness() const
{
    return m_fitness;
}

void Individual::setFitness(int newFitness)
{
    if (m_fitness == newFitness)
        return;
    m_fitness = newFitness;
}

int Individual::subjectFitness() const
{
    return m_subjectFitness;
}

void Individual::setSubjectFitness(int newSubjectFitness)
{
    if (m_subjectFitness == newSubjectFitness)
        return;
    m_subjectFitness = newSubjectFitness;
}

int Individual::teacherFitness() const
{
    return m_teacherFitness;
}

void Individual::setTeacherFitness(int newTeacherFitness)
{
    if (m_teacherFitness == newTeacherFitness)
        return;
    m_teacherFitness = newTeacherFitness;
}

int Individual::classroomFitness() const
{
    return m_classroomFitness;
}

void Individual::setClassroomFitness(int newClassroomFitness)
{
    if (m_classroomFitness == newClassroomFitness)
        return;
    m_classroomFitness = newClassroomFitness;
}

int Individual::windowFitness() const
{
    return m_windowFitness;
}

void Individual::setWindowFitness(int newWindowFitness)
{
    if (m_windowFitness == newWindowFitness)
        return;
    m_windowFitness = newWindowFitness;
}

int Individual::distributionFitness() const
{
    return m_distributionFitness;
}

void Individual::setDistributionFitness(int newDistributionFitness)
{
    if (m_distributionFitness == newDistributionFitness)
        return;
    m_distributionFitness = newDistributionFitness;
}

int Individual::blockFitness() const
{
    return m_blockFitness;
}

void Individual::setBlockFitness(int newBlockFitness)
{
    if (m_blockFitness == newBlockFitness)
        return;
    m_blockFitness = newBlockFitness;
}

int Individual::availabilityFitness() const
{
    return m_availabilityFitness;
}

void Individual::setAvailabilityFitness(int newAvailabilityFitness)
{
    if (m_availabilityFitness == newAvailabilityFitness)
        return;
    m_availabilityFitness = newAvailabilityFitness;
}

std::vector<std::vector<int> > Individual::missingSubjects() const
{
    return m_missingSubjects;
}

void Individual::setMissingSubjects(const std::vector<std::vector<int> > &newMissingSubjects)
{
    if (m_missingSubjects == newMissingSubjects)
        return;
    m_missingSubjects = newMissingSubjects;
}

int Individual::cal_fitness(const Containers &classesData)
{
    size_t classGroupSize = classesData.getClassGroups().size();
    size_t teacherSize = classesData.getTeachers().size(); // zamien classesData na containersData albo cos w tym stylu
    size_t classroomSize = classesData.getClassrooms().size();

    int fitness = 0;
    int subjectFitness = 0;     // type: 1
    int teacherFitness = 0;     // type: 2
    int classroomFitness = 0;   // type: 3
    int windowFitness = 0;      // type: 4
    int distributionFitness = 0;// type: 5
    int blockFitness = 0;       // type: 6
    int availabilityFitness = 0;// type: 7
    //być może fixedLessonStartTimeFitnes

    std::vector<std::vector<int>> missingSubjectsContainer;
    std::vector<int> noGap;
    std::vector<int> distribution;
    std::unordered_map<int, std::pair<int, int>> subjectCounter;
    std::vector<std::tuple<int, int, int>> subjectLocation;
    std::vector<std::tuple<int, int, int, Gene> > mismatchesVector;
    Gene emptyGene;

    for(int c = 0; c < classGroupSize; ++c)
    {
        for(int d = 0; d < DAYS_SIZE; ++d)
        {
            for(int h = 0; h < HOURS_SIZE; ++h)
            {
                if(chromosome()[c][d][h].subjectID != 0) //0
                {
                    //SUBJECT & WINDOW FITNESS 1
                    //subjectCounter.push_back(chromosome()[c][d][h].subjectID);
                    noGap.push_back(h + 1);
                    subjectCounter.insert({chromosome()[c][d][h].subjectID, std::make_pair(d, h)});
                    subjectLocation.emplace_back(chromosome()[c][d][h].subjectID, d, h);

                    //TEACHER & CLASSROOM FITNESS
                    for(int cg = 0; cg < classGroupSize; ++cg)
                    {
                        if(classesData.getClassGroups()[cg]->id() != classesData.getClassGroups()[c]->id())
                        {
                            if(chromosome()[c][d][h].teacherID == chromosome()[cg][d][h].teacherID)
                            {
                                ++teacherFitness;
                            }
                            if(chromosome()[c][d][h].classroomID == chromosome()[cg][d][h].classroomID)
                            {
                                ++classroomFitness;
                            }
                        }
                    }

                    // for(int tD = 0; tD < teacherSize; tD++)
                    // {
                    //     if(chromosome()[c][d][h].teacherID == classesData.getTeachers()[tD]->id())
                    //     {
                    //         classesData.getTeachers()[tD]->
                    //     }
                    // }

                }                
            }
            // WINDOW FITNESS 2
            if(!noGap.empty())
            {
                windowFitness += noGap.back() - (noGap.front() - 1) - noGap.size();
            }
            // else
            // {
            //     windowFitness += 0;//5//DAYS_SIZE;
            // }
            // DISTRIBUTION FITNESS 1
            distribution.push_back(noGap.size());
            noGap.clear();
        }
        // DISTRIBUTION FITNESS 2
        for(const auto& numberOfLesson : distribution)
        {
            if(numberOfLesson == 3) // 5
            {
                distributionFitness += 1;// ++distributionFitness;
            }
            else if(numberOfLesson == 2)
            {
                distributionFitness += 3;//8;
            }
            else if(numberOfLesson < 2)
            {
                distributionFitness += 5;//8;
            }
        }
        distribution.clear();
        //SUBJECT FITNESS
        auto [subjectFit, blockFit, subjectsID] = cal_subject_block_fitness(classesData, classesData.getClassGroups()[c]->profileID(), subjectLocation);//subjectCounter);
        subjectFitness += subjectFit;
        blockFitness += blockFit;
        missingSubjectsContainer.push_back(subjectsID);
        subjectCounter.clear();
        subjectLocation.clear();
    }





    fitness = subjectFitness + teacherFitness + classroomFitness + windowFitness + distributionFitness + blockFitness;

    std::cout << "Fitness: " << fitness //<< std::endl;
    << "\nsubjectFitness: " << subjectFitness
    << "\nteacherFitness:  " << teacherFitness
    << "\nclassroomFitness: " << classroomFitness
    << "\nwindowsFitness: " << windowFitness
    << "\ndistributionFitness: " << distributionFitness
    << "\nblockFitness: " << blockFitness << std::endl;

    setSubjectFitness(subjectFitness);
    setTeacherFitness(teacherFitness);
    setClassroomFitness(classroomFitness);
    setWindowFitness(windowFitness);
    setDistributionFitness(distributionFitness);
    setBlockFitness(blockFitness);

    setMissingSubjects(missingSubjectsContainer);

    return fitness;
}
// sprawdzic czy mozna ulepszyc np przy pomocy tuple
std::tuple<int, int, std::vector<int> > Individual::cal_subject_block_fitness(const Containers &classesData, const int &classGroupProfileID, std::vector<std::tuple<int, int, int>> subjectLocation)//const std::unordered_map<int, std::pair<int, int> > &subjectCounter)
{
    int subjectFitness = 0, blockFitness = 0;
    std::vector<int> missingSubject;

    const Profile* classGroupProfile = nullptr;
    for(const Profile* p : classesData.getProfiles())
    {
        if(p->id() == classGroupProfileID)
        {
            classGroupProfile = p;
            break;
        }
    }

    std::unordered_map<int, int> currentNumberOfHours;
    std::unordered_map<int, std::vector<std::vector<int>>> blockVector;

    for(const auto& t : subjectLocation) // zmień na np. subjectLocation
    {
        ++currentNumberOfHours[std::get<0>(t)];
        // BLOCK FITNESS 1
        if (blockVector.find(std::get<0>(t)) == blockVector.end())
            blockVector[std::get<0>(t)] = std::vector<std::vector<int>>(DAYS_SIZE);
        blockVector[std::get<0>(t)][std::get<1>(t)].push_back(std::get<2>(t));
        std::sort(blockVector[std::get<0>(t)][std::get<1>(t)].begin(), blockVector[std::get<0>(t)][std::get<1>(t)].end());
    }

    for(const Subject* s : classGroupProfile->getSubjectsList())
    {
        bool found = false;
        for(const auto& [sID, sHours] : currentNumberOfHours)
        {
            if(s->id() == sID)
            {
                found = true;
                // qDebug() << classGroupProfileID << " INITIAL_NUMBER_OF_HOURS: " << s->numberOfHours() << " / " << sHours;
                if(s->numberOfHours() > sHours) //if(s->numberOfHours() != sHours)
                {
                    ++subjectFitness;
                    missingSubject.push_back(sID);
                }
                else if(s->numberOfHours() < sHours)
                {
                    subjectFitness += 4;
                    //missingSubject.push_back(sID);
                }
                else // BLOCK FITNESS 2
                {
                    if(s->block() == 1) // 0 // czy w danym dniu nie występuje więcej niż 1 instancja przedmiotu
                    {
                        for(const auto& [sID, dhVector] : blockVector)
                            for(int d = 0; d < dhVector.size(); ++d)
                            {
                                if(blockVector[sID][d].size() > 1)
                                    blockFitness += blockVector[sID][d].size() - 1; // ++blockFitness;
                                    // blockFitness += 0;//blockFitness++;
                            }
                    }
                    else
                    {
                        std::vector<int> blockDayDistribution;
                        for(const auto& [sID, dhVector] : blockVector)
                        {
                            for(int d = 0; d < dhVector.size(); ++d)
                            {
                                if(blockVector[sID][d].size() != 0)
                                    blockDayDistribution.push_back(blockVector[sID][d].size());
                                // else
                                    // continue;
                                if(blockVector[sID][d].size() == s->block() && blockVector[sID][d].back() - blockVector[sID][d].front() > s->block() - 1)
                                    blockFitness += blockVector[sID][d].back() - blockVector[sID][d].front(); //++blockFitness;
                                    // blockFitness += 0;
                                else if(blockVector[sID][d].size() > s->block())
                                    blockFitness += blockVector[sID][d].size() - s->block();
                                    // blockFitness += 0;
                            }
                        }
                        if(blockDayDistribution.size() != std::ceil(static_cast<double>(s->numberOfHours()) / s->block())) //std::ceil(s->numberOfHours() / s->block()))
                            blockFitness += 0;
                            // blockFitness += std::abs(blockDayDistribution.size() - std::ceil(static_cast<double>(s->numberOfHours()) / s->block())); //++blockFitness;
                    }
                }
            }
        }
        if (!found)
        {
            // Przedmiot w ogóle nie występuje w planie — brakuje go całkowicie!
            ++subjectFitness;
            missingSubject.push_back(s->id());
        }
    }
    return std::make_tuple(subjectFitness, blockFitness, missingSubject);
}

int Individual::random_num(int start, int end) //rozważ inline
{
    int range = (end - start) + 1;
    int random_int = start + (rand()%range);
    return random_int;
}

Gene Individual::mutated_genes(const std::vector<int> &missingSubjects, const std::vector<std::vector<Gene> > &classGroupGenes)
{
    bool next = false;
    for(size_t s = 0; s < classGroupGenes.size(); ++s)
    {
        next = false; // bez tego pomija nastepne petle
        for(size_t cr = 0; cr < classGroupGenes[s].size(); ++cr)
        {
            if(next == true)
                break;
            for(size_t ms = 0; ms < missingSubjects.size(); ++ms)
            {
                if(missingSubjects[ms] == classGroupGenes[s][cr].subjectID)
                {
                    int r = random_num(0, classGroupGenes[s].size() - 1); // zwraca losowa sale ze zbioru dostepnych dla danego przedmiotu //sprawdz czy poprawne
                    return classGroupGenes[s][r];
                }
                else
                {
                    next = true;
                    break;
                }
            }
        }
    }

    Gene emptyGene;
    int r1 = random_num(0, 100);
    int r2 = random_num(0, classGroupGenes.size() - 1);
    return r1 < 70 ? classGroupGenes[r2][0] : emptyGene; // r1 < 90

    // return emptyGene;
}

Individual Individual::mate(Individual parent2, const std::vector<std::vector<std::vector<Gene> > > &Genes, const Containers &classesData)
{
    chromosome_t child_chromosome;
    Gene emptyGene;
    size_t classGroupsSize = classesData.getClassGroups().size();
    std::vector<std::vector<Gene>> classGroupGenes;
    std::vector<std::vector<int>> missingSubjectsContainer = missingSubjects();

    int currentFitness = fitness();

    child_chromosome.resize(classGroupsSize);
    for(int c = 0; c < classGroupsSize; ++c)
    {
        child_chromosome[c].resize(DAYS_SIZE);
        for(int d = 0; d < DAYS_SIZE; ++d)
            child_chromosome[c][d].resize(HOURS_SIZE);
    }

    int MAX_HOUR = HOURS_SIZE;
    // if(fitness() < 30 && distributionFitness() > 5 )
    //     MAX_HOUR = HOURS_SIZE - 1;

    // bool sort = false;
    // if(currentFitness > 15)
    //     sort = false;
    // else
    //     sort = true;

    // int cf = random_num(0, 10);

    for(int c = 0; c < classGroupsSize; ++c)
    {
        classGroupGenes = Genes[c]; // bo zestaw genów dla danej klasy występuje w tej samej kolejności co klasy// sprawdzić
        emptyGene.classGroupID = classesData.getClassGroups()[c]->id();
        for(int d = 0; d < DAYS_SIZE; ++d)
        {
            for(int h = 0; h < MAX_HOUR; ++h) //HOURS_SIZE
            {
                float p = random_num(0, 100)/100;
                if(currentFitness > 40) //10
                {
                    if(p < 0.25)//0.50
                    {
                        child_chromosome[c][d][h] = chromosome()[c][d][h];
                    }
                    else if(p >=0.25 && p < 0.50)//p >=0.50 && p < 0.90
                    {
                        child_chromosome[c][d][h] = parent2.chromosome()[c][d][h];
                    }
                    else
                    {// mutacje w randomowych miejscach w planie spróbować
                        int d1 = random_num(0, 4);
                        int h1 = random_num(0, MAX_HOUR - 1);//7
                        child_chromosome[c][d1][h1] = mutated_genes(missingSubjectsContainer[c], classGroupGenes);//Genes[c]);//
                    }
                }
                else if(currentFitness > 30)
                {
                    if(p < 0.35)//0.50
                    {
                        child_chromosome[c][d][h] = chromosome()[c][d][h];
                    }
                    else if(p >=0.35 && p < 0.65)//p >=0.50 && p < 0.90
                    {
                        child_chromosome[c][d][h] = parent2.chromosome()[c][d][h];
                    }
                    else
                    {// mutacje w randomowych miejscach w planie spróbować
                        int d1 = random_num(0, 4);
                        int h1 = random_num(0, 6);//7
                        child_chromosome[c][d1][h1] = mutated_genes(missingSubjectsContainer[c], classGroupGenes);//Genes[c]);//
                    }
                }
                else if(currentFitness > 20)
                {
                    if(p < 0.45)//0.50
                    {
                        child_chromosome[c][d][h] = chromosome()[c][d][h];
                    }
                    else if(p >=0.45 && p < 0.75)//p >=0.50 && p < 0.90
                    {
                        child_chromosome[c][d][h] = parent2.chromosome()[c][d][h];
                    }
                    else
                    {// mutacje w randomowych miejscach w planie spróbować
                        int d1 = random_num(0, 4);
                        int h1 = random_num(0, 6);//7
                        child_chromosome[c][d1][h1] = mutated_genes(missingSubjectsContainer[c], classGroupGenes);//Genes[c]);//
                    }
                }
                else if(currentFitness > 10)
                {
                    if(p < 0.50)//0.50
                    {
                        child_chromosome[c][d][h] = chromosome()[c][d][h];
                    }
                    else if(p >=0.50 && p < 0.90)//p >=0.50 && p < 0.90
                    {
                        child_chromosome[c][d][h] = parent2.chromosome()[c][d][h];
                    }
                    else
                    {// mutacje w randomowych miejscach w planie spróbować
                        //int d1 = random_num(0, 4);
                        int h1 = random_num(0, 6);//7
                        child_chromosome[c][d][h1] = mutated_genes(missingSubjectsContainer[c], classGroupGenes);//Genes[c]);//
                    }
                }
                else if(currentFitness >= 0)
                {
                    if(p < 0.50)//0.50
                    {
                        child_chromosome[c][d][h] = chromosome()[c][d][h];
                    }
                    else if(p >=0.50 && p < 0.95)//0.99
                    {
                        child_chromosome[c][d][h] = parent2.chromosome()[c][d][h];
                    }
                    else
                    {// mutacje w randomowych miejscach w planie spróbować
                        //int d1 = random_num(0, 4);
                        //int h1 = random_num(0, 6);//7
                        child_chromosome[c][d][h] = mutated_genes(missingSubjectsContainer[c], classGroupGenes);//Genes[c]);//
                    }
                }
            }
            // if(MAX_HOUR != HOURS_SIZE)
            //     child_chromosome[c][d][7] = emptyGene;
        }
        // if(sort)
        //     for(int d = 0; d < DAYS_SIZE; ++d)
        //     {
        //         std::sort(child_chromosome[c][d].begin(), child_chromosome[c][d].end());
        //     }
    }
    return Individual(child_chromosome, classesData);
}

