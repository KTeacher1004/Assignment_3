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
#include "../ProfileManagement/ProfileManagement.h"

using namespace std;

void CheckLogin(nd &head, string name, string password){
    
    nd current = head;
    while(current != NULL){
        // Check if the credentials match
        if(name == current->m.getUsername() && password == current->m.getPassword()){
            cout << "Login Success" << endl;
            system("pause");
            system("cls");
            ProfileManagement(current->m);
            break;
        }
        else {
        current = current->nextMember;
        }
    }
    cout << "Invalid  Username or Password" << endl;
    system("pause"); 
    return;
}

void LoginPage(){
    cout << "------WELCOME TO LOGIN PAGE-----" << endl;
    cout << "--------------------------------" << endl;
    cout << "Please login in your account" << endl;
    string username, password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    nd head = return_nd();
    CheckLogin(head,  username, password);

}
