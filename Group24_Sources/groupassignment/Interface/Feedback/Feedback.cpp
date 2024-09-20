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
#include "Feedback.h"

using namespace std;

using namespace std;

float FeedBack::getRating() { return rating; }
void FeedBack::setRating(float new_rating) { rating = new_rating; }

string FeedBack::getPassengerName() { return passengerName; }
void FeedBack::setPassengerName(string name) { passengerName = name; }

string FeedBack::getDriverName() { return driverName; }
void FeedBack::setDriverName(string name) { driverName = name; }

string FeedBack::getFeedbackContent() { return feedbackContent; }
void FeedBack::setFeedbackContent(string feedbackContent){
    this->feedbackContent = feedbackContent;
};

void FeedBack::displayFeedback()
{
    cout << "Rating: " << rating << endl;
    cout << "Feedback: " << feedbackContent << endl;
}

void FeedBack::applyFeedback()
{
    cout << "\nFeedback applied and credit points updated:\n";
    displayFeedback();
}