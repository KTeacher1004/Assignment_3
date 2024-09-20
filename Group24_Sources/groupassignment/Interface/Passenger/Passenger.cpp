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
#include "../Class/Passenger.h"
#include "../Carpool/carpool.h"
#include "../Time/time.h"
#include "../ProfileManagement/ProfileManagement.h"
#include "../Node/Node.h"


using namespace std;

bool Passenger::bookCarpool(){
    ifstream infile("Carpool.txt");
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open the carpool file." << endl;
        return false;
    }

    vector<string> carpoolList;
    string line;
    int carpoolId;

    cout << "Enter the ID of the carpool you want to book: ";
    cin >> carpoolId;

    bool carpoolFound = false;
    bool alreadyBooked = false;
    bool seatAvailable = false;

    string driver, departureLocation, destinationLocation, date, status;
    Time departureTime, estimatedDuration;
    int availableSeats, bookedSeats, requiredCreditPoint;
    float minimalRatingPoint;

    while (getline(infile, line))
    {
        istringstream iss(line);

        string id_str, departureTime_str, estimatedDuration_str, availableSeats_str, bookedSeats_str, requiredCreditPoint_str, minimalRatingPoint_str;
        getline(iss, id_str, ',');
        getline(iss, driver, ',');
        getline(iss, departureLocation, ',');
        getline(iss, departureTime_str, ',');
        getline(iss, destinationLocation, ',');
        getline(iss, date, ',');
        getline(iss, estimatedDuration_str, ',');
        getline(iss, requiredCreditPoint_str, ',');
        getline(iss, minimalRatingPoint_str, ',');
        getline(iss, availableSeats_str, ',');
        getline(iss, bookedSeats_str, ',');
        getline(iss, status, ',');

        int id = stoi(id_str);
        availableSeats = stoi(availableSeats_str);
        bookedSeats = stoi(bookedSeats_str);
        requiredCreditPoint = stoi(requiredCreditPoint_str);
        minimalRatingPoint = stof(minimalRatingPoint_str);
        departureTime = Time::fromString(departureTime_str);
        estimatedDuration = Time::fromString(estimatedDuration_str);

        if (id == carpoolId)
        {
            carpoolFound = true;

            // Check if the carpool is already booked by the user
            for (Carpool bookedCarpool : bookedCarpoools)
            {
                if (bookedCarpool.getBookingID() == carpoolId)
                {
                    alreadyBooked = true;
                    break;
                }
            }

            // Check if seats are available
            if (bookedSeats < availableSeats)
            {
                seatAvailable = true;
                bookedSeats++;      // Increment the number of booked seats
                status = "Pending"; // Update status to "Pending"
                line = id_str + "," + driver + "," + departureLocation + ", " + departureTime.toString() + "," + destinationLocation + "," + date + ", " + estimatedDuration.toString() + ", " + to_string(requiredCreditPoint) + ", " + to_string(minimalRatingPoint) + ", " + to_string(availableSeats) + ", " + to_string(bookedSeats) + ", " + status;
            }
        }

        carpoolList.push_back(line); 
    }

    infile.close();

    if (!carpoolFound)
    {
        cerr << "Error: Carpool with booking ID " << carpoolId << " not found." << endl;
        return false;
    }

    if (alreadyBooked)
    {
        cerr << "Error: You have already booked this carpool." << endl;
        return false;
    }

    if (!seatAvailable)
    {
        cerr << "Error: No available seats for this carpool." << endl;
        return false;
    }

  
    ofstream outfile("Carpool.txt");
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open the carpool file for writing." << endl;
        return false;
    }

    for (const auto &carpool : carpoolList)
    {
        outfile << carpool << endl;
    }

    outfile.close();

  
    Carpool carpool(carpoolId, driver, departureLocation, departureTime, destinationLocation, date,
                    estimatedDuration, requiredCreditPoint, minimalRatingPoint, availableSeats, bookedSeats, status);

    bookedCarpoools.push_back(carpool);

    ofstream bookedCarpoolFile("BookedCarpool.txt", ios::app);
    if (bookedCarpoolFile.is_open())
    {
        bookedCarpoolFile << carpoolId << "," << getUsername() << endl;
        bookedCarpoolFile.close();
    }
    else
    {
        cerr << "Error: Unable to open the BookedCarpool file for writing." << endl;
    }

  
    ofstream acceptingCarpoolFile("AcceptingCarpool.txt", ios::app);
    if (acceptingCarpoolFile.is_open())
    {
        acceptingCarpoolFile << carpoolId << "," << getUsername() << ",Pending" << endl;
        acceptingCarpoolFile.close();
    }
    else
    {
        cerr << "Error: Unable to open the AcceptingCarpool file for writing." << endl;
    }

    cout << "Carpool booked successfully." << endl;
    return true;
}

void Passenger::cancelBooking() {
    string a,id;
    cout << "Enter the carpool id you want to cancel: ";
    cin >> id;
    a = getUsername();
    CancelOne(a, id);
}

string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}


bool Passenger::giveFeedback()
{
    int rating;
    string feedbackContent;
    string driverName;

    cout << "Enter the driver's name: ";
    getline(cin, driverName);

    cout << "Enter your rating (1-5): ";
    cin >> rating;
    cin.ignore();

    cout << "Enter your feedback: ";
    getline(cin, feedbackContent);

    FeedBack feedback(getUsername(), driverName, rating, feedbackContent);

    ofstream file("../Feedback.txt", ios::app);
    if (file.is_open())
    {
        file << driverName << "," << getUsername() << "," << rating << "," << feedbackContent << endl;
        file.close();
        cout << "Feedback given" << endl;
        return true;
    }
    else
    {
        cout << "Unable to open file" << endl;
        return false;
    }
};

float Passenger::calculateRatingScore()
{
    ifstream file("../Feedback.txt");
    if (file.is_open())
    {
        string line;
        int count = 0;
        float sum = 0;
        vector<FeedBack> driverFeedBacks;

        while (getline(file, line))
        {
            // Parse each line to extract username, rating, driver_username, and feedback_content
            stringstream ss(line);
            string username, driverUsername, ratingStr, feedbackContent;
            getline(ss, username, ',');
            getline(ss, driverUsername, ',');
            getline(ss, ratingStr, ',');
            int rating = stoi(ratingStr);
            getline(ss, feedbackContent);

            // Check if the driverUsername matches the driver's username
            if (username == this->getUsername())
            {
                // Create a new FeedBack object and add it to the vector
                FeedBack feedback(username, driverUsername, rating, feedbackContent);
                driverFeedBacks.push_back(feedback);
                sum += rating;
                count++;
            }
        }

        file.close();

        // Calculate the average rating score
        if (count > 0)
        {
            setRatingScore(sum / count); 
            return sum / count;
        }
        else
        {
            setRatingScore(sum / count);
            return 0.0;
        }
    }
    else
    {
        cout << "Cannot find file" << endl;
        return getRatingScore(); 
    }
}


void Passenger::toString()
{
    cout << "Username: " << getUsername() << endl;
    cout << "Real Name: " << getFullName() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Phone Number: " << getPhoneNumber() << endl;
    cout << "ID Type: " << getIDType() << endl;
    cout << "ID Number: " << getIDNumber() << endl;
    cout << "City: " << getCity() << endl;
    cout << "Rating Score" <<  getRatingScore() << endl;


    string filePath = "BookedCarpool.txt";

    cout << "BOOKED CARPOOL: " << endl;
    cout << setw(12) << left << "Booking ID" << endl;
    cout << setw(12) << left << "----------" << endl;


    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    string line;
    bool hasBookings = false;

    while (getline(file, line))
    {
        stringstream ss(line);
        string bookingId, realName;

        getline(ss, bookingId, ',');
        getline(ss, realName, ',');

        // Trim any leading/trailing spaces from realName
        realName = trim(realName);

        // Compare the trimmed realName with the Passenger's real name
        if (realName == getUsername())
        {
            cout << setw(12) << left << bookingId << endl;
            hasBookings = true;
        }
    }

    if (!hasBookings)
    {
        cout << "No carpools booked for this user." << endl;
    }

    file.close();
}

void PassengerPage(Member m){
    string city;
    cout <<  "Welcome, " << m.getUsername() << endl;
    cout << "Select your city" << endl;
    cin >> city;

    Passenger pas(m.getUsername(), m.getPassword(), m.getFullName(), m.getEmail(), m.getIDType(), m.getIDNumber(), m.getPhoneNumber(), m.getFee(), m.getRatingScore(), city);

     while (true){
        int choice;
        cout << "1:  Book Carpool" << endl;
        cout << "2:  Cancel Carpool" << endl;
        cout << "3:  Give Feedback" << endl;
        cout << "4:  View  Bookings" << endl;
        cout << "5: Log out" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice){
            case 1:
                pas.bookCarpool();
                PassengerPage(m);
                break;
            case 2:
                pas.cancelBooking();
                PassengerPage(m);
                break;
            case 3:
                pas.giveFeedback();
                pas.calculateRatingScore();
                PassengerPage(m);
                break;
            case 4:
                pas.toString();
                PassengerPage(m);
                break;
            case 5:
                ProfileManagement(m);
                break;
            default: 
                cout << "Invalid choice" << endl;
                PassengerPage(m);
        } 
    }
}