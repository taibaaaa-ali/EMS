#pragma once
#include <iostream>
#include <string>
using namespace std;

class ExtraService
{
protected:
    int serviceID;
    string name;
    string description;
    float unitPrice;

public:
    ExtraService(int id = 0, string n = "", string desc = "", float price = 0);
    void get_service_info();
    float get_price() const;
};