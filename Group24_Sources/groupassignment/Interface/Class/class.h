#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>


using namespace std;

// class Member
class Member{
    //class attributes
    private:
        string username, password, full_name, email, ID_type, ID_number;
        int phoneNumber, Fee, Rating_Score;
    public:
    //Constructor
    Member(){}
        Member(string username, string password, string full_name, string email, string ID_type, string ID_number, int phoneNumber, int Fee, int Rating_Score)
        : username(username), password(password), full_name(full_name), email(email), ID_type(ID_type), ID_number(ID_number), phoneNumber(phoneNumber), Fee(Fee), Rating_Score(Rating_Score) {}
        // Setter
    void setUsername(string username) { this->username = username; }
    void setPassword(string password) { this->password = password; }
    void setFullName(string full_name) { this->full_name = full_name; }
    void setEmail(string email) { this->email = email; }
    void setIDType(string ID_type) { this->ID_type = ID_type; }
    void setIDNumber(string ID_number) { this->ID_number = ID_number; }
    void setPhoneNumber(int phoneNumber) { this->phoneNumber = phoneNumber; }
    void setFee(int Fee) { this->Fee = Fee; }
    void setRatingScore(int Rating_Score) { this->Rating_Score = Rating_Score; }

    // Getter
    string getUsername() { return username; }
    string getPassword() { return password; }
    string getFullName() { return full_name; }
    string getEmail() { return email; }
    string getIDType() { return ID_type; }
    string getIDNumber() { return ID_number; }
    int getPhoneNumber() { return phoneNumber; }
    int getFee() { return Fee; }
    int getRatingScore() { return Rating_Score; }


    // function
    void WriteToFile(Member member) {
    ofstream outputFile("Member.dat", ios::app);
    if (outputFile.is_open()) {
        outputFile << member.getUsername() << "," << member.getPassword() << "," << member.getFullName() << "," << member.getPhoneNumber() << "," << member.getEmail() << "," << member.getIDType() << "," << member.getIDNumber() << "," << member.getFee() << "," << member.getRatingScore() << endl;
        outputFile.close();
    } else {
        cout << "Unable to open file" << endl;
    }
}
};

struct Node{
    Member m;
    Node* nextMember;
};

typedef struct Node *nd;



