//
// Created by gswlee on 18-9-25.
//

#ifndef LAB1_TASK_H
#define LAB1_TASK_H

#include <iostream>


using namespace std;

class task {
public:
    int num;

    task(const int arriveHour, const int arriveMinute, const int needTime);

    void begin(const int beginHour, const int beginMinute);

    void finsh();

    bool isArrive(int nowHour, int nowMinute);

    int getArriveHour();

    int getArriveMinute();

    int getNeedTime();
    int getEndHour();

    int getEndMinute();

    bool isFinsh();

    void showInfo();

private:
    int arriveHour = 0;
    int arriveMinute = 0;
    int beginHour = 0;
    int beginMinute = 0;
    int endHour = 0;
    int endMinute = 0;
    int needTime = 0;
    int costTime = 0;
    double rate = 0;
    bool condition = false;
};


#endif //LAB1_TASK_H
