#pragma once
#include <iostream>
#include <string>
using namespace std;

class Stall
{
protected:
    int stallID;
    string size;
    int XCoord, YCoord;
    string zoneType;
    float basePrice;
    bool isBooked;

public:
    Stall();
    Stall(int id, string sz, int x, int y, string zone, float price);
    void book();
    void release();
    void stall_details();
};
