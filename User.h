#ifndef USER_H
#define USER_H

#include "myString.h"
#include <iostream>
using namespace std;

class User
{
protected:
    myString name;
    int id;
    myString password;

public:
    User();
    User(myString n, int i);
    User(myString n, int i, myString pass);

    virtual ~User() {}

    virtual void print_details() const;

    int getID() const;
    myString getName() const;
    bool login(int inputID, myString inputPass) const;
};

User::User() : name(""), id(0), password("") {}

User::User(myString n, int i) : name(n), id(i), password("") {}

User::User(myString n, int i, myString pass) : name(n), id(i), password(pass) {}

void User::print_details() const
{
    cout << "User Name: ";
    name.print();
    cout << endl;
    cout << "User ID: " << id << endl;
}

int User::getID() const
{
    return id;
}

myString User::getName() const
{
    return name;
}

bool User::login(int inputID, myString inputPass) const
{
    return id == inputID && password.equal(inputPass);
}

#endif
