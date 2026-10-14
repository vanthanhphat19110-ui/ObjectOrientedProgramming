#include <iostream>
using namespace std;

class Fraction
{
private:
    int num, denom;

public:
    Fraction(int tu, int mau) : num(tu), denom(mau) {};

    string toString() { return to_string(num) + "/" + to_string(denom); }

    Fraction operator+(const Fraction &other)
    {
        int tu = num * other.denom + denom * other.num;
        int mau = denom * other.denom;
        return Fraction(tu, mau);
    }

    Fraction operator+(int x) const { return Fraction(num + denom * x, denom); }

    Fraction &operator+=(const Fraction &other)
    {
        num = num * other.denom + denom * other.num;
        denom = denom * other.denom;
        return *this;
    }
};

int main()
{
    // Fraction p1(1, 2), p2(3, 4);
    // Fraction p3 = p1 + p2;
    // cout << "p3 = " << p3.toString() << ".\n";

    // Kết quả:
    // p3 = 10/8.

    // Fraction p4(1, 2), p5(3, 4);
    // p4 += p5;
    // cout << "p4 = " << p4.toString() << ".\n";

    // Kết quả:
    // p4 = 10/8.

    // Fraction p6(4, 5);
    // Fraction p7 = p6 + 8;
    // cout << "p7 = " << p7.toString() << ".\n";

    // Kết quả:
    // p7 = 44/5.
}