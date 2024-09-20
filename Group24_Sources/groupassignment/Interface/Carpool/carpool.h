#ifndef CARPOOL_H
#define CARPOOL_H

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
#include "../Driver/driver.h"
#include "../Time/time.h"

using namespace std;

class Driver;

class Carpool{
private:
    static int staticId; 
    int bookingID;
    string driver;
    string departureLocation;
    Time departureTime;
    string destinationLocation;
    string date;
    Time estimatedDuration;
    int requiredCreditPoint;
    float minimalRatingPoint;
    int availableSeats;
    int bookedSeats;
    string status;

public:
    Carpool() : bookingID(staticId++) {} // increment staticId every time a new object is created

    Carpool(int id, string driver, string departureLocation, Time departureTime, string destinationLocation, string date, Time estimatedDuration, int requiredCreditPoint, float minimalRatingPoint, int availableSeats, int bookedSeats, string status = "Available")
        : bookingID(staticId++) 
    {
        this->driver = driver;
        this->departureLocation = departureLocation;
        this->departureTime = departureTime;
        this->destinationLocation = destinationLocation;
        this->date = date;
        this->estimatedDuration = estimatedDuration;
        this->requiredCreditPoint = requiredCreditPoint;
        this->minimalRatingPoint = minimalRatingPoint;
        this->availableSeats = availableSeats;
        this->bookedSeats = bookedSeats;
        this->status = status;
    }

    // Getter functions
    int getBookingID();
    string getDriver();
    string getDepartureLocation();
    Time getDepartureTime();
    string getDestinationLocation();
    string getDate();
    Time getEstimatedDuration();
    int getAvailableSeats();
    int getBookedSeats();
    int getRequiredCreditPoint();
    float getMinimalRatingPoint();
    string getStatus();

    // Setter functions
    void setDriver(string driver);
    void setBookingID(int bookingID);
    void setDepartureLocation(string departureLocation);
    void setDepartureTime(Time departureTime);
    void setDestinationLocation(string destinationLocation);
    void setDate(string date);
    void setEstimatedDuration(Time estimatedDuration);
    void setRequiredCreditPoint(int requiredCreditPoint);
    void setMinimalRatingPoint(float minimalRatingPoint);
    void setAvailableSeats(int availableSeats);
    void setBookedSeats(int bookedSeats);
    void setStatus(string status);

    
    static Carpool createFromStream(istream &file);
    void writeToStream(ostream &file) const;

    void carpoolToString();
};

#endif