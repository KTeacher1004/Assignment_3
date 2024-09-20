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



using namespace std;

//class admin
class Admin {
    private:
    string adminname;
    string adminRealname;
    string adminemail;
    long long adminphoneNumber;
    string adminPassword;
    string adminID_type;
    string adminID_number;
    string adminRole;
    public:
    Admin(){}
        Admin(string adminname, string adminRealname, string adminemail, long long adminphoneNumber, string adminPassword, string adminID_type, string adminID_number, string adminRole) : 
        adminname(adminname), adminRealname(adminRealname), adminemail(adminemail), adminphoneNumber(adminphoneNumber), adminPassword(adminPassword), adminID_type(adminID_type), adminID_number(adminID_number), adminRole(adminRole){}
    //Setter
    void setAdminname(string adminname) { this->adminname = adminname; }
    void setAdminPassword(string adminPassword) { this->adminPassword = adminPassword; }
    void setAdminRealName(string adminRealname) { this->adminRealname = adminRealname; }
    void setAdminEmail(string adminemail) { this->adminemail = adminemail; }
    void setAdminIDType(string adminID_type) { this->adminID_type = adminID_type; }
    void setAdminIDNumber(string adminID_number) { this->adminID_number = adminID_number; }
    void setAdminPhoneNumber(int adminphoneNumber) { this->adminphoneNumber = adminphoneNumber; }
    void setAdminRole(string adminRole) { this->adminRole = adminRole; }

    // Getter
    string getAdminname() { return adminname; }
    string getAdminPassword() { return adminPassword; }
    string getAdminRealName() { return adminRealname; }
    string getAdminEmail() { return adminemail; }
    string getAdminIDType() { return adminID_type; }
    string getAdminIDNumber() { return adminID_number; }
    long long getAdminPhoneNumber() { return adminphoneNumber; }
    string getAdminRole() { return adminRole; }
};

void WriteAdminToFile(Admin admin) {
    ofstream outputFile("Admin.dat", ios::app);
    if (outputFile.is_open()) {
        outputFile << admin.getAdminname() << "," << admin.getAdminPassword() << "," << admin.getAdminRealName() << "," << admin.getAdminEmail() << "," << admin.getAdminIDType() << "," << admin.getAdminIDNumber() << "," << admin.getAdminPhoneNumber() << "," << admin.getAdminRole() << endl;
        outputFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
};

struct AdminNode{
    Admin a;
    AdminNode* nextAdmin;
};

typedef struct AdminNode *ad;
void readAdminFromFile(ad &head, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string adminname, adminPassword, adminRealname, adminemail, adminID_type, adminID_number, adminRole;
        long long adminphoneNumber;

        // Parse the line using ',' as a delimiter
        getline(ss, adminname, ',');
        getline(ss, adminPassword, ',');
        getline(ss, adminRealname, ',');
        ss >> adminphoneNumber;
        ss.ignore(1, ','); // Skip the comma
        getline(ss, adminemail, ',');
        getline(ss, adminID_type, ',');
        getline(ss, adminID_number, ',');
        getline(ss, adminRole, ',');
        ss.ignore(1, ',');

        // Create a new Admin object
        Admin a;
        a.setAdminname(adminname);
        a.setAdminPassword(adminPassword);
        a.setAdminRealName(adminRealname);
        a.setAdminPhoneNumber(adminphoneNumber);
        a.setAdminEmail(adminemail);
        a.setAdminIDType(adminID_type);
        a.setAdminIDNumber(adminID_number);
        a.setAdminRole(adminRole);

        // Create a new node
        ad tmp = new AdminNode();
        tmp->a = a;
        tmp->nextAdmin = NULL;

        // Add node to the list
        if (head == NULL) {
            head = tmp;
        } else {
            ad p = head;
            while (p->nextAdmin != NULL) {
                p = p->nextAdmin;
            }
            p->nextAdmin = tmp;
        }
    }

    file.close();
}
ad return_ad(){
    ad body = NULL;
    readAdminFromFile(body, "Admin.dat");
    return body;
}

void writeAdminToTxT(ad b, const string &filename)
{
    ofstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file!" << endl;
        return;
    }
    while (b  != NULL){
        file << b->a.getAdminname() << "," << b->a.getAdminPassword() << "," << b->a.getAdminRealName() << "," << b->a.getAdminPhoneNumber() << "," << b->a.getAdminEmail() << "," << b->a.getAdminIDType() << "," << b->a.getAdminIDNumber() << "," << b->a.getAdminRole() << "\n";
        b = b->nextAdmin;
    }

    file.close();
}


void AdminPage(){
    int AdminOption;
    while (true) {
        cout << "------WELCOME BACK ADMIN-----" << endl;
        cout << "--------------------------------" << endl;
        cout << "Please choose your option:" << endl;
        cout << "(1) View Member" << endl;
        cout << "(2) View CarpoolListing" << endl;
        cout << "(3) Logout" << endl;
        cin >> AdminOption;
        cin.ignore();

        switch(AdminOption){
            case 1:{
                ifstream file("Member.dat");
                if (!file.is_open()) {
                    cerr << "Error opening file! File may not exist or is not in the correct directory." << endl;
                    break;
                }

                if (!file.good()) {
                    cerr << "Error reading file. File may be corrupted or not readable." << endl;
                    break;
                }

                string line;
                cout << "------MEMBER LIST------" << endl;
                while (getline(file, line)) {
                    cout << line << endl;
                }

                file.close();
                break;
            };
            case 2: {
                cout << "-----This is CarpoolList-----" << endl;
                break;
            }
            case 3: {
                cout << "Logging out..." << endl;
                return; // Exit the AdminPage() function
            }
            default:
                cout << "Invalid option. Please choose again." << endl;
                break;
        }
    }
}

void checkAdminLogin() {
    string adminUsername, adminPassword;
    cout << "------ADMIN LOGIN PAGE-----" << endl;
    cout << "----------------------------" << endl;
    cout << "Please enter admin credentials:" << endl;

    cout << "Enter username: ";
    cin >> adminUsername;

    cout << "Enter password: ";
    cin >> adminPassword;

    ifstream file("Admin.dat");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string adminname, adminPassword, adminRealname, adminemail, adminID_type, adminID_number, adminRole;
        long long adminphoneNumber;

        // Parse the line using ',' as a delimiter
        getline(ss, adminname, ',');
        getline(ss, adminPassword, ',');
        getline(ss, adminRealname, ',');
        ss >> adminphoneNumber;
        ss.ignore(1, ','); // Skip the comma
        getline(ss, adminemail, ',');
        getline(ss, adminID_type, ',');
        getline(ss, adminID_number, ',');
        getline(ss, adminRole, ',');
        ss.ignore(1, ',');

        if (adminname == adminUsername && adminPassword == adminPassword) {
            cout << "Login accepted!" << endl;
            AdminPage(); // Call AdminPage() here
            return;
        }
    }

    cout << "Login failed!" << endl;
}

