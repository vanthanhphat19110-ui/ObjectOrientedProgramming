#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class CMyTime
{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;
    long long totalSecond(const CMyTime &);
    CMyTime tranferToTime(long long);

public:
    CMyTime();
    CMyTime(const CMyTime &);
    CMyTime(int, int, int);

    friend istream &operator>>(istream &, CMyTime &);
    friend ostream &operator<<(ostream &, const CMyTime &);

    CMyTime &operator++();
    CMyTime operator--(int);
    CMyTime &operator-=(int);

    bool operator>(const CMyTime &);
    bool operator<(const CMyTime &);
    bool operator==(const CMyTime &);
    bool operator>=(const CMyTime &);
    bool operator<=(const CMyTime &);

    void ShowTime();
    void CountDown();
    void RunStopwatch();

    CMyTime &operator+=(int);
    CMyTime operator+(const CMyTime &);
    CMyTime operator-(const CMyTime &);

    // Bài tập thêm.
    void readFile(const string &, vector<CMyTime> &);
    void writeToFileSorted();
    void writeToFileResult();
};

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

istream &operator>>(istream &in, CMyTime &time)
{
    ifstream fin("INPUT.txt");

    if (!fin)
    {
        cout << "ERROR: Cannot open INPUT.txt";
        return in;
    }

    fin >> time.m_Hour;
    fin >> time.m_Minute;
    fin >> time.m_Second;

    fin.close();
    return in;
}

ostream &operator<<(ostream &out, const CMyTime &time)
{
    out << setfill('0')
        << setw(2) << time.m_Hour << ":"
        << setw(2) << time.m_Minute << ":"
        << setw(2) << time.m_Second << ":";
    return out;
}

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
            m_Hour++;
            if (m_Hour == 24)
                m_Hour = 0;
        }
    }
    return *this;
}

CMyTime CMyTime::operator--(int)
{
    CMyTime ans(*this);
    ans.m_Second--;
    if (ans.m_Second == -1)
    {
        ans.m_Second = 59;
        ans.m_Minute--;
        if (ans.m_Minute == -1)
        {
            ans.m_Minute = 59;
            ans.m_Hour--;
            if (ans.m_Hour == -1)
                ans.m_Hour = 23;
        }
    }
    return ans;
}

CMyTime &CMyTime::operator-=(int n)
{
    n %= 24;
    m_Hour -= n;
    if (m_Hour < 0)
        m_Hour = 24 + m_Hour;
    return *this;
}

long long CMyTime::totalSecond(const CMyTime &time)
{
    return (m_Hour * 3600 + m_Minute * 60 + m_Second);
}

bool CMyTime::operator>(const CMyTime &other)
{
    return totalSecond(*this) > totalSecond(other);
}

bool CMyTime::operator<(const CMyTime &other)
{
    return totalSecond(*this) < totalSecond(other);
}

bool CMyTime::operator==(const CMyTime &other)
{
    return totalSecond(*this) == totalSecond(other);
}

bool CMyTime::operator>=(const CMyTime &other)
{
    return (*this > other) || (*this == other);
}

bool CMyTime::operator<=(const CMyTime &other)
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

CMyTime CMyTime::tranferToTime(long long totalSecond)
{
    int answerHour = totalSecond / 3600;
    totalSecond = totalSecond % 3600;
    int answerMinute = totalSecond / 60;
    int answerSecond = totalSecond % 60;

    CMyTime ans;
    ans.m_Hour = answerHour;
    ans.m_Minute = answerMinute;
    ans.m_Second = answerSecond;
    return ans;
}

CMyTime CMyTime::operator+(const CMyTime &other)
{
    long long thisSecond = totalSecond(*this);
    long long otherSecond = totalSecond(other);
    long long answerSecond = thisSecond + otherSecond;
    return tranferToTime(answerSecond);
}

CMyTime CMyTime::operator-(const CMyTime &other)
{
    long long thisSecond = totalSecond(*this);
    long long otherSecond = totalSecond(other);
    long long answerSecond = abs(thisSecond - otherSecond);
    return tranferToTime(answerSecond);
}

void CMyTime::readFile(const string &filename, vector<CMyTime> &myTimes)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "ERROR: Cannot open " << filename << ".\n";
        return;
    }

    int n;
    fin >> n;
}

void writeToFileSorted()
{
}

void writeToFileResult()
{
}

int main()
{
    return 0;
}