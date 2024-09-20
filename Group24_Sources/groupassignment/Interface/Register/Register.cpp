#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>
#include <vector>
#include "../Class/class.h"
#include "../Dashboard/Dashboard.h"


using namespace std;

void readFromFile(nd &head, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string username, password, full_name, email, ID_type, IDnumber;
        int phone_number, fee, Rating_Score;

        // Parse the line using ',' as a delimiter
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, full_name, ',');
        ss >> phone_number;
        ss.ignore(1, ','); // Skip the comma
        getline(ss, email, ',');
        getline(ss, ID_type, ',');
        getline(ss, IDnumber, ',');
        ss >> fee;
        ss.ignore(1, ',');
        ss >> Rating_Score;

        // Create a new Member object
        Member m;
        m.setUsername(username);
        m.setPassword(password);
        m.setFullName(full_name);
        m.setPhoneNumber(phone_number);
        m.setEmail(email);
        m.setIDType(ID_type);
        m.setIDNumber(IDnumber);
        m.setFee(fee);
        m.setRatingScore(Rating_Score);

        // Create a new node
        nd tmp = new Node();
        tmp->m = m;
        tmp->nextMember = NULL;

        // Add node to the list
        if (head == NULL) {
            head = tmp;
        } else {
            nd p = head;
            while (p->nextMember != NULL) {
                p = p->nextMember;
            }
            p->nextMember = tmp;
        }
    }

    file.close();
}

void writetoTxT(nd b, const string &filename)
{
    ofstream file(filename);
    if(!file.is_open()){
        cerr << "Error opening file!" << endl;
        return;
    }
    while (b  != NULL){
        file << b->m.getUsername() << "," << b->m.getPassword() << "," << b->m.getFullName() << "," << b->m.getPhoneNumber() << "," << b->m.getEmail() << "," << b->m.getIDType() << "," << b->m.getIDNumber() << "," << b->m.getFee() << "," << b->m.getRatingScore() << "\n";
        b = b->nextMember;
    }

    file.close();
}

// Password Policy
bool PasswordPolicy(string password) {
    // Check for at least one uppercase, one lowercase, and one digit
    bool hasUpper = false, hasLower = false, hasDigit = false;

    for (char ch : password) {
        if (isupper(ch)) hasUpper = true;
        if (islower(ch)) hasLower = true;
        if (isdigit(ch)) hasDigit = true;
    }

    return hasUpper && hasLower && hasDigit;
}

//Create Account
nd createAccount(){
    Member m;
    string username, password, full_name, email, ID_type, IDnumber;
    int phone_number;
    int fee = 10;
    int Rating_Score = -1;
    cout << "----Welcome to Register Page----" << endl;
    cout << "--------------------------------" << endl;
    cout << "Please fill in your information." << endl;
    // Get username
    cout << "Username: ";
    cin >> username;

    // Get password and validate against policy
    while (true) {
        cout << "Password: ";
        cin >> password;
        if (PasswordPolicy(password)) {
            cout << "Password accepted!" << endl;
            break;
        } else {
            cout << "Password must contain at least one uppercase letter, one lowercase letter, and one digit." << endl;
        }
    }

    // Clear input buffer before reading full name
    cin.ignore();
    
    // Get full name
    cout << "Your full name: ";
    getline(cin, full_name);

    // Get phone number
    cout << "Your phone number: ";
    cin >> phone_number;

    // Get email
    cout << "Your email: ";
    cin >> email;

    // Clear input buffer before reading ID type
    cin.ignore();

    // Get ID type and validate
    while (true) {
        cout << "Your ID type (Passport or Citizen ID): ";
        getline(cin, ID_type);
        if (ID_type == "Passport" || ID_type == "Citizen ID") {
            break;
        } else {
            cout << "Invalid ID Type, please enter 'Passport' or 'Citizen ID'." << endl;
        }
    }

    // Get ID number
    cout << "ID/Passport number: ";
    cin >> IDnumber;

    cout << "Your starting Fee is: " << fee << endl;
    cout << "Your starting Rating_Score is: " << Rating_Score << endl;
    
    m.setUsername(username);
    m.setPassword(password);
    m.setFullName(full_name);
    m.setPhoneNumber(phone_number);
    m.setEmail(email);
    m.setIDType(ID_type);
    m.setIDNumber(IDnumber);
    m.setFee(fee);
    m.setRatingScore(Rating_Score);

    nd tmp = new Node();
    tmp->m = m;
    tmp->nextMember = NULL;
    return tmp;
}

// Check if list is empty
bool empty(nd m){
    return m == NULL;
}

// Get size of the list
int Size(nd m){
    int cnt = 0;
    while(m != NULL){
        ++cnt;
        m = m->nextMember;
    }
    return cnt;
}

// Add node
void insert(nd &a){
    nd tmp = createAccount();
    if (a == NULL){
        a = tmp;
    } else {
        nd p = a;
        while(p->nextMember != NULL){
            p = p->nextMember;
        }
        p->nextMember = tmp;
    }
}

// Print value of a Member node
void print(Member m){
    cout << "Username: " << m.getUsername() << endl;
    cout << "Password: " << m.getPassword() << endl;
    cout << "Fullname: " << m.getFullName() << endl;
    cout << "Phone number: " <<  m.getPhoneNumber() << endl;
    cout << "Email: " <<  m.getEmail() << endl;
    cout << "ID Type: " << m.getIDType() << endl;
    cout << "ID Number: " << m.getIDNumber() << endl;
    cout << "Fee: " << m.getFee() << endl;
    cout << "Rating Score: " << m.getRatingScore() << endl;
}





// Print the list (Admin view)
void printls(nd a){
    cout << "List Member\n" << endl;
    while(a != NULL){
        print(a->m);
        cout << "__________________" << endl;
        a = a->nextMember;
    }
}

// Return Head
nd return_nd(){
    nd head = NULL;
    readFromFile(head, "Member.dat");
    return head;
}



// Interface
void RegisterPage(){
    nd head = return_nd();
    insert(head);
    writetoTxT(head,"Member.dat");
    powerOn();
}

void ViewList(){
    nd head = return_nd();
    printls(head);
}

//Upgrade 
void Edit(nd &a, string name){
    nd current = a;
    while(current != NULL){
         if(name == current->m.getUsername()){
            int choice;
            while(true){
                cout << "Choose what to change:" << endl;
                cout << "1. Username" << endl;
                cout << "2. Password" << endl;
                cout << "3. Full name" << endl;
                cout << "4. Phone number" << endl;
                cout << "5. Email" << endl;
                cout << "6. ID type" << endl;
                cout << "7. ID number" << endl;
                cout << "8. Back to main menu" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                case 1: {
                    string new_name;
                    cout  << "Enter new username: ";
                    cin >>  new_name;
                    current->m.setUsername(new_name);
                    break;
                }
                    break;
                
                default:
                    break;
                }
            }
         }
    }
}

void EditPage(Member m){
    nd head = return_nd();
    string name = m.getUsername();
    Edit(head, name);
    writetoTxT(head,"Member.dat");
}

