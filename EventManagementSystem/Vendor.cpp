#include "Vendor.h"

Vendor::Vendor(string n, int vendorId, string category, string contact) : name(n), id(vendorId), productCategory(category), contactInfo(contact) {}

void Vendor::get_details()
{
    cout << "Vendor: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Category: " << productCategory << endl;
    cout << "Contact: " << contactInfo << endl;
}
