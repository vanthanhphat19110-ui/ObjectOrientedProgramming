#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
using namespace std;

class CMyTime
{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;

    // Support functions.
    long long totalSecond() const;
    static CMyTime tranferToTime(long long);

public:
    // Constructors.
    CMyTime();
    CMyTime(const CMyTime &other);
    CMyTime(int hour, int minute, int second);

    // IO operators.
    friend istream &operator>>(istream &in, CMyTime &time);
    friend ostream &operator<<(ostream &out, const CMyTime &time);

    // Đồng hồ xem giờ.
    CMyTime &operator++();      // tăng 1s (tiền tố)
    CMyTime operator--(int);    // giảm 1s (hậu tố)
    CMyTime &operator-=(int n); // giảm n giờ

    // Comparison operators.
    bool operator>(const CMyTime &other) const;
    bool operator<(const CMyTime &other) const;
    bool operator==(const CMyTime &other) const;
    bool operator>=(const CMyTime &other) const;
    bool operator<=(const CMyTime &other) const;

    void ShowTime();
    void CountDown();
    void RunStopwatch();

    // Đồng hồ thể thao.
    CMyTime &operator+=(int n);                    // tăng n giờ (vượt 24h)
    CMyTime operator+(const CMyTime &other) const; // cộng hai thời gian
    CMyTime operator-(const CMyTime &other) const; // trừ hai thời gian

    // Bài tập thêm.
    void readFile(const string &filename, vector<CMyTime> &myTimes);
};

// Constructors.
CMyTime::CMyTime() : m_Hour(0), m_Minute(0), m_Second(0) {};

CMyTime::CMyTime(const CMyTime &other)
{
    m_Hour = other.m_Hour;
    m_Minute = other.m_Minute;
    m_Second = other.m_Second;
}

CMyTime::CMyTime(int hour, int minute, int second)
{
    m_Hour = hour;
    m_Minute = minute;
    m_Second = second;
}

// Support functions.
long long CMyTime::totalSecond() const
{
    return (m_Hour * 3600 + m_Minute * 60 + m_Second);
}

CMyTime CMyTime::tranferToTime(long long totalSecond)
{
    int hour = totalSecond / 3600;
    totalSecond %= 3600;
    int minute = totalSecond / 60;
    int second = totalSecond % 60;
    return CMyTime(hour, minute, second);
}

// IO operators.
istream &operator>>(istream &in, CMyTime &time)
{
    in >> time.m_Hour >> time.m_Minute >> time.m_Second;
    return in;
}

ostream &operator<<(ostream &out, const CMyTime &time)
{
    out << setfill('0')
        << setw(2) << time.m_Hour << ":"
        << setw(2) << time.m_Minute << ":"
        << setw(2) << time.m_Second;
    return out;
}

// Đồng hồ xem giờ.
CMyTime &CMyTime::operator++()
{
    m_Second++;
    if (m_Second == 60)
    {
        m_Second = 0;
        m_Minute++;
        if (m_Minute == 60)
        {
            m_Minute = 0;
            m_Hour = (m_Hour + 1) % 24;
        }
    }
    return *this;
}

CMyTime CMyTime::operator--(int)
{
    CMyTime ans(*this);
    ans.m_Second--;
    if (ans.m_Second < 0)
    {
        ans.m_Second = 59;
        ans.m_Minute--;
        if (ans.m_Minute < 0)
        {
            ans.m_Minute = 59;
            ans.m_Hour--;
            if (ans.m_Hour < 0)
                ans.m_Hour = 23;
        }
    }
    return ans;
}

CMyTime &CMyTime::operator-=(int n)
{
    int hourShift = n % 24;
    m_Hour = (m_Hour - hourShift + 24) % 24;
    return *this;
}

// Comparison operators.
bool CMyTime::operator>(const CMyTime &other) const
{
    return this->totalSecond() > other.totalSecond();
}

bool CMyTime::operator<(const CMyTime &other) const
{
    return this->totalSecond() < other.totalSecond();
}

bool CMyTime::operator==(const CMyTime &other) const
{
    return this->totalSecond() == other.totalSecond();
}

bool CMyTime::operator>=(const CMyTime &other) const
{
    return (*this > other) || (*this == other);
}

bool CMyTime::operator<=(const CMyTime &other) const
{
    return (*this < other) || (*this == other);
}

void CMyTime::ShowTime()
{
}

void CMyTime::CountDown()
{
}

void CMyTime::RunStopwatch()
{
}

CMyTime &CMyTime::operator+=(int n)
{
    m_Hour += n;
    return *this;
}

CMyTime CMyTime::operator+(const CMyTime &other) const
{
    long long thisSecond = this->totalSecond();
    long long otherSecond = other.totalSecond();
    long long answerSecond = thisSecond + otherSecond;
    return tranferToTime(answerSecond);
}

CMyTime CMyTime::operator-(const CMyTime &other) const
{
    long long thisSecond = this->totalSecond();
    long long otherSecond = other.totalSecond();
    long long answerSecond = abs(thisSecond - otherSecond);
    return tranferToTime(answerSecond);
}

void CMyTime::readFile(const string &filename, vector<CMyTime> &myTimes)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "ERROR: Cannot open file \"" << filename << "\".\n";
        return;
    }

    int n;
    fin >> n;

    for (int i = 0; i < n; i++)
    {
        CMyTime temp;
        fin >> temp;
        myTimes.push_back(temp);
    }

    fin.close();
}

void writeToFileSorted(const string &filename, const vector<CMyTime> &myTimes)
{
    if (myTimes.empty())
        return;

    sort(myTimes.begin(), myTimes.end());

    ofstream fout(filename);

    if (!fout)
    {
        cout << "ERROR: Cannot open file \"" << filename << "\".\n";
        return;
    }

    for (int i = 0; i < myTimes.size(); i++)
        fout << myTimes[i] << "\n";

    fout.close();
}

void writeToFileResult(const string &filename, const vector<CMyTime> &myTimes)
{
    if (myTimes.empty())
        return;

    CMyTime totalTime(myTimes[0]), fastestTime(myTimes[0]), slowestTime(myTimes[0]);
    for (int i = 1; i < myTimes.size(); i++)
    {
        totalTime = totalTime + myTimes[i];

        if (myTimes[i] > fastestTime)
            fastestTime = myTimes[i];

        if (myTimes[i] < slowestTime)
            slowestTime = myTimes[i];
    }

    ofstream fout(filename);

    if (!fout)
    {
        cout << "ERROR: Cannot open file \"" << filename << "\".\n";
        return;
    }

    fout << "Total time: " << totalTime << ".\n"
         << "Fastest time: " << fastestTime << ".\n"
         << "Slowest time: " << slowestTime << ".\n";

    fout.close();
}

int main()
{
    return 0;
}