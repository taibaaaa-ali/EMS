#include "Package.h"

Package::Package(string n, int packageId, string sz, float p): name(n), id(packageId), size(sz), price(p) {}

void Package::get_package_details()
{
    cout << "Package: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Size: " << size << endl;
    cout << "Price: $" << price << endl;
}

float Package::getPrice() const
{
    return price;
}