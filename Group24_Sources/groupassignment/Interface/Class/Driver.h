#ifndef DRIVER_H
#define DRIVER_H

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
#include "../Feedback/Feedback.h"
#include "../Carpool/carpool.h"
#include "../Carpool/carpoolNode.h"

class Driver : public Member{
    private:
    string city;
    string role;
    vector<Carpool> carpools;
    vector<FeedBack> passengerFeedBacks;
    CarpoolNode *head;
    public:
    Driver(){};
    Driver(string username, string password, string full_name, string email, string ID_type, string ID_number, int phoneNumber, int Fee, int Rating_Score, string city, string role = "driver", vector<Carpool> carpools = {}, vector<FeedBack> passengerFeedbacks = {}): Member(username, password, full_name, email, ID_type, ID_number, phoneNumber, Fee, Rating_Score){
        this->city = city;
        this->role = role;
        this->carpools = carpools;
        head = nullptr;
    }
    // setter
    void  setCity(string city){this->city = city;}
    void  setRole(string role){this->role = role;}



    // getter
    string getCity(){return city;}
    string getRole(){return role;}


    //function 
    bool createCarpool();

    bool unlistCarpool();

    void loadCarpoolsFromFile(const std::string &filePath);

    void readCarpoolsFromFile(const std::string &filePath);

    bool acceptBooking();

    bool giveFeedback();

    float calculateRatingScore();

    void toString();
};

#endif