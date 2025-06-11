#include "ExtraService.h"

ExtraService::ExtraService(int id, string n, string desc, float price)
    : serviceID(id), name(n), description(desc), unitPrice(price) {
}

void ExtraService::get_service_info()
{
    cout << "Service: " << name << endl;
    cout << "ID: " << serviceID << endl;
    cout << "Description: " << description << endl;
    cout << "Unit Price: $" << unitPrice << endl;
}

float ExtraService::get_price()
{
    return unitPrice;
}
