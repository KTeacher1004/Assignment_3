#ifndef NODE_H
#define NODE_H
using namespace std;

class Handling{
    private:
    string id, name, status;
    public:
    Handling(){}
    Handling(string id, string name, string status){this->id = id,  this->name = name, this->status = status;}
    void setID(string id){
        this->id = id;
    }
    void setName(string name){
        this->name = name;
    }
    void  setStatus(string status){
        this->status = status;
    }
    string getId(){return id;}
    string getName(){return name;}
    string getStatus(){return status;}
};

struct Node1{
    Handling data;
    Node1 *next;
};

typedef struct Node1 *nd;

#endif  // NODE_H