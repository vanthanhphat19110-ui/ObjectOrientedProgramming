#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Student
{
private:
    string id;

public:
    void setId(const string &id)
    {
        this->id = id;
    }

    string getId()
    {
        return id;
    }
};

class Point2D
{
private:
    double x, y;

public:
    Point2D() : x(0), y(0)
    {
        cout << "Point2D -> Default constructor.\n";
    }

    Point2D(const Point2D &p)
    {
        cout << "Point2D -> Copy constructor.\n";
        this->x = p.x;
        this->y = p.y;
    }

    Point2D(const double &m)
    {
        cout << "Point2D -> Constructor with 1 argument.\n";
        this->x = m;
        this->y = m;
    }

    Point2D(const double &x, const double &y)
    {
        cout << "Point2D -> Constructor with 2 arguments.\n";
        this->x = x;
        this->y = y;
    }

    // Point2D(Point2D &&other) noexcept : x(other.x), y(other.y)
    // {
    //     cout << "Point2D -> Move constructor.\n";
    //     other.x = 0.0;
    //     other.y = 0.0;
    // }

    ~Point2D()
    {
        cout << "Point2D -> Destructor.\n";
    }

    void setPoint(const double &x, const double &y)
    {
        this->x = x;
        this->y = y;
    }

    void setX(const double &x)
    {
        this->x = x;
    }

    void setY(const double &y)
    {
        this->y = y;
    }

    double getX()
    {
        return x;
    }

    double getY()
    {
        return y;
    }

    double distanceTo(const Point2D &p)
    {
        cout << "Point2D -> distanceTo().\n";
        double dx = x - p.x;
        double dy = y - p.y;
        return sqrt(dx * dx + dy * dy);
    }

    string toString()
    {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
    };
};

class Triangle
{
private:
    Point2D a, b, c;

public:
    Triangle() : a(0, 0), b(1, 0), c(0, 1)
    {
        cout << "Triangle -> Default constructor.\n";
    }

    Triangle(Point2D a, Point2D b, Point2D c)
    {
        cout << "Triangle -> Constructor with 3 arguments.\n";
        this->a = a;
        this->b = b;
        this->c = c;
    }

    // Triangle (Point2D a, Point2D b, Point2D c): a(a), b(b), c(c)
    // {
    //     cout << "Triangle -> Constructor with 3 arguments.\n";
    // }

    ~Triangle()
    {
        cout << "Triangle -> Destructor.\n";
    }
};

int main()
{
    // Point2D p1(1, 2);
    // cout << "p1 = " << p1.toString() << ".\n";

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // p1 = (1.000000, 2.000000).
    // Point2D -> Destructor.

    // Point2D p2(10);
    // cout << "p2 = " << p2.toString() << ".\n";

    // Kết quả:
    // Point2D -> Constructor with 1 argument.
    // p2 = (10.000000, 10.000000).
    // Point2D -> Destructor.

    // nếu không viết bất kì constructor nào hết thì sẽ gọi default constructor có sẵn.
    // Point2D p3;
    // cout << "p3 = " << p3.toString() << ".\n";

    // Kết quả:
    // Point2D -> Default constructor.
    // p3 = (0.000000, 0.000000).
    // Point2D -> Destructor.

    // Point2D p4(); // function p4()

    // nếu không viết copy constructor thì sẽ gọi copy constructor có sẵn.
    // Point2D p5(3, 4);
    // Point2D p6(p5);
    // cout << "p6 = " << p6.toString() << ".\n";

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Copy constructor.
    // p6 = (3.000000, 4.000000).
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Point2D p7(1, 2);
    // Point2D p8;
    // p8 = p7; // phép gán.
    // cout << "p8 = " << p8.toString() << ".\n";

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Default constructor.
    // p8 = (1.000000, 2.000000).
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Point2D p9(1, 2);
    // Point2D p10 = p9; // khởi tạo.
    // cout << "p10 = " << p10.toString() << ".\n";

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Copy constructor.
    // p10 = (1.000000, 2.000000).
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Point2D *p11;

    // Point2D *p12;
    // p12 = new Point2D;

    // Kết quả:
    // Point2D -> Default constructor.

    // Point2D *p13;
    // p13 = new Point2D;
    // delete p13;

    // Point2D -> Default constructor.
    // Point2D -> Destructor.

    // Point2D *p14;
    // p14 = new Point2D[5];

    // Kết quả:
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.

    // Point2D *p15;
    // p15 = new Point2D[5];
    // delete p15;

    // Kết quả:
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Destructor.

    // Point2D *p16;
    // p16 = new Point2D[5];
    // delete[] p16;

    // Kết quả:
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Point2D p17(1, 2);
    // Point2D *p18;
    // p18 = &p17;

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Destructor.

    // Point2D p19(1, 2);
    // Point2D p20 = std::move(p19);
    // cout << "p19 = " << p19.toString() << ".\n";
    // cout << "p20 = " << p20.toString() << ".\n";

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Move constructor.
    // p19 = (0.000000, 0.000000).
    // p20 = (1.000000, 2.000000).
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Point2D p21(1, 9);
    // vector<Point2D> p22;
    // p22.push_back(p21);

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Copy constructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // vector<Point2D> p23;
    // p23.push_back(Point2D(1, 9));

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Move constructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Point2D p24(1, 2);
    // Point2D p25(3, 4);
    // double d = p24.distanceTo(p25);
    // cout << "d = " << d << ".\n";

    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> distanceTo().
    // d = 2.82843.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // vector<Point2D> p26(5);

    // Kết quả:
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // vector<Point2D> p27[5];

    // vector<Point2D *> p28;

    // vector<Point2D *> p29(5);
    // p29[0] = new Point2D(1, 2);
    // p29[1] = new Point2D(3, 4);
    // p29[2] = p29[1];
    // p29[3] = new Point2D(1, 2);
    // p29[4] = new Point2D(3, 4);
    // delete p29[0];
    // delete p29[1];
    // delete p29[3];
    // delete p29[4];

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Triangle t1;

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Triangle -> Default constructor.
    // Triangle -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    // Point2D a(0, 5);
    // Point2D b(3, 0);
    // Point2D c(0, 4);
    // Triangle t2(a, b, c);

    // Kết quả:
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Constructor with 2 arguments.
    // Point2D -> Copy constructor.
    // Point2D -> Copy constructor.
    // Point2D -> Copy constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Point2D -> Default constructor.
    // Triangle -> Constructor with 3 arguments.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Triangle -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.
    // Point2D -> Destructor.

    return 0;
}