#include <iostream>
using namespace std;
#include "myString.h"

class Package
{
    myString name;
    int id;
    myString size;
    float price;

public:
    Package();
    Package(myString n, int packageId, myString sz, float p);

    void get_package_details();
    float getPrice() const;
};

Package::Package() : name(""), id(0), size(""), price(0) {}

Package::Package(myString n, int packageId, myString sz, float p)
    : name(n), id(packageId), size(sz), price(p) {
}

void Package::get_package_details()
{
    cout << "Package: ";
    name.print();
    cout << endl;
    cout << "ID: " << id << endl;
    cout << "Size: ";
    size.print();
    cout << endl;
    cout << "Price: $" << price << endl;
}

float Package::getPrice() const
{
    return price;
}
