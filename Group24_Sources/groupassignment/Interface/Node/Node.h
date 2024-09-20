#ifndef NODE_H
#define NODE_H
#include "../Class/Node.h"
using namespace std;

void readFromFile(nd &head, const string& filename);
void writeToFile(nd head, const string& filename);
void deleteNode(nd& head, string id, string name);
void CancelOne(string name, string id);

#endif  // NODE_H