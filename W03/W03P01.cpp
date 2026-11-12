#include <iostream>
using namespace std;

class Fraction
{
private:
    int num, denom;

public:
    Fraction() : num(0), denom(1) {};

    Fraction(int tu, int mau) : num(tu), denom(mau) {};

    string toString() { return to_string(num) + "/" + to_string(denom); }

    Fraction operator+(const Fraction &other)
    {
        int tu = num * other.denom + denom * other.num;
        int mau = denom * other.denom;
        return Fraction(tu, mau);
    }

    Fraction operator+(int x) const { return Fraction(num + denom * x, denom); }

    // Hàm friend: cho phép truy cập vào private của class.
    friend Fraction operator+(int x, const Fraction &f);

    Fraction &operator+=(const Fraction &other)
    {
        num = num * other.denom + denom * other.num;
        denom = denom * other.denom;
        return *this;
    }

    Fraction &operator+=(int x)
    {
        num = num + denom * x;
        return *this;
    }

    friend istream &operator>>(istream &in, Fraction &f);
    friend ostream &operator<<(ostream &out, const Fraction &f);
};

Fraction operator+(int x, const Fraction &f) { return Fraction(x * f.denom + f.num, f.denom); }

istream &operator>>(istream &in, Fraction &f)
{
    in >> f.num >> f.denom;
    return in;
}

ostream &operator<<(ostream &out, const Fraction &f)
{
    out << f.num << "/" << f.denom;
    return out;
}

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

    // Fraction p8(5, 6);
    // Fraction p9 = 5 + p8;
    // cout << "p9 = " << p9.toString() << ".\n";

    // Kết quả:
    // p9 = 35/6.

    // Fraction p10, p11;
    // cout << "Input p10, p11: ";
    // cin >> p10 >> p11;
    // cout << "p10 = " << p10 << ", p11 = " << p11 << ".\n";

    // Kết quả:
    // Input p10, p11: 4 5 9 10
    // p10 = 4/5, p11 = 9/10.

    return 0;
}