#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "cpu.h"
#include "task.h"

using namespace std;

void prepareTask(vector<task> &taskSet);

void getTaskQueue(const vector<task> taskSet, vector<task> &taskQueue, int sysClockHour, int sysClockMinute);

void FCFS(vector<task> taskSet, cpu intel);

void SJF(vector<task> taskSet, cpu intel);

void HRN(vector<task> taskSet, cpu intel);

bool sortFun(task a, task b);

bool isFinsh(vector<task> taskSet);

bool sortSJF(task a, task b);


int main() {
    int n;
    cout << "输入cpu核心个数:";
    cin >> n;
    cpu intel(n);
    vector<task> taskSet;
    prepareTask(taskSet);
    sort(taskSet.begin(), taskSet.end(), sortFun);

    //先来先服务
    FCFS(taskSet, intel);

    //最短作业优先
    SJF(taskSet, intel);

    //最高相应比
    HRN(taskSet, intel);

    return 0;
}

void prepareTask(vector<task> &taskSet) {
    int arriveHour, arriveMinute, needTime, i = 0;
    ifstream infile;
    infile.open("/home/gswlee/study/OSclass/lab1/data.dat", ios::in);
    while (!infile.eof()) {
        infile >> arriveHour >> arriveMinute >> needTime;
        task temp(arriveHour, arriveMinute, needTime);
        temp.num = i;
        taskSet.push_back(temp);
        i++;
    }
    infile.close();
}

void getTaskQueue(vector<task> taskSet, vector<task> &taskQueue, int sysClockHour, int sysClockMinute) {
    for (int i = 0; i < taskSet.size(); i++) {
        if (taskSet[i].isArrive(sysClockHour, sysClockMinute) && !taskSet[i].isFinsh())
            taskQueue.push_back(taskSet[i]);
    }
    sort(taskQueue.begin(), taskQueue.end(), sortFun);
}

bool sortFun(task a, task b) {
    if (a.getArriveHour() < b.getArriveHour())
        return true;
    if ((a.getArriveHour() == b.getArriveHour()) && (a.getArriveMinute() < b.getArriveMinute()))
        return true;
    return false;
}

bool sortSJF(task a, task b) {
    if (a.getNeedTime() < b.getNeedTime())
        return true;
    return false;
}

bool isFinsh(vector<task> taskSet) {
    for (int i = 0; i < taskSet.size(); i++) {
        if (!taskSet[i].isFinsh())
            return false;
    }
    return true;
}

void FCFS(vector<task> taskSet, cpu intel) {
    //设置系统时钟;
    int sysClockHour = taskSet[0].getArriveHour();
    int sysClockMinute = taskSet[0].getArriveMinute();

    while (!intel.isFinsh() || !isFinsh(taskSet)) {
        //将完成的任务退出cpu
        for (int i = 0; i < intel.num; i++) {
            if (intel.isAvalibale(i) == false)

                if ((taskSet[intel.getTaskOnHandle(i)].getEndHour() == sysClockHour) &&
                    (taskSet[intel.getTaskOnHandle(i)].getEndMinute() == sysClockMinute)) {
                    taskSet[intel.getTaskOnHandle(i)].finsh();
                    intel.setCore(i);
                }
        }
        //开始处理任务
        if (intel.isAvaliable()) {
            vector<task> taskQueue;
            getTaskQueue(taskSet, taskQueue, sysClockHour, sysClockMinute);
            while (intel.isAvaliable() && taskQueue.size()) {
                int i = intel.findCoreAvaliable();
                intel.setTask(i, taskQueue[0].num);
                taskSet[taskQueue[0].num].begin(sysClockHour, sysClockMinute);
                taskQueue.erase(taskQueue.begin());
            }

        }

        //更新时钟
        sysClockHour += (sysClockMinute + 1) / 60;
        sysClockMinute = (sysClockMinute + 1) % 60;
    }
    cout << "先来先服务" << endl;
    cout << "任务号" << "      " << "进入时间" << "      " << "开始时间" << "      " << "结束时间" << "      " << "预计时间" << "  "
         << "周转时间" << "  " << "带权周转时间" << endl;
    for (int i = 0; i < taskSet.size(); i++) {
        taskSet[i].showInfo();
    }
}

void SJF(vector<task> taskSet, cpu intel) {
    //设置系统时钟;
    int sysClockHour = taskSet[0].getArriveHour();
    int sysClockMinute = taskSet[0].getArriveMinute();

    while (!intel.isFinsh() || !isFinsh(taskSet)) {
        //将完成的任务退出cpu
        for (int i = 0; i < intel.num; i++) {
            if (intel.isAvalibale(i) == false)

                if ((taskSet[intel.getTaskOnHandle(i)].getEndHour() == sysClockHour) &&
                    (taskSet[intel.getTaskOnHandle(i)].getEndMinute() == sysClockMinute)) {
                    taskSet[intel.getTaskOnHandle(i)].finsh();
                    intel.setCore(i);
                }
        }
        //开始处理任务
        if (intel.isAvaliable()) {
            vector<task> taskQueue;
            getTaskQueue(taskSet, taskQueue, sysClockHour, sysClockMinute);
            sort(taskQueue.begin(), taskQueue.end(), sortSJF);
            while (intel.isAvaliable() && taskQueue.size()) {
                int i = intel.findCoreAvaliable();
                intel.setTask(i, taskQueue[0].num);
                taskSet[taskQueue[0].num].begin(sysClockHour, sysClockMinute);
                taskQueue.erase(taskQueue.begin());
            }

        }

        //更新时钟
        sysClockHour += (sysClockMinute + 1) / 60;
        sysClockMinute = (sysClockMinute + 1) % 60;
    }
    cout<<endl;
    cout << "最短作业优先" << endl;
    cout << "任务号" << "      " << "进入时间" << "      " << "开始时间" << "      " << "结束时间" << "      " << "预计时间" << "  "
         << "周转时间" << "  " << "带权周转时间" << endl;
    for (int i = 0; i < taskSet.size(); i++) {
        taskSet[i].showInfo();
    }
}

void HRN(vector<task> taskSet, cpu intel) {
    //设置系统时钟;
    int sysClockHour = taskSet[0].getArriveHour();
    int sysClockMinute = taskSet[0].getArriveMinute();

    while (!intel.isFinsh() || !isFinsh(taskSet)) {
        //将完成的任务退出cpu
        for (int i = 0; i < intel.num; i++) {
            if (intel.isAvalibale(i) == false)

                if ((taskSet[intel.getTaskOnHandle(i)].getEndHour() == sysClockHour) &&
                    (taskSet[intel.getTaskOnHandle(i)].getEndMinute() == sysClockMinute)) {
                    taskSet[intel.getTaskOnHandle(i)].finsh();
                    intel.setCore(i);
                }
        }
        //开始处理任务
        if (intel.isAvaliable()) {
            vector<task> taskQueue;
            getTaskQueue(taskSet, taskQueue, sysClockHour, sysClockMinute);
            sort(taskQueue.begin(), taskQueue.end(), [sysClockHour, sysClockMinute](task a, task b) {
                if ((((sysClockHour - a.getArriveHour()) * 60 + (sysClockMinute - a.getArriveMinute())) *
                     b.getNeedTime()) >
                    (((sysClockHour - b.getArriveHour()) * 60 + (sysClockMinute - b.getArriveMinute())) *
                     a.getNeedTime()))
                    return false;
                return true;
            });
            while (intel.isAvaliable() && taskQueue.size()) {
                int i = intel.findCoreAvaliable();
                intel.setTask(i, taskQueue[0].num);
                taskSet[taskQueue[0].num].begin(sysClockHour, sysClockMinute);
                taskQueue.erase(taskQueue.begin());
            }

        }

        //更新时钟
        sysClockHour += (sysClockMinute + 1) / 60;
        sysClockMinute = (sysClockMinute + 1) % 60;
    }
    cout<<endl;
    cout << "最高响应比优先" << endl;
    cout << "任务号" << "      " << "进入时间" << "      " << "开始时间" << "      " << "结束时间" << "      " << "预计时间" << "  "
         << "周转时间" << "  " << "带权周转时间" << endl;
    for (int i = 0; i < taskSet.size(); i++) {
        taskSet[i].showInfo();
    }
}

