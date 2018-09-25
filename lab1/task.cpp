//
// Created by gswlee on 18-9-25.
//

#include "task.h"

task::task(const int arriveHour, const int arriveMinute, const int needTime) {
    this->arriveHour = arriveHour;
    this->arriveMinute = arriveMinute;
    this->needTime = needTime;
}

bool task::isArrive(int nowHour, int nowMinute) {
    if (nowHour < arriveHour)
        return false;
    else if (nowHour == arriveHour && nowMinute < arriveMinute)
        return false;
    return true;
}

bool task::isFinsh() { return condition; }

void task::begin(const int beginHour, const int beginMinute) {
    this->beginHour = beginHour;
    this->beginMinute = beginMinute;
    this->endHour = this->beginHour + (this->beginMinute + this->needTime) / 60;
    this->endMinute = (this->beginMinute + this->needTime) % 60;
    this->costTime = 60 * (this->endHour - this->arriveHour) + (this->endMinute - this->arriveMinute);
    this->rate = (double) this->costTime / (double) this->needTime;
    this->condition= true;
}

void task::finsh() { this->condition = true; }

int task::getArriveHour() { return arriveHour; }

int task::getArriveMinute() { return arriveMinute; }

int task::getNeedTime() { return needTime; }

int task::getEndHour() { return endHour; }

int task::getEndMinute() { return endMinute; }

void task::showInfo() {
    printf("%3d%10d:%02d%10d:%02d%10d:%02d%10d%10d%10.3lf\n", num, arriveHour, arriveMinute, beginHour, beginMinute,
           endHour, endMinute, needTime, costTime, rate);
}