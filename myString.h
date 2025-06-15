#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class myString
{
    char* Vs;
    int size;

public:
    myString();
    myString(char c);
    myString(const char* c);
    myString(const myString& s);
    ~myString();

    myString& operator=(const myString& s);

    void print() const;
    int length() const;
    int atoi() const;
    void itoa(int num);
    void trim();

    char charAt(int i) const;         // ✅ Fixed const
    char& charRefAt(int i);

    bool equal(const myString& a) const;
    int comparison(const myString& other) const;
};

myString::myString()
{
    size = 1;
    Vs = new char[size];
    Vs[0] = '\0';
}

myString::myString(char c)
{
    size = 2;
    Vs = new char[size];
    Vs[0] = c;
    Vs[1] = '\0';
}

myString::myString(const char* c)
{
    int count = 0;
    while (c[count] != '\0') count++;
    size = count + 1;
    Vs = new char[size];
    for (int i = 0; i < count; i++) Vs[i] = c[i];
    Vs[size - 1] = '\0';
}

myString::myString(const myString& s)
{
    size = s.size;
    Vs = new char[size];
    for (int i = 0; i < size; i++) Vs[i] = s.Vs[i];
}

myString::~myString()
{
    delete[] Vs;
}

myString& myString::operator=(const myString& s)
{
    if (this != &s)
    {
        delete[] Vs;
        size = s.size;
        Vs = new char[size];
        for (int i = 0; i < size; i++) Vs[i] = s.Vs[i];
    }
    return *this;
}

void myString::print() const
{
    std::cout << Vs;
}

int myString::length() const
{
    return size - 1;
}

int myString::atoi() const
{
    int num = 0;
    for (int i = 0; i < size - 1; i++)
    {
        if (Vs[i] >= '0' && Vs[i] <= '9')
            num = num * 10 + (Vs[i] - '0');
    }
    return num;
}

void myString::itoa(int num)
{
    int temp = num;
    size = 1;
    if (num == 0) size = 2;
    else while (temp > 0) { size++; temp /= 10; }

    Vs = new char[size];
    Vs[size - 1] = '\0';
    int idx = size - 2;

    if (num == 0) Vs[0] = '0';
    else while (num > 0 && idx >= 0)
    {
        Vs[idx--] = (num % 10) + '0';
        num /= 10;
    }
}

void myString::trim()
{
    int start = 0, end = size - 2;
    while ((Vs[start] == ' ' || Vs[start] == '\n') && start < end) start++;
    while ((Vs[end] == ' ' || Vs[end] == '\n') && end > start) end--;

    int newSize = end - start + 2;
    char* t = new char[newSize];
    for (int i = 0; i < newSize - 1; i++) t[i] = Vs[start + i];
    t[newSize - 1] = '\0';

    delete[] Vs;
    Vs = t;
    size = newSize;
}

char myString::charAt(int i) const  // ✅ Fixed
{
    return Vs[i];
}

char& myString::charRefAt(int i)
{
    return Vs[i];
}

bool myString::equal(const myString& a) const
{
    return comparison(a) == 0;
}

int myString::comparison(const myString& other) const
{
    int i = 0;
    while (Vs[i] != '\0' && other.Vs[i] != '\0')
    {
        if (Vs[i] != other.Vs[i])
            return Vs[i] - other.Vs[i];
        i++;
    }
    return Vs[i] - other.Vs[i];
}

#endif
