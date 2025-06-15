#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "User.h"
#include "myString.h"
using namespace std;

class Manager : public User
{
    myString email;
    myString phone;

public:
    Manager();
    Manager(myString n, int managerId, myString mail, myString phoneNum, myString pass);

    void print_details() const override;
    myString getEmail() const;
    myString getPhone() const;
};

Manager::Manager() : User(), email(""), phone("") {}

Manager::Manager(myString n, int managerId, myString mail, myString phoneNum, myString pass)
    : User(n, managerId, pass), email(mail), phone(phoneNum)
{
}

void Manager::print_details() const
{
    cout << "Manager Name: ";
    name.print();
    cout << endl;
    cout << "Manager ID: " << id << endl;
    cout << "Email: ";
    email.print();
    cout << endl;
    cout << "Phone: ";
    phone.print();
    cout << endl;
}

myString Manager::getEmail() const
{
    return email;
}

myString Manager::getPhone() const
{
    return phone;
}

#endif
