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
#include "../Class/Driver.h"
#include "../ProfileManagement/ProfileManagement.h"
#include "../Node/Node.h"


using namespace std;

bool Driver::createCarpool()
{
    string departureLocation, destinationLocation, date, departureTimeStr, estimatedDurationStr;
    int requiredCreditPoint, availableSeats;
    float minimalRatingPoint;
    int bookedSeats = 0;
    string status = "Available";
    string name = getFullName();

    // Collect input from the user
    cout << "Enter departure location: ";
    getline(cin, departureLocation);

    cout << "Enter destination location: ";
    getline(cin, destinationLocation);

    cout << "Enter date (YYYY-MM-DD): ";
    getline(cin, date);

    cout << "Enter departure time (HH:MM): ";
    getline(cin, departureTimeStr);

    cout << "Enter estimated duration (HH:MM): ";
    getline(cin, estimatedDurationStr);

    cout << "Available Seat: ";
    cin >> availableSeats;
    cin.ignore();

    cout << "Enter required credit points: ";
    cin >> requiredCreditPoint;
    cin.ignore();

    cout << "Enter minimal rating point: ";
    cin >> minimalRatingPoint;
    cin.ignore();

    // Create a Carpool object with the gathered data
    Carpool newCarpool;
    newCarpool.setDriver(name);
    newCarpool.setDepartureLocation(departureLocation);
    newCarpool.setDepartureTime(Time::fromString(departureTimeStr));
    newCarpool.setDestinationLocation(destinationLocation);
    newCarpool.setDate(date);
    newCarpool.setEstimatedDuration(Time::fromString(estimatedDurationStr));
    newCarpool.setRequiredCreditPoint(requiredCreditPoint);
    newCarpool.setMinimalRatingPoint(minimalRatingPoint);
    newCarpool.setAvailableSeats(availableSeats);
    newCarpool.setBookedSeats(bookedSeats);
    newCarpool.setStatus(status);

    ofstream file("Carpool.txt", ios::app);
    if (!file.is_open())
    {
        cerr << "Error opening file!" << endl;
        return false;
    }

    newCarpool.writeToStream(file);

    file.close();
    return true;
}



//unlist a carpool
bool Driver::unlistCarpool()
{
    Driver::loadCarpoolsFromFile("Carpool.txt");
    int ID;
    cout << "Please enter the booking ID: ";
    cin >> ID;

    CarpoolNode *head = nullptr;
    CarpoolNode *current = nullptr;
    bool idFound = false; // Flag to check if the ID was found

    // Create a linked list from carpools
    for (auto &carpool : carpools)
    {
        CarpoolNode *newNode = new CarpoolNode(&carpool);
        if (!head)
        {
            head = newNode;
            current = head;
        }
        else
        {
            current->next = newNode;
            current = current->next;
        }
    }

    // Check the bookedSeat before deleting the node with the specified booking ID
    if (head && head->carpool->getBookingID() == ID)
    {
        if (head->carpool->getBookedSeats() != 0)
        {
            cout << "Cannot delete this carpool. Seats are already booked." << endl;
            return false;
        }
        CarpoolNode *temp = head;
        head = head->next;
        delete temp;
        idFound = true;

        // Update booking IDs of remaining carpools
        current = head;
        while (current)
        {
            current->carpool->setBookingID(current->carpool->getBookingID() - 1);
            current = current->next;
        }
    }
    else
    {
        current = head;
        while (current && current->next)
        {
            if (current->next->carpool->getBookingID() == ID)
            {
                if (current->next->carpool->getBookedSeats() != 0)
                {
                    cout << "Cannot delete this carpool. Seats are already booked." << endl;
                    return false;
                }
                CarpoolNode *temp = current->next;
                current->next = current->next->next;
                delete temp;
                idFound = true;
                break;
            }
            current = current->next;
        }

        // Update booking IDs of remaining carpools
        if (idFound)
        {
            current = head;
            while (current)
            {
                if (current->carpool->getBookingID() > ID)
                {
                    current->carpool->setBookingID(current->carpool->getBookingID() - 1);
                }
                current = current->next;
            }
        }
    }

    // If the booking ID is not found, print a message
    if (!idFound)
    {
        cout << "Booking ID not found." << endl;

        // Cleanup linked list before returning
        current = head;
        while (current)
        {
            CarpoolNode *temp = current;
            current = current->next;
            delete temp;
        }

        return false;
    }

    // Overwrite the carpools back to the file
    ofstream file("Carpool.txt");
    if (file.is_open())
    {
        current = head;
        while (current)
        {
            current->carpool->writeToStream(file);
            current = current->next;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file." << endl;

        // Cleanup linked list
        current = head;
        while (current)
        {
            CarpoolNode *temp = current;
            current = current->next;
            delete temp;
        }

        return false;
    }

    // Delete the linked list
    current = head;
    while (current)
    {
        CarpoolNode *temp = current;
        current = current->next;
        delete temp;
    }

    return true;
}

void Driver::loadCarpoolsFromFile(const string &filePath)
{
    ifstream file(filePath);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        Carpool carpool = Carpool::createFromStream(ss);
        carpools.push_back(carpool);
    }

    file.close();
}

bool Driver::acceptBooking()
{
    int carpoolId;
    cout << "Enter the carpool ID to accept: ";
    cin >> carpoolId;

    // Open the AcceptingCarpool.txt file for reading
    ifstream infile("AcceptingCarpool.txt");
    if (!infile.is_open())
    {
        cerr << "Error: Unable to open the AcceptingCarpool.txt file." << endl;
        return false;
    }

    vector<string> acceptingCarpools;
    string line;
    bool found = false;

    // Read the file line by line
    while (getline(infile, line))
    {
        istringstream iss(line);
        string id_str, realName, status;

        getline(iss, id_str, ',');
        getline(iss, realName, ',');
        getline(iss, status, ',');

        int id = stoi(id_str);

        // If the carpool ID matches the input, change the status to "Accepted"
        if (id == carpoolId)
        {
            status = "Accepted";
            found = true;
        }

        // Recreate the line with the updated status
        string updatedLine = id_str + "," + realName + "," + status;
        acceptingCarpools.push_back(updatedLine);
    }

    infile.close();

    if (!found)
    {
        cerr << "Error: No carpools found with ID " << carpoolId << "." << endl;
        return false;
    }

    // Write the updated entries back to the AcceptingCarpool.txt file
    ofstream outfile("AcceptingCarpool.txt");
    if (!outfile.is_open())
    {
        cerr << "Error: Unable to open the AcceptingCarpool.txt file for writing." << endl;
        return false;
    }

    for (const auto &updatedLine : acceptingCarpools)
    {
        outfile << updatedLine << endl;
    }

    outfile.close();

    cout << "All bookings with carpool ID " << carpoolId << " have been accepted." << endl;
    return true;
}

bool Driver::giveFeedback()
{
    int rating;
    string feedbackContent;
    string userName;

    cout << "Enter the user's name: ";
    getline(cin, userName);

    cout << "Enter your rating (1-5): ";
    cin >> rating;
    cin.ignore();

    cout << "Enter your feedback: ";
    getline(cin, feedbackContent);

    FeedBack feedback(userName, getUsername(), rating, feedbackContent);

    ofstream file("../Feedback.txt", ios::app);
    if (file.is_open())
    {
        file << userName << "," << getUsername() << "," << rating << "," << feedbackContent << endl;
        file.close();
        cout << "Feedback given" << endl;
        return true;
    }
    else
    {
        cout << "Unable to open file" << endl;
        return false;
    }
}
float Driver::calculateRatingScore()
{
    ifstream file("../Feedback.txt");
    if (file.is_open())
    {
        string line;
        int count = 0;
        float sum = 0;
        vector<FeedBack> passengerFeedBacks;

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
            if (driverUsername == this->getUsername())
            {
                // Create a new FeedBack object and add it to the vector
                FeedBack feedback(username, driverUsername, rating, feedbackContent);
                passengerFeedBacks.push_back(feedback);
                sum += rating;
                count++;
            }
        }

        file.close();

        // Calculate the average rating score
        if (count > 0)
        {   
            setRatingScore(sum / count); // Update the driverRatingScore member variable
            return sum / count;
        }
        else
        {
            setRatingScore(sum / count); // Update the driverRatingScore member variable
            return 0.0;
        }
    }
    else
    {
        cout << "Cannot find file" << endl;
        return this->getRatingScore(); // Return the current driverRatingScore value
    }
}



void Driver::toString()
{
    Driver::loadCarpoolsFromFile("Carpool.txt");

    cout << "Username: " << getUsername() << endl;
    cout << "Real Name: " << getFullName() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Phone Number: " << getPhoneNumber() << endl;
    cout << "ID Type: " << getIDType() << endl;
    cout << "ID Number: " << getIDNumber() << endl;
    cout << "City: " << getCity() << endl;
    cout << "Role: " << getRole() << endl;
    cout << "Rating Score" << getRatingScore() << endl;

    // Printing Carpool header
    cout << "AVAILABLE CARPOOL: " << endl;
    cout << setw(12) << left << "Booking ID" << " | "
         << setw(15) << left << "Driver Name" << " | "
         << setw(20) << left << "Departure Location" << " | "
         << setw(15) << left << "Departure Time" << " | "
         << setw(20) << left << "Destination Location" << " | "
         << setw(12) << left << "Date" << " | "
         << setw(20) << left << "Estimated Duration" << " | "
         << setw(20) << left << "Required Credit Point" << " | "
         << setw(20) << left << "Minimal Rating Point" << " | "
        << setw(15) << left << "Available Seats" << " | "
        << setw(15) << left << "Booked Seats" << " | "
        << setw(10) << left << "Status" << " | " << endl;

    // Divider
    cout << setw(12) << left << "----------" << " | "
         << setw(15) << left << "--------------" << " | "
         << setw(20) << left << "------------------" << " | "
         << setw(15) << left << "--------------" << " | "
         << setw(20) << left << "--------------------" << " | "
         << setw(12) << left << "----------" << " | "
         << setw(20) << left << "--------------------" << " | "
         << setw(20) << left << "---------------------" << " | "
         << setw(20) << left << "----------------------" << " | "
         << setw(15) << left << "---------------" << " | "
         << setw(15) << left << "---------------" << " | "
         << setw(10) << left << "----------" << " | "
         << endl;

    if (carpools.empty())
    {
        cout << "No carpools available." << endl;
    }
    else
    {
        for (Carpool carpool : carpools)
        {
            carpool.carpoolToString();
        }
    }
};


void DriverPage(Member m){
    string city;
    cout <<  "Welcome, " << m.getUsername() << endl;
    cout << "Select your city" << endl;
    cin >> city;
    cin.ignore();
    bool driverLoggedIn = true;

    Driver dri(m.getUsername(), m.getPassword(), m.getFullName(), m.getEmail(), m.getIDType(), m.getIDNumber(), m.getPhoneNumber(), m.getFee(), m.getRatingScore(), city);
    while (true){
        int choice;
        cout << "1:  View all carpools" << endl;
        cout << "2:  Create a new carpool" << endl;
        cout << "3:  Unlist a carpool" << endl;
        cout << "4:  Accept user's booking" << endl;
        cout << "5. Send Feedback" << endl;
        cout << "6: Log out" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice){
            case 1:
                dri.toString();
                DriverPage(m);
                break;
            case 2:
                dri.createCarpool();
                DriverPage(m);
                break;
            case 3:
                dri.unlistCarpool();
                DriverPage(m);
                break;
            case 4:
                dri.acceptBooking();
                DriverPage(m);
                break;
            case 5:
                dri.giveFeedback();
                dri.calculateRatingScore();
                DriverPage(m);
                break;
            case 6:
                ProfileManagement(m);
                break;
            default: 
                cout << "Invalid choice" << endl;
                DriverPage(m);
        } 
    }
}