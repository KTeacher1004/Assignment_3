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
#include "../Class/Node.h"

using namespace std;


void readFromFile(nd &head, const string& filename){
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while(getline(file, line)){
        stringstream ss(line);  
        string name, status, id;

        getline(ss, id, ',');
        getline(ss,  name, ','); // name
        getline(ss,  status, ','); // status
        
        Handling m;
        m.setID(id);
        m.setName(name);
        m.setStatus(status);

        nd tmp = new Node1();
        tmp->data = m;
        tmp->next = NULL;
    
        if (head == NULL){
            head = tmp;
        }
        else {
            nd last = head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = tmp;
        }
    }
    file.close();
}

void writeToFile(nd head, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        nd temp = head;
        while (temp != nullptr) {
            file << temp->data.getId() << "," << temp->data.getName() << "," << temp->data.getStatus() << endl;
            temp = temp->next;
        }
        file.close();
    } else {
        cerr << "Unable to open file" << endl;
    }
}

void deleteNode(nd& head, string id, string name) {
    nd temp = head;
    nd prev = nullptr;

    if (temp != nullptr && temp->data.getId() == id && temp->data.getStatus() == "Pending" && temp->data.getName() == name) {
        head = temp->next;
        delete temp;
        return;
    }

    while (temp != nullptr && temp->data.getId() != id  && temp->data.getName() != name) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) return;

    prev->next = temp->next;
    delete temp;
}

nd returnND(){
    nd head = NULL;
    readFromFile(head, "AcceptingCarpool.txt");
    return head;
}

void print(Handling m){
    cout << "ID: " << m.getId() << endl;
    cout << "Name: " << m.getName() << endl;
    cout << "Status: " << m.getStatus() << endl;
}

void printls(nd a){
    while(a != NULL){
        print(a->data);
        a = a->next;
    }
}

void CancelOne(string name, string id){
    nd head = returnND();
    deleteNode(head,id, name);
    writeToFile(head,"AcceptingCarpool.txt");
}

