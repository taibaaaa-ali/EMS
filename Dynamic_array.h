#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
using namespace std;

template <typename T>
class Dynamic_array
{
    T* arr;
    int len;
    int cap;

    void double_capacity()
    {
        cap = (cap == 0 ? 1 : cap * 2);
        T* temp = new T[cap];
        if (arr)
        {
            for (int i = 0; i < len; i++)
                temp[i] = arr[i];
            delete[] arr;
        }
        arr = temp;
    }

public:
    Dynamic_array()
        : arr(nullptr), len(0), cap(0)
    {
        arr = new T[cap];
    }

    Dynamic_array(int count, const T& value)
        : len(count),
        cap(count * 2 > 4 ? count * 2 : 4)
    {
        arr = new T[cap];
        for (int i = 0; i < len; i++)
            arr[i] = value;
    }

    Dynamic_array(const Dynamic_array<T>& other)
        : len(other.len),
        cap(other.cap)
    {
        arr = new T[cap];
        for (int i = 0; i < len; i++)
            arr[i] = other.arr[i];
    }

    Dynamic_array<T>& operator=(const Dynamic_array<T>& other)
    {
        if (this != &other)
        {
            delete[] arr;
            len = other.len;
            cap = other.cap;
            arr = new T[cap];
            for (int i = 0; i < len; i++)
                arr[i] = other.arr[i];
        }
        return *this;
    }

    ~Dynamic_array()
    {
        delete[] arr;
    }

    T& operator[](int index) { return arr[index]; }
    const T& operator[](int index) const { return arr[index]; }

    void push(const T& item)
    {
        if (len >= cap)
            double_capacity();
        arr[len++] = item;
    }

    void pop()
    {
        if (len > 0)
            len--;
    }

    void delete_at(int index)
    {
        if (index < 0 || index >= len)
            return;
        for (int i = index; i < len - 1; i++)
            arr[i] = arr[i + 1];
        len--;
    }

    int size() const { return len; }

    bool empty() const { return len == 0; }

    void clear() { len = 0; }

    T& back() { return arr[len - 1]; }
    const T& back() const { return arr[len - 1]; }

    int find(const T& value) const
    {
        for (int i = 0; i < len; i++)
            if (arr[i] == value)
                return i;
        return -1;
    }
};

#endif
