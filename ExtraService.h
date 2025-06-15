#include "myString.h"
#include <iostream>
using namespace std;

class ExtraService
{
    int serviceID;
    myString name;
    myString description;
    float unitPrice;

public:
    ExtraService();
    ExtraService(int id, myString n, myString desc, float price);

    void get_service_info() const;
    float get_price() const;
};

ExtraService::ExtraService() : serviceID(0), name(""), description(""), unitPrice(0.0f) {}

ExtraService::ExtraService(int id, myString n, myString desc, float price)
    : serviceID(id), name(n), description(desc), unitPrice(price) {
}

void ExtraService::get_service_info() const
{
    cout << "Service: ";
    name.print();
    cout << endl;
    cout << "ID: " << serviceID << endl;
    cout << "Description: ";
    description.print();
    cout << endl;
    cout << "Unit Price: $" << unitPrice << endl;
}

float ExtraService::get_price() const
{
    return unitPrice;
}

