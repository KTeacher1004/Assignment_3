#ifndef FEEDBACK_H
#define FEEDBACK_H

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

class FeedBack
{
private:
    
    string passengerName;
    string driverName;
    float rating; // Rating given
    string feedbackContent;

public:
    FeedBack(){}

    FeedBack(string passengerName = "", string driverName = "", float rating = 0, std::string feedbackContent = "")
    {
        this->passengerName = passengerName;
        this->driverName = driverName;
        this->rating = rating;
        this->feedbackContent = feedbackContent;
    }

    float getRating();
    void setRating(float new_rating);

    string getPassengerName();
    void setPassengerName(string name);

    string getDriverName();
    void setDriverName(string name);

    string getFeedbackContent();
    void setFeedbackContent(string feedbackContent);

    void calculaterMemberPoint(float rating);
    void calculateDriverPoint(float rating);
    void displayFeedback();
    void applyFeedback();
};

#endif // FEEDBACK_H     