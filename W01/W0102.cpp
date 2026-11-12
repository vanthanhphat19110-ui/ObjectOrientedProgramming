#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Point2D
{
private:
    double x, y;

public:
    Point2D(double x, double y) : x(x), y(y) {};
    Point2D() : x(0), y(0) {};

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }

    void input()
    {
        cin >> x >> y;
    }

    string toString()
    {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
    }

    double EuclideDistanceTo(const Point2D &A)
    {
        return sqrt(pow(A.x - x, 2) + pow(A.y - y, 2));
    }

    double ManhattanDistanceTo(const Point2D &A)
    {
        return fabs(A.x - x) + fabs(A.y - y);
    }

    double CosineDistanceTo(const Point2D &A)
    {
        double EPS = 1e-6;
        double len1 = sqrt(x * x + y * y);
        double len2 = sqrt(A.x * A.x + A.y * A.y);
        if (len1 < EPS || len2 < EPS)
            return 0.0;

        double dotProduct = x * A.x + y * A.y;
        double cosineSimilarity = dotProduct / (len1 * len2);
        if (cosineSimilarity > 1.0)
            cosineSimilarity = 1.0;
        if (cosineSimilarity < -1.0)
            cosineSimilarity = -1.0;
        return 1 - cosineSimilarity;
    }
};

class Triangle
{
private:
    Point2D A, B, C;

public:
    Triangle(Point2D A, Point2D B, Point2D C) : A(A), B(B), C(C) {};

    void input()
    {
        A.input();
        B.input();
        C.input();
    }

    string toString()
    {
        return A.toString() + ", " + B.toString() + ", " + C.toString();
    }

    string classify()
    {
        double a = B.EuclideDistanceTo(C);
        double b = C.EuclideDistanceTo(A);
        double c = A.EuclideDistanceTo(B);
        double EPS = 1e-6;

        if (b + c - a <= EPS || c + a - b <= EPS || a + b - c <= EPS)
            return "Not a triangle"; // Không phải là tam giác

        bool abIsEqual = fabs(b - a) < EPS;
        bool bcIsEqual = fabs(c - b) < EPS;
        bool caIsEqual = fabs(a - c) < EPS;

        if (abIsEqual && bcIsEqual)
            return "An equilateral triangle"; // Tam giác đều

        bool isRightAngled = fabs(b * b + c * c - a * a) < EPS || fabs(c * c + a * a - b * b) < EPS || fabs(a * a + b * b - c * c) < EPS;
        bool isIsosceles = abIsEqual || bcIsEqual || caIsEqual;

        if (isRightAngled && isIsosceles)
            return "An isosceles right triangle"; // Tam giác vuông cân

        if (isRightAngled)
            return "A right-angled triangle"; // Tam giác vuông

        if (isIsosceles)
            return "An isosceles triangle"; // Tam giác cân

        return "An ordinary triangle"; // Tam giác thường
    }

    double perimeter()
    {
        double a = B.EuclideDistanceTo(C);
        double b = C.EuclideDistanceTo(A);
        double c = A.EuclideDistanceTo(B);
        return a + b + c;
    }

    double area()
    {
        double a = B.EuclideDistanceTo(C);
        double b = C.EuclideDistanceTo(A);
        double c = A.EuclideDistanceTo(B);
        double p = (a + b + c) / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }
};