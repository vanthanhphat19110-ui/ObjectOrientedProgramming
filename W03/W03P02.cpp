#include <iostream>
using namespace std;

class IntArray
{
private:
    int *arr;
    int sizeArr;

public:
    // Default constructor.
    IntArray()
    {
        cout << "IntArray -> Default constructor.\n";
        arr = nullptr;
        sizeArr = 0;
    }

    // Copy constructor: deep copy.
    IntArray(const IntArray &other)
    {
        cout << "IntArray -> Copy constructor.\n";
        sizeArr = other.sizeArr;
        arr = new int[sizeArr];

        for (int i = 0; i < sizeArr; i++)
            arr[i] = other.arr[i];
    }

    // Copy assignment operator: deep copy.
    IntArray &operator=(const IntArray &other)
    {
        cout << "IntArray -> Copy assignment operator.\n";
        if (this == &other)
            return *this;

        if (arr != nullptr)
        {
            delete[] arr;
            arr = nullptr;
            sizeArr = 0;
        }

        sizeArr = other.sizeArr;
        arr = new int[sizeArr];

        for (int i = 0; i < sizeArr; i++)
            arr[i] = other.arr[i];

        return *this;
    }

    // // Move constructor.
    // IntArray(IntArray &&other) noexcept
    // {
    //     cout << "IntArray -> Move constructor.\n";
    //     if (arr != nullptr)
    //     {
    //         delete[] arr;
    //         arr = nullptr;
    //         sizeArr = 0;
    //     }
    //     arr = other.arr;
    //     sizeArr = other.sizeArr;
    //     other.arr = nullptr;
    //     other.sizeArr = 0;
    // }

    // // Move assignment operator.
    // IntArray &operator=(IntArray &&other) noexcept
    // {
    //     cout << "IntArray -> Move assignment operator.\n";
    //     if (this != &other)
    //     {
    //         if (arr != nullptr)
    //         {
    //             delete[] arr;
    //             arr = nullptr;
    //             sizeArr = 0;
    //         }
    //         arr = other.arr;
    //         sizeArr = other.sizeArr;
    //         other.arr = nullptr;
    //         other.sizeArr = 0;
    //     }
    //     return *this;
    // }

    // Destructor.
    ~IntArray()
    {
        if (arr != nullptr)
        {
            cout << "IntArray -> Destructor.\n";
            delete[] arr;
            arr = nullptr;
            sizeArr = 0;
        }
    }

    void input()
    {
        cout << "- Input size: ";
        cin >> sizeArr;
        arr = new int[sizeArr];

        cout << "- Input array: ";
        for (int i = 0; i < sizeArr; i++)
            cin >> arr[i];
    }

    void output()
    {
        if (arr == nullptr)
        {
            cout << "- Array is empty.\n";
            return;
        }

        cout << "- Array: ";
        for (int i = 0; i < sizeArr - 1; i++)
            cout << arr[i] << ", ";
        cout << arr[sizeArr - 1] << ".\n";
    }
};

int main()
{
    // IntArray m1;
    // m1.input();
    // m1.output();

    // Kết quả:
    // IntArray -> Default constructor.
    // - Input size: 5
    // - Input array: 10 20 30 40 50
    // - Array: 10, 20, 30, 40, 50.
    // IntArray -> Destructor.

    // IntArray m2(m1);
    // m2.output();

    // Kết quả:
    // IntArray -> Default constructor.
    // - Input size: 5
    // - Input array: 10 20 30 40 50
    // - Array: 10, 20, 30, 40, 50.
    // IntArray -> Copy constructor.
    // - Array: 10, 20, 30, 40, 50.
    // IntArray -> Destructor.
    // IntArray -> Destructor.

    // IntArray m3;
    // m3 = m1;
    // m3.output();

    // Kết quả:
    // IntArray -> Default constructor.
    // - Input size: 5
    // - Input array: 10 20 30 40 50
    // - Array: 10, 20, 30, 40, 50.
    // IntArray -> Default constructor.
    // IntArray -> Copy assignment operator.
    // - Array: 10, 20, 30, 40, 50.
    // IntArray -> Destructor.
    // IntArray -> Destructor.

    return 0;
}