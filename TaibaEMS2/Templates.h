#include <iostream>
#include "Dynamic_array.h"
using namespace std;

template <typename T>
class Templates
{
public:
    // Search by ID (requires T to have getID())
    static int findByID(const Dynamic_array<T>& arr, int id)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            if (arr[i].getID() == id)
                return i;
        }
        return -1;
    }

    // Print all (requires T to have print_details())
    static void printAll(const Dynamic_array<T>& arr)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            arr[i].print_details();
            cout << endl;
        }
    }
};


