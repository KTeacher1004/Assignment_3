#ifndef PASSENGER_H
#define PASSENGER_H

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
#include "../Register/Register.h"
#include "../Carpool/carpool.h"
#include "../Feedback/Feedback.h"

class Passenger : public Member{
    private:
    string city;
    string role;
    vector<Carpool> bookedCarpoools;
    vector<FeedBack> passengerFeedBacks; 
    public:
    Passenger(){};
    Passenger(string username, string password, string full_name, string email, string ID_type, string ID_number, int phoneNumber, int Fee, int Rating_Score, string city, string role = "passenger", vector<Carpool> bookedCarpools = {}, vector<FeedBack> passengerFeedbacks = {}): Member(username, password, full_name, email, ID_type, ID_number, phoneNumber, Fee, Rating_Score){
        this->bookedCarpoools = bookedCarpools;
        this->city = city;
        this->role = role;
    }
    // setter
    void  setCity(string city){this->city = city;}
    void  setRole(string role){this->role = role;}


    // getter
    string getCity(){return city;}
    string getRole(){return role;}

    //function
    void loadCarpoolsFromBookedFile(const std::string &filePath);

    bool bookCarpool();

    void cancelBooking();
        
    bool giveFeedback();

    float calculateRatingScore();

    void toString();
};

#endif