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
#include "../Time/time.h"
#include "carpool.h"



int Carpool::getBookingID()
{
    return bookingID;
}
string Carpool::getDriver(){
    return driver;
}

string Carpool::getDepartureLocation()
{
    return departureLocation;
}

Time Carpool::getDepartureTime()
{
    return departureTime;
}

string Carpool::getDestinationLocation()
{
    return destinationLocation;
}

string Carpool::getDate()
{
    return date;
}

Time Carpool::getEstimatedDuration()
{
    return estimatedDuration;
}

int Carpool::getAvailableSeats()
{
    return availableSeats;
}

int Carpool::getBookedSeats(){
    return bookedSeats;
}

int Carpool::getRequiredCreditPoint()
{
    return requiredCreditPoint;
}

float Carpool::getMinimalRatingPoint(){
    return minimalRatingPoint;
}

string Carpool::getStatus()
{
    return status;
}


//set methods
void Carpool::setDriver(string driver){
    this->driver = driver;
}

void Carpool::setBookingID(int bookingID)
{
    this->bookingID = bookingID;
}

void Carpool::setDepartureLocation(string departureLocation)
{
    this->departureLocation = departureLocation;
}

void Carpool::setDepartureTime(Time departureTime)
{
    this->departureTime = departureTime;
}

void Carpool::setDestinationLocation(string destinationLocation)
{
    this->destinationLocation = destinationLocation;
}

void Carpool::setDate(string date)
{
    this->date = date;
}

void Carpool::setEstimatedDuration(Time estimatedDuration)
{
    this->estimatedDuration = estimatedDuration;
}

void Carpool::setAvailableSeats(int availableSeats)
{
    this->availableSeats = availableSeats;
}

void Carpool::setBookedSeats(int BookedSeats){
    this->bookedSeats = bookedSeats;
}

void Carpool::setRequiredCreditPoint(int requiredCreditPoint)
{
    this->requiredCreditPoint = requiredCreditPoint;
}
void Carpool::setMinimalRatingPoint(float minimalRatingPoint){
    this->minimalRatingPoint = minimalRatingPoint;
}
void Carpool::setStatus(string status)
{
    this->status = status;
}

void Carpool::carpoolToString(){
    cout << setw(12) << left << getBookingID() << " | "
         << setw(15) << left << getDriver() << " | "
         << setw(20) << left << getDepartureLocation() << " | "
         << setw(15) << left << getDepartureTime().toString() << " | "
         << setw(20) << left << getDestinationLocation() << " | "
         << setw(12) << left << getDate() << " | "
         << setw(5) << getEstimatedDuration().getHour() << " hour" << (getEstimatedDuration().getHour() > 1 ? "s" : "") << " " << getEstimatedDuration().getMinute() << " minute" << (getEstimatedDuration().getMinute() > 1 ? "s" : "") << " | "
         << setw(21) << left << getRequiredCreditPoint() << " | "
         << setw(20) << left << getMinimalRatingPoint() << " | "
         << setw(15) << left << getAvailableSeats() << " | "
         << setw(15) << left << getBookedSeats() << " | "
         << setw(10) << left << getStatus() << " | " << endl;
}

Carpool Carpool::createFromStream(istream &file)
{
    Carpool carpool;

    string bookingIDStr, availableSeatsStr, bookedSeatsStr, requiredCreditPointStr, minimalRatingPointStr, departureTimeStr, estimatedDurationStr;


    getline(file, bookingIDStr, ',');
    getline(file, carpool.driver, ',');
    getline(file, carpool.departureLocation, ',');
    getline(file, departureTimeStr, ',');
    getline(file, carpool.destinationLocation, ',');
    getline(file, carpool.date, ',');
    getline(file, estimatedDurationStr, ',');
    getline(file, requiredCreditPointStr, ',');
    getline(file, minimalRatingPointStr, ',');
    getline(file, availableSeatsStr, ',');
    getline(file, bookedSeatsStr, ',');
    getline(file, carpool.status, ',');

    carpool.bookingID = stoi(bookingIDStr);
    carpool.departureTime = Time::fromString(departureTimeStr);         
    carpool.estimatedDuration = Time::fromString(estimatedDurationStr);
    carpool.requiredCreditPoint = stoi(requiredCreditPointStr);
    carpool.minimalRatingPoint = stof(minimalRatingPointStr);
    carpool.availableSeats = stoi(availableSeatsStr);
    carpool.bookedSeats = stoi(bookedSeatsStr);

    return carpool;
}


void Carpool::writeToStream(ostream &file) const{
    file << bookingID << ", " 
        << driver << ", " 
        << departureLocation << ", "
         << departureTime.toString() << ", " 
         << destinationLocation << ", "
         << date << ", " 
         << estimatedDuration.toString() << ", "
         << requiredCreditPoint << ", " 
         << minimalRatingPoint << ", "
         << availableSeats << ", " 
         << bookedSeats << ", "
         << status << endl;
}

int Carpool::staticId = 1;

