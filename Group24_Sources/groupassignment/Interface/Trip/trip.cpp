#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct Carpool {
    int bookingID;
    string driver;
    string departureLocation;
    string departureTime;
    string destinationLocation;
    string date;
    string estimatedDuration;
    int availableSeats;
    double bookedSeats;
    double requiredCreditPoint;
    int minimalRatingPoint;
    string status;
};

struct AcceptingCarpool {
    int bookingID;
    string passenger;
    string status;
};

// Helper function to split a line by a delimiter (e.g., comma)
vector<string> split(const string& line, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Helper function to trim whitespace from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return ""; // If the string is all whitespace
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to read Carpool data from Carpool.txt
vector<Carpool> readCarpoolFile(const string& filename) {
    vector<Carpool> carpools;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> tokens = split(line, ','); // Split by comma

        if (tokens.size() == 12) {
            Carpool carpool;
            carpool.bookingID = stoi(trim(tokens[0]));
            carpool.driver = trim(tokens[1]);
            carpool.departureLocation = trim(tokens[2]);
            carpool.departureTime = trim(tokens[3]);
            carpool.destinationLocation = trim(tokens[4]);
            carpool.date = trim(tokens[5]);
            carpool.estimatedDuration = trim(tokens[6]);
            carpool.availableSeats = stoi(trim(tokens[7]));
            carpool.bookedSeats = stod(trim(tokens[8]));
            carpool.requiredCreditPoint = stod(trim(tokens[9]));
            carpool.minimalRatingPoint = stoi(trim(tokens[10]));
            carpool.status = trim(tokens[11]);

            carpools.push_back(carpool);
        }
    }
    return carpools;
}

// Function to read AcceptingCarpool data from AcceptingCarpool.txt
vector<AcceptingCarpool> readAcceptingCarpoolFile(const string& filename) {
    vector<AcceptingCarpool> acceptingCarpools;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<string> tokens = split(line, ','); // Split by comma

        if (tokens.size() == 3) {
            AcceptingCarpool acceptingCarpool;
            acceptingCarpool.bookingID = stoi(trim(tokens[0]));
            acceptingCarpool.passenger = trim(tokens[1]);
            acceptingCarpool.status = trim(tokens[2]);

            acceptingCarpools.push_back(acceptingCarpool);
        }
    }
    return acceptingCarpools;
}

// Function to write accepted trips to Trip.txt
void writeToTripTxt(const vector<Carpool>& carpools, const vector<AcceptingCarpool>& acceptingCarpools) {
    ofstream outputFile("Trip.txt");
    if (!outputFile.is_open()) {
        cerr << "Unable to open Trip.txt for writing." << endl;
        return;
    }

    bool foundTrip = false;
    
    for (const auto& carpool : carpools) {
        if (carpool.status == "Pending") {
            for (const auto& acceptingCarpool : acceptingCarpools) {
                if (acceptingCarpool.bookingID == carpool.bookingID && acceptingCarpool.status == "Accepted") {
                    outputFile << "Carpool Information:" << endl;
                    outputFile << "Driver: " << carpool.driver << endl;
                    outputFile << "Departure Location: " << carpool.departureLocation << endl;
                    outputFile << "Departure Time: " << carpool.departureTime << endl;
                    outputFile << "Destination Location: " << carpool.destinationLocation << endl;
                    outputFile << "Date: " << carpool.date << endl;
                    outputFile << "Estimated Duration: " << carpool.estimatedDuration << endl;
                    outputFile << "Available Seats: " << carpool.availableSeats << endl;
                    outputFile << "Booked Seats: " << carpool.bookedSeats << endl;
                    outputFile << "Required Credit Points: " << carpool.requiredCreditPoint << endl;
                    outputFile << "Minimal Rating Points: " << carpool.minimalRatingPoint << endl;
                    outputFile << "Passenger: " << acceptingCarpool.passenger << endl;
                    outputFile << endl;
                    foundTrip = true;
                }
            }
        }
    }

    if (!foundTrip) {
        outputFile << "No accepted trips found." << endl;
    }

    outputFile.close();
}

// Function to display contents of Trip.txt based on the user's input username
void displayTripTxt() {
    ifstream inputFile("Trip.txt");
    if (!inputFile.is_open()) {
        cerr << "Unable to open Trip.txt for reading." << endl;
        return;
    }

    string username;
    cout << "Enter your username: ";
    getline(cin, username);

    string line;
    bool found = false;
    bool displayTrip = false;
    string tripDetails = "";

    while (getline(inputFile, line)) {
        if (line.find("Carpool Information:") != string::npos && !tripDetails.empty()) {
            // Check if the previous trip should be displayed (if Passenger or Driver matches)
            if (displayTrip) {
                cout << tripDetails << "-----------------------------------" << endl;
            }
            tripDetails.clear();
            displayTrip = false;
        }

        tripDetails += line + "\n";

        // Check if the line contains "Driver:" or "Passenger:" and if it matches the username
        if (line.find("Driver:") != string::npos || line.find("Passenger:") != string::npos) {
            stringstream ss(line);
            string key, name;
            getline(ss, key, ':'); // Get the key (Driver or Passenger)
            getline(ss, name);     // Get the name after the colon
            name = trim(name);     // Trim any extra spaces

            // Check if the username matches Driver or Passenger
            if (name == username) {
                found = true;
                displayTrip = true;
            }
        }
    }

    // Output the last trip if found
    if (displayTrip) {
        cout << tripDetails << "-----------------------------------" << endl;
    }

    if (!found) {
        cout << "Trip doesn't exist." << endl;
    }

    inputFile.close();
}

// TripPage function to generate Trip.txt and then display its contents based on the username
void TripPage() {
    vector<Carpool> carpools = readCarpoolFile("Carpool.txt");
    vector<AcceptingCarpool> acceptingCarpools = readAcceptingCarpoolFile("AcceptingCarpool.txt");

    writeToTripTxt(carpools, acceptingCarpools);
    displayTripTxt();  // Display the Trip.txt contents filtered by username
}