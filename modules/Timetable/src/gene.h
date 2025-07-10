#ifndef GENE_H
#define GENE_H

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

class Gene
{
public:
    int classGroupID;
    int subjectID;
    int teacherID;
    int classroomID;

    bool operator==(const Gene &g2) const
    {
        return subjectID == g2.subjectID &&
               teacherID == g2.teacherID &&
               classroomID == g2.classroomID &&
               classGroupID == g2.classGroupID;
    }

    Gene(int cg = 0, int s = 0, int t = 0, int cr = 0)
        : classGroupID(cg), subjectID(s), teacherID(t), classroomID(cr) {}

};


using chromosome_t = std::vector<std::vector<std::vector<Gene>>>;


// bool operator<(const Gene &g2) const
// {
//     return teacherID < g2.teacherID;//subjectID < g2.subjectID;
//     // teacherID < g2.teacherID &&
//     // classroomID < g2.classroomID;
// }

#endif // GENE_H
