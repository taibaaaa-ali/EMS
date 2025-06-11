#pragma once
#include <iostream>
#include <string>
using namespace std;

class Package
{
protected:
    string name;
    int id;
    string size;
    float price;

public:
    Package(string n = "", int packageId = 0, string sz = "", float p = 0);
    void get_package_details();
    float getPrice() const;
};