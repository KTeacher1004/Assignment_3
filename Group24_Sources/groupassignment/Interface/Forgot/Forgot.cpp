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

void checkAccount(nd &head, string username, string email){
    // Check if the account exists
    nd current = head;
    while(current != NULL){
        if(username == current->m.getUsername() && email == current->m.getEmail()){
            cout << "Acount found" << endl;
            cout << "Please enter new password: " << endl;
            string newPassword;
            cin >> newPassword;
            if(PasswordPolicy(newPassword)){
                current->m.setPassword(newPassword);
                cout << "Password  changed successfully" << endl;
                cout << "Go to Login Page" << endl;
                system("pause");
                system("cls");
                writetoTxT(head, "Member.dat");
                LoginPage();
            }
            else {
                cout << "Password must contain at least one uppercase letter, one lowercase letter, and one digit." << endl;
                system("pause");
                system("cls");
                return;
            }
        } else {
            cout << "Does not find the account with that username and email" << endl;
            system("pause");
            system("cls");
            return;
        }
        current = current->nextMember;
    }
}




void ForgotPassword(){
    cout << "Forgot Password Interface" << endl;
    string username, email;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter email: ";
    cin >> email;
    nd head = return_nd();
    checkAccount(head, username, email);
}