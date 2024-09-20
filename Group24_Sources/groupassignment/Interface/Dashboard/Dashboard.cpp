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
#include "../Login/Login.h"
#include "../Forgot/Forgot.h"
#include "../Admin/admin.h"
#include "../Guest/Guest.h"



using namespace std;

#define ll long long

void powerOn(){
    bool turnOn = true;
    while (turnOn){
        int loggingOption;
        cout << "EEET2482/EEET2653/COSC2082/COSC2721 N" << endl;
        cout << "GROUP ASSIGNMENT CARPOOLING APPLICATIO" << endl;
        cout << "Instructor: Dr Ling Huo Chong, Dr Jeff Nijsse" << endl;
        cout << "Group: Group number 24" << endl;
        cout << "S3976250: Ly Minh Phuc" << endl;
        cout << "S3976251: Nguyen Tu Quoc Thai" << endl;
        cout << "S3976252: Tran Hoang Khiem" << endl;
        cout << "S3976253: Tran Vinh Tuong" << endl;
        cout << endl;
        cout << "------------------- WELCOME TO CARPOOLING APPLICATION -----------------" << endl;
        cout << endl;
        cout << "Use the application as: Guest (1), Member(2), Admin(3)" << endl;
        cin >> loggingOption;
        cin.ignore();

        switch(loggingOption){
            case 1:{
                GuestPage();
                break;
            };
            case 2:{
                cout << "1: SIGN UP" << endl;
                cout << "2: LOG IN" << endl;
                cout << "3: Forgot Password" << endl;
                cout << "4: EXIT" << endl;

                int option;
                cout << "Enter your option: ";
                cin >> option;
                cin.ignore();

                switch (option)
                {
                case 1:
                    RegisterPage();
                    break;
                case 2:
                    LoginPage();
                    break;
                case 3:
                    ForgotPassword();
                    break;
                case 4:
                    cout << "Confirm exiting? (Y/N): ";
                    char confirm;
                    cin >> confirm;
                    cin.ignore();
                    if (confirm == 'Y' || confirm == 'y'){
                        turnOn = false;
                    }
                    break;
                default:
                    cout << "Invalid option! Please enter 1, 2, or 3." << endl;
                    break;
                }
                break;
            };
            case 3: {
                checkAdminLogin();
                break;
            }
        }  
    }
}