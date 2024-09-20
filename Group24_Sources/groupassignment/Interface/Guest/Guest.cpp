#include <iostream>
#include <fstream>
#include <string>
#include "../Register/Register.h"
using namespace std;

void GuestPage(){
    int GuestOption;
    while (true) {
        cout << "------WELCOME GUEST-----" << endl;
        cout << "--------------------------------" << endl;
        cout << "Please choose your option:" << endl;
        cout << "(1) View Carpool Listing" << endl;
        cout << "(2) Register" << endl;
        cout << "(3) Logout" << endl;
        cin >> GuestOption;
        cin.ignore();

        if (GuestOption == 1) {
            cout << "-----This is Carpool Listing-----" << endl;
        } else if (GuestOption == 2) {
            cout << "Registering..." << endl;
            RegisterPage();// Call the RegisterPage() function
        } else if (GuestOption == 3) {
            cout << "Logging out..." << endl;
            break; // Exit the loop when user chooses to logout
        } else {
            cout << "Invalid option. Please choose again." << endl;
        }
    }
}

