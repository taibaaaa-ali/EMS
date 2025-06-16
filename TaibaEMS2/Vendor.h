#ifndef VENDOR_H
#define VENDOR_H

#include <iostream>
#include <fstream>
#include "User.h"
#include "myString.h"
using namespace std;

class Vendor : public User
{
    myString productCategory;
    myString contactInfo;

public:
    Vendor();
    Vendor(myString n, int vendorId, myString category, myString contact, myString pass);

    void print_details() const override;
    myString getProductCategory() const;
    myString getContactInfo() const;

    void writeToFile(ofstream& out) const;
    bool readFromFile(ifstream& in);
};

Vendor::Vendor() : User(), productCategory(""), contactInfo("") {}

Vendor::Vendor(myString n, int vendorId, myString category, myString contact, myString pass)
    : User(n, vendorId, pass), productCategory(category), contactInfo(contact)
{
}

void Vendor::print_details() const
{
    cout << "Vendor Name: ";
    name.print();
    cout << endl;
    cout << "Vendor ID: " << id << endl;
    cout << "Category: ";
    productCategory.print();
    cout << endl;
    cout << "Contact: ";
    contactInfo.print();
    cout << endl;
}

myString Vendor::getProductCategory() const
{
    return productCategory;
}

myString Vendor::getContactInfo() const
{
    return contactInfo;
}

void Vendor::writeToFile(ofstream& out) const
{
    out << id << ",";

    for (int i = 0; i < name.length(); i++)
        out << name.charAt(i);
    out << ",";

    for (int i = 0; i < productCategory.length(); i++)
        out << productCategory.charAt(i);
    out << ",";

    for (int i = 0; i < contactInfo.length(); i++)
        out << contactInfo.charAt(i);
    out << ",";

    for (int i = 0; i < password.length(); i++)
        out << password.charAt(i);
    out << "\n";
}

bool Vendor::readFromFile(ifstream& in)
{
    char line[250];
    if (!in.getline(line, 250))
        return false;

    int field = 0, i = 0, bufIdx = 0;
    char buffer[100];
    char nameBuf[100] = {}, catBuf[100] = {}, contactBuf[100] = {}, passBuf[100] = {};
    int vid = 0;

    while (line[i] != '\0')
    {
        if (line[i] != ',' && line[i] != '\n')
        {
            buffer[bufIdx++] = line[i];
        }
        else
        {
            buffer[bufIdx] = '\0';

            if (field == 0)
                vid = atoi(buffer);
            else if (field == 1)
                for (int j = 0; j <= bufIdx; j++) nameBuf[j] = buffer[j];
            else if (field == 2)
                for (int j = 0; j <= bufIdx; j++) catBuf[j] = buffer[j];
            else if (field == 3)
                for (int j = 0; j <= bufIdx; j++) contactBuf[j] = buffer[j];
            else if (field == 4)
                for (int j = 0; j <= bufIdx; j++) passBuf[j] = buffer[j];

            field++;
            bufIdx = 0;
        }
        i++;
    }

    if (bufIdx > 0 && field == 4)
    {
        buffer[bufIdx] = '\0';
        for (int j = 0; j <= bufIdx; j++) passBuf[j] = buffer[j];
    }

    id = vid;
    name = myString(nameBuf);
    productCategory = myString(catBuf);
    contactInfo = myString(contactBuf);
    password = myString(passBuf);

    return true;
}

#endif
