#pragma once
#include <iostream>
#include <string>
using namespace std;

class Vendor
{
protected:
    string name;
    int id;
    string productCategory;
    string contactInfo;

public:
    Vendor(string n = "", int vendorId = 0, string category = "", string contact = "");
    void get_details();
};
