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
#include "time.h"

using namespace std;

Time::Time()
{
    hour = 0;
    minute = 0;
}

Time::Time(int hour, int minute)
{
    this->hour = hour;
    if (minute > 59 || minute < 0)
    {
        this->minute = 0;
    }
    else
    {
        this->minute = minute;
    }
}

int &Time::getHour()
{
    return hour;
}

int &Time::getMinute()
{
    return minute;
}

void Time::setHour(int hourP)
{
    hour = hourP;
}

void Time::setMinute(int minuteP)
{
    if (minuteP > 59 || minuteP < 0)
    {
        minute = 0;
    }
    else
    {
        minute = minuteP;
    }
}

Time Time::operator+(const Time &timeParam) {
    int sumMinute = this->minute + timeParam.minute;
    int sumHour = this->hour + timeParam.hour + (sumMinute / 60);

    int finalMinute = sumMinute % 60;
    int finalHour = sumHour % 24;
    return Time(finalHour, finalMinute);
}

istream &operator>>(istream &in, Time &time){
    char delimiter; 
    in >> time.hour >> delimiter >> time.minute;
    if (time.minute > 59 || time.minute < 0)
    {
        time.minute = 0; 
    }
    return in;
}

Time Time::fromString(const string &timeStr)
{
    stringstream ss(timeStr);
    int h, m;
    char colon;
    ss >> h >> colon >> m; // Read hour, colon, and minute
    return Time(h, m);
}

string Time::toString() const
{
    stringstream ss;
    ss << setw(2) << setfill('0') << hour << ":" << setw(2) << setfill('0') << minute;
    return ss.str();
}

