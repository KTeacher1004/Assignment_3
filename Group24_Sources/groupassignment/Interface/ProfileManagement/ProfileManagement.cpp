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
#include <cctype>
#include "../Register/Register.h"
#include "../Dashboard/Dashboard.h"
#include "../Passenger/Passenger.h"
#include "../Driver/Driver.h"


using namespace std;

void ProfileManagement(Member m){
    cout << "----------Member Interface------------" << endl;
    cout << "Welcome: " << m.getFullName() << endl;
    cout << "--------------------------------------" << endl;
    cout << "1.  View Profile" << endl;
    cout << "2.  Edit Profile" << endl;
    cout << "3.  Choose Role" << endl;
    cout << "4.  Logout" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Select your choice: " << endl;
    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
        print(m);
        ProfileManagement(m);
        break;
    case 2:
        EditPage(m);
        ProfileManagement(m);
        break;
    case 3:
        cout << "Role selection "  << endl;
        cout << "1. As Passenger" << endl;
        cout << "2. As Driver" << endl;
        cout << "3. Log Out" << endl;
        cout << "Select your choice: " << endl;
        int role;
        cin >> role;
        cin.ignore();
        switch (role){
            case 1:
            PassengerPage(m);
            ProfileManagement(m);
            break;
            case 2:
            DriverPage(m);
            ProfileManagement(m);
            break;
            case 3:
            cout << "Logging out..." << endl;
            ProfileManagement(m);
            default:
            cout  << "Invalid choice" << endl;
            ProfileManagement(m);
        }
        break;
    case 4:
        powerOn();
        break;
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }
}