#include <iostream>
#include <string>
using namespace std;

// Câu 02:
class IFace
{
public:
    virtual void show() = 0;
    virtual IFace *clone() = 0;
    virtual ~IFace() {};
};

class Face : public IFace
{
private:
    string shape;

protected:
    string getShape() { return shape; }

public:
    Face(const string &sh) : shape(sh) {};

    virtual void show() override { cout << "Shape: " << shape << endl; }

    virtual IFace *clone() override
    {
        Face *ans = new Face(*this);
        return ans;
    }
};

class EyedFace : public Face
{
private:
    int eyes;
    static int count;

public:
    EyedFace() : Face::Face("Unknown"), eyes(0) { count++; }
    EyedFace(const string &sh, int eyes) : Face::Face(sh), eyes(eyes) { count++; }
    EyedFace(const EyedFace &other) : Face::Face(other), eyes(other.eyes) { count++; }
    ~EyedFace() { count--; }

    static int getCount() { return count; }

    virtual void show() override
    {
        Face::show();
        cout << "Eyes: " << eyes << endl;
    }

    virtual IFace *clone() override
    {
        EyedFace *ans = new EyedFace(*this);
        return ans;
    }
};

void testFace(IFace *fc)
{
    IFace *a[3] = {fc, fc->clone(), fc->clone()};
    for (int i = 0; i < 3; i++)
        a[i]->show();
    cout << "The same 3 lines ?" << endl;

    delete a[1];
    delete a[2];
}

int EyedFace::count = 0;

int main()
{
    Face fc1("Rectangle");
    testFace(&fc1);
    cout << "So doi tuong EyedFace con lai trong bo nho la: " << EyedFace::getCount() << endl;
    return 0;
}