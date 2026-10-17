#include <iostream>
#include <cstring>
using namespace std;

class MyString
{
private:
    char *pString;
    int length;

public:
    MyString() : pString(nullptr), length(0) {};

    MyString(const MyString &other)
    {
        length = other.length;
        pString = new char[length + 1];

        for (int i = 0; i < length; i++)
            pString[i] = other.pString[i];
        pString[length] = '\0';
    }

    MyString(const char *str)
    {
        if (str == nullptr)
        {
            pString = nullptr;
            length = 0;
        }
        else
        {
            length = strlen(str);
            pString = new char[length + 1];
            for (int i = 0; i < length; i++)
                pString[i] = str[i];
            pString[length] = '\0';
        }
    }

    ~MyString()
    {
        if (pString != nullptr)
        {
            delete[] pString;
            pString = nullptr;
            length = 0;
        }
    }

    bool operator==(const MyString &other) const
    {
        if (this == &other)
            return true;

        if (length != other.length)
            return false;

        for (int i = 0; i < length; i++)
        {
            if (pString[i] != other.pString[i])
                return false;
        }

        return true;
    }

    MyString &operator+=(const MyString &other)
    {
        if (other.pString == nullptr)
            return *this;

        char *temp = new char[length + other.length + 1];
        for (int i = 0; i < length; i++)
            temp[i] = pString[i];
        for (int i = 0; i < other.length; i++)
            temp[length + i] = other.pString[i];

        length += other.length;
        delete[] pString;
        pString = temp;
        pString[length] = '\0';

        return *this;
    }

    MyString &operator=(const MyString &other)
    {
        if (this == &other)
            return *this;

        if (pString != nullptr)
        {
            delete[] pString;
            pString = nullptr;
            length = 0;
        }

        length = other.length;
        pString = new char[length + 1];
        for (int i = 0; i < length; i++)
            pString[i] = other.pString[i];
        pString[length] = '\0';

        return *this;
    }

    friend ostream &operator<<(ostream &out, const MyString &s);
};

ostream &operator<<(ostream &out, const MyString &s)
{
    for (int i = 0; i < s.length; i++)
        out << s.pString[i];
    return out;
}