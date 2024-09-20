#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>
#include <numeric>
#include <time.h>
#include <random>
#include <iomanip>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

class Time{
private:
    int hour;
    int minute;

public:
    Time();                     
    Time(int hour, int minute); 

    int& getHour();
    int& getMinute();
    void setHour(int hourP);
    void setMinute(int minuteP);

    Time operator+(const Time &timeParam);

    friend istream &operator>>(istream &in, Time &time);

    static Time fromString(const string &timeStr);

    string toString() const;
};

#endif