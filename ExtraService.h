#ifndef EXTRASERVICE_H
#define EXTRASERVICE_H

#include "myString.h"
#include <iostream>
using namespace std;

class ExtraService
{
    int id;
    myString name;
    myString description;
    float price;

public:
    ExtraService();
    ExtraService(int id, myString n, myString desc, float price);

    void get_service_info() const;
    float get_price() const;
};

ExtraService::ExtraService() : id(0), name(""), description(""), price(0.0f) {}

ExtraService::ExtraService(int id, myString n, myString desc, float price)
    : id(id), name(n), description(desc), price(price) {
}

void ExtraService::get_service_info() const
{
    cout << "Service: ";
    name.print();
    cout << endl;
    cout << "ID: " << id << endl;
    cout << "Description: ";
    description.print();
    cout << endl;
    cout << "Unit Price: $" << price << endl;
}

float ExtraService::get_price() const
{
    return price;
}

#endif
