#include <iostream>
#include <string>
using namespace std;

class School
{
private:
    string name;

public:
    School(string s);
    string toString();
    void rename(string newName)
    {
        name = newName;
    }
    ~School()
    {
        cout << "School - Des" << endl;
    }
};

School::School(string s)
{
    name = s;
}

string School::toString()
{
    return name;
}

class Student
{
private:
    string id;
    string name;
    School *mySchool;

public:
    Student(string a, string b, School *s);
    string toString();
    ~Student()
    {
        // // ver 1
        // delete mySchool;
        // mySchool = nullptr;

        // // ver 2
        // mySchool = nullptr;

        // // ver 3 => rename() problem
        // delete mySchool;
        // mySchool = nullptr;

        // ver 4
        // Do nothing
    }
};

// ver 1 + ver 2: shallow copy
Student::Student(string a, string b, School *s)
{
    this->id = a;
    this->name = b;
    this->mySchool = s;
}

// // ver 3: deep copy => rename() problem
// Student::Student(string a, string b, School *s){
//     this->id = a;
//     this->name = b;
//     mySchool = new School(*s);
// }

string Student::toString()
{
    string s = "ID: " + id + "\n";
    s += "Name: " + name + "\n";
    s += "School: " + mySchool->toString() + "\n";
    return s;
}

int main()
{
    School *hcmus = new School("HCMUS");

    Student st1("1", "Nguyen Van A", hcmus);
    Student st2("2", "Tran Thi B", hcmus);

    cout << st1.toString() << endl;
    cout << st2.toString() << endl;

    hcmus->rename("HCMUNS");
    cout << st1.toString() << endl;
    cout << st2.toString() << endl;

    delete hcmus;

    return 0;
}

// ID: 1
// Name: Nguyen Van A
// School: HCMUS

// ID: 2
// Name: Tran Thi B
// School: HCMUS

// ID: 1
// Name: Nguyen Van A
// School: HCMUS

// ID: 2
// Name: Tran Thi B
// School: HCMUS

// School - Des
// School - Des

// ID: 1
// Name: Nguyen Van A
// School: HCMUS

// ID: 2
// Name: Tran Thi B
// School: HCMUS

// School - Des
// School - Des

// ID: 1
// Name: Nguyen Van A
// School: HCMUS

// ID: 2
// Name: Tran Thi B
// School: HCMUS

// School - Des
// School - Des
// zsh: trace trap  ./W04P01