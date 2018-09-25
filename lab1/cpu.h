//
// Created by gswlee on 18-9-25.
//

#ifndef LAB1_CPU_H
#define LAB1_CPU_H

#include <vector>
#include <string>

using namespace std;

class cpu {
public:
    int num;

    cpu(const int num);

    bool isFinsh();

    bool isAvaliable();

    bool isAvalibale(int corenum);

    int findCoreAvaliable();

    void setTask(int corenum, int tasknum);

    void setCore(const int corenum);

    int getTaskOnHandle(int corenum);

private:
    vector<bool> coreConditions;
    vector<int> taskOnHandle;
};


#endif //LAB1_CPU_H
