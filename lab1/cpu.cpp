//
// Created by gswlee on 18-9-25.
//

#include "cpu.h"

cpu::cpu(const int num) {
    this->num = num;
    for (int i = 0; i < num; i++){
        coreConditions.push_back(true);
        taskOnHandle.push_back(100);
    }

}

bool cpu::isFinsh() {
    for (int i = 0; i < num; i++) {
        if (coreConditions[i] == false)
            return false;
    }
    return true;
}

bool cpu::isAvaliable() {
    for (int i = 0; i < num; i++) {
        if (coreConditions[i] == true)
            return true;
    }
    return false;
}

bool cpu::isAvalibale(int corenum) {
    return coreConditions[corenum];
}

int cpu::findCoreAvaliable() {
    for (int i = 0; i < num; i++) {
        if (coreConditions[i] == true)
            return i;
    }
}

void cpu::setTask(int corenum, int tasknum) {
    coreConditions[corenum] = false;
    taskOnHandle[corenum] = tasknum;
}

void cpu::setCore(const int corenum) {
    coreConditions[corenum] = true;
}

int cpu::getTaskOnHandle(int corenum) { return taskOnHandle[corenum]; }