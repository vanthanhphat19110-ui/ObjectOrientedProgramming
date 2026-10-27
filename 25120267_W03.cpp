#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
const float EPS = 0.001;

class CStudent
{
private:
    string m_Name;
    string m_ID;
    vector<pair<string, pair<int, float>>> m_Subjects;

public:
    CStudent();
    CStudent(const CStudent &other);
    CStudent(const string &name, const string &id);

    string getName() { return m_Name; }
    string getId() { return m_ID; }

    friend istream &operator>>(istream &in, CStudent &student);
    friend ostream &operator<<(ostream &out, const CStudent &student);

    float AverageGrade() const;

    bool operator>(const CStudent &other);
    bool operator>=(const CStudent &other);
    bool operator==(const CStudent &other);
    bool operator<(const CStudent &other);
    bool operator<=(const CStudent &other);
};

CStudent::CStudent()
{
    m_Name = "";
    m_ID = "";
}

CStudent::CStudent(const CStudent &other)
{
    m_Name = other.m_Name;
    m_ID = other.m_ID;
    m_Subjects = other.m_Subjects;
}

CStudent::CStudent(const string &name, const string &id)
{
    m_Name = name;
    m_ID = id;
}

istream &operator>>(istream &in, CStudent &student)
{
    cout << "+ Nhap ho ten sinh vien: ";
    in >> student.m_Name;

    cout << "+ Nhap ma so sinh vien: ";
    in >> student.m_ID;

    int numberOfSubjects;
    cout << "+ Nhap so mon hoc: ";
    in >> numberOfSubjects;

    for (int i = 0; i < numberOfSubjects; i++)
    {
        cout << "+ Nhap ma mon hoc thu " << i + 1 << ": ";
        in >> student.m_Subjects[i].first;

        cout << "+ Nhap so tin chi mon hoc thu " << i + 1 << ": ";
        in >> student.m_Subjects[i].second.first;

        cout << "+ Nhap diem mon hoc thu " << i + 1 << ": ";
        in >> student.m_Subjects[i].second.second;
    }

    return in;
}

float CStudent::AverageGrade() const
{
    int n = m_Subjects.size();
    int tongTinChi = 0;
    float tongDiem = 0;
    for (int i = 0; i < n; i++)
    {
        int soTinChi = m_Subjects[i].second.first;
        float diem = m_Subjects[i].second.second;
        tongDiem += diem * soTinChi;
        tongTinChi += soTinChi;
    }
    float diemTrungBinh = tongDiem / tongTinChi;

    return diemTrungBinh;
}

ostream &operator<<(ostream &out, const CStudent &student)
{
    out << "+ Ho ten sinh vien: " << student.m_Name << ".\n"
        << "+ Ma so sinh vien: " << student.m_ID << ".\n"
        << "+ Danh sach mon hoc:\n";

    int n = student.m_Subjects.size();
    for (int i = 0; i < n; i++)
    {
        string maMonHoc = student.m_Subjects[i].first;
        int soTinChi = student.m_Subjects[i].second.first;
        float diem = student.m_Subjects[i].second.second;

        out << "    . Ma mon hoc: " << maMonHoc << ".\n"
            << "    . So tin chi: " << soTinChi << ".\n"
            << "    . Diem mon hoc: " << diem << ".\n\n";
    }

    out << "+ Diem trung binh: " << student.AverageGrade() << ".\n";

    return out;
}

bool CStudent::operator>(const CStudent &other)
{
    return (this->AverageGrade() - other.AverageGrade()) >= EPS;
}

bool CStudent::operator<(const CStudent &other)
{
    return (this->AverageGrade() - other.AverageGrade()) <= -EPS;
}

bool CStudent::operator==(const CStudent &other)
{
    return fabs(this->AverageGrade() - other.AverageGrade()) < EPS;
}

bool CStudent::operator>=(const CStudent &other)
{
    return *this > other || *this == other;
}

bool CStudent::operator<=(const CStudent &other)
{
    return *this < other || *this == other;
}

class CListStudent
{
private:
    vector<CStudent> m_Students;

public:
    void Input();
    void Output();

    CStudent FindMaxAverageStudent();
    CStudent FindMinAverageStudent();

    void SortAscending();
    void SortDescending();

    void DeleteStudent(string id);
    CStudent FindStudent(string id);
    void ClassifyStudent();
};

void CListStudent::Input()
{
    int n;
    cout << "- Nhap so luong sinh vien: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "- Nhap sinh vien thu " << i + 1 << ":\n";
        cin >> m_Students[i];
    }
}

void CListStudent::Output()
{
    int n = m_Students.size();
    for (int i = 0; i < n; i++)
    {
        cout << "- Sinh vien thu " << i + 1 << ":\n";
        cout << m_Students[i];
    }
}

CStudent CListStudent::FindMaxAverageStudent()
{
    if (m_Students.empty())
    {
        cout << "List of students is empty.\n";
        return CStudent();
    }

    CStudent ans = m_Students[0];
    int n = m_Students.size();

    for (int i = 1; i < n; i++)
    {
        if (m_Students[i] > ans)
            ans = m_Students[i];
    }

    return ans;
}

CStudent CListStudent::FindMinAverageStudent()
{
    if (m_Students.empty())
    {
        cout << "List of students is empty.\n";
        return CStudent();
    }

    CStudent ans = m_Students[0];
    int n = m_Students.size();

    for (int i = 1; i < n; i++)
    {
        if (m_Students[i] < ans)
            ans = m_Students[i];
    }

    return ans;
}

void CListStudent::SortAscending()
{
    int n = m_Students.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = i; j < n - 1 - i; j++)
        {
            if (m_Students[j] > m_Students[j + 1])
            {
                CStudent temp = m_Students[j];
                m_Students[j] = m_Students[j + 1];
                m_Students[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void CListStudent::SortDescending()
{
    int n = m_Students.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = i; j < n - 1 - i; j++)
        {
            if (m_Students[j] < m_Students[j + 1])
            {
                CStudent temp = m_Students[j];
                m_Students[j] = m_Students[j + 1];
                m_Students[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void CListStudent::DeleteStudent(string id)
{
    bool found = false;
    for (auto it = m_Students.begin(); it != m_Students.end(); it++)
    {
        if (it->getId() == id)
        {
            found = true;
            m_Students.erase(it);
            cout << "Da xoa sinh vien co ma so: " << id << ".\n";
            break;
        }
    }

    if (!found)
        cout << "Khong tim thay sinh vien co ma so " << id << ".\n";
}

CStudent CListStudent::FindStudent(string id)
{
    int n = m_Students.size();
    CStudent ans;
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        if (m_Students[i].getId() == id)
        {
            found = true;
            ans = m_Students[i];
            break;
        }
    }

    if (!found)
        cout << "Khong tim thay id.\n";

    return ans;
}

void CListStudent::ClassifyStudent()
{
    int n = m_Students.size();
    for (int i = 0; i < n; i++)
    {
        string name = m_Students[i].getName();
        string id = m_Students[i].getId();
        float diemTrungBinh = m_Students[i].AverageGrade();

        cout << "- Ho ten sinh vien: " << name << ".\n"
             << "- Ma so sinh vien: " << id << ".\n"
             << "- Diem trung binh: " << diemTrungBinh << ".\n"
             << "- Hoc luc: ";

        if ((diemTrungBinh - 9 >= EPS || fabs(diemTrungBinh - 9) < EPS) && (diemTrungBinh - 10 <= -EPS || fabs(diemTrungBinh - 10) < EPS))
            cout << "Loai Xuat sac.\n\n";
        else if (diemTrungBinh - 8 >= EPS || fabs(diemTrungBinh - 8) < EPS)
            cout << "Loai Gioi.\n\n";
        else if (diemTrungBinh - 7 >= EPS || fabs(diemTrungBinh - 7) < EPS)
            cout << "Loai Kha.\n\n";
        else if (diemTrungBinh - 6 >= EPS || fabs(diemTrungBinh - 6) < EPS)
            cout << "Loai Trung binh kha.\n\n";
        else if (diemTrungBinh - 5 >= EPS || fabs(diemTrungBinh - 5) < EPS)
            cout << "Loai Trung binh.\n\n";
        else if (diemTrungBinh - 4 >= EPS || fabs(diemTrungBinh - 4) < EPS)
            cout << "Loai Kem.\n\n";
        else
            cout << "Khong xep loai.\n\n";
    }
}

int main()
{
    return 0;
}