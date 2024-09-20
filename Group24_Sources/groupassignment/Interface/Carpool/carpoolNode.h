#ifndef CARPOOLNODE_H
#define CARPOOLNODE_H

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
#include <queue>
#include <stack>

using namespace std;

class Carpool;

class CarpoolNode
{
public:
    Carpool *carpool;
    CarpoolNode *next;

    CarpoolNode(Carpool* carpool) : carpool(carpool), next(nullptr) {}
};

#endif