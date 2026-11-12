#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <map>
#include <algorithm>
using namespace std;

class CDate
{
private:
    int Day, Month, Year;

public:
    // Constructors.
    CDate();
    CDate(int day, int month, int year);

    // IO operators.
    friend istream &operator>>(istream &in, CDate &date);
    friend ostream &operator<<(ostream &out, const CDate &date);

    // Comparison operator.
    bool operator<(const CDate &other) const;
};

// Constructors.
CDate::CDate() : Day(1), Month(1), Year(1) {};

CDate::CDate(int day, int month, int year) : Day(day), Month(month), Year(year) {};

// IO operators.
istream &operator>>(istream &in, CDate &date)
{
    char c;
    in >> date.Day >> c >> date.Month >> c >> date.Year;
    return in;
}

ostream &operator<<(ostream &out, const CDate &date)
{
    out << setfill('0')
        << setw(2) << date.Day << "/"
        << setw(2) << date.Month << "/"
        << setw(2) << date.Year;
    return out;
}

// Comparison operator.
bool CDate::operator<(const CDate &other) const
{
    if (Year != other.Year)
        return Year < other.Year;
    if (Month != other.Month)
        return Month < other.Month;
    return Day < other.Day;
}

class CMyTime
{
private:
    int m_Hour;
    int m_Minute;
    int m_Second;

    // Support function.
    long long totalSecond() const;

public:
    // Constructors.
    CMyTime();
    CMyTime(const CMyTime &other);
    CMyTime(int hour, int minute, int second);

    // Getters.
    int getHour() const { return m_Hour; }
    int getMinute() const { return m_Minute; }
    int getSecond() const { return m_Second; }

    // IO operators.
    friend istream &operator>>(istream &in, CMyTime &time);
    friend ostream &operator<<(ostream &out, const CMyTime &time);

    // Comparison operators.
    bool operator>(const CMyTime &other) const;
    bool operator<(const CMyTime &other) const;
    bool operator==(const CMyTime &other) const;
    bool operator>=(const CMyTime &other) const;
    bool operator<=(const CMyTime &other) const;
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

// Support function.
long long CMyTime::totalSecond() const
{
    return (m_Hour * 3600 + m_Minute * 60 + m_Second);
}

// IO operators.
istream &operator>>(istream &in, CMyTime &time)
{
    char c;
    in >> time.m_Hour >> c >> time.m_Minute >> c >> time.m_Second;
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

class CMessage
{
private:
    string m_Number;
    int m_Vote;
    CDate m_Date;
    CMyTime m_Time;

public:
    // Constructors.
    CMessage();

    // IO operators.
    friend istream &operator>>(istream &in, CMessage &msg);
    friend ostream &operator<<(ostream &out, const CMessage &msg);

    // Getters.
    string getNumber() const { return m_Number; }
    int getVote() const { return m_Vote; }
    CDate getDate() const { return m_Date; }
    CMyTime getTime() const { return m_Time; }

    bool isValidNumber();
};

// Constructor.
CMessage::CMessage() : m_Number(""), m_Vote(0), m_Date(), m_Time() {};

bool CMessage::isValidNumber()
{
    if (m_Number.size() < 10)
        return false;

    for (int i = 0; i < m_Number.size(); i++)
    {
        if (!isdigit(m_Number[i]))
            return false;
    }

    return true;
}

// IO operators.
istream &operator>>(istream &in, CMessage &msg)
{
    in >> msg.m_Number >> msg.m_Vote >> msg.m_Date >> msg.m_Time;
    return in;
}

ostream &operator<<(ostream &out, const CMessage &msg)
{
    out << msg.m_Number << " " << msg.m_Vote << " " << msg.m_Date << " " << msg.m_Time;
    return out;
}

class CListMessage
{
private:
    vector<CMessage> m_Messages;

public:
    // IO operators.
    friend istream &operator>>(istream &in, CListMessage &list);
    friend ostream &operator<<(ostream &out, const CListMessage &list);

    // Methods.
    void ShowMostVotedCode();
    void ShowMostActivePhone();
    void ShowPeakMessageDay();
    void ShowPeakVotingHour();
    void ShowTop10();
};

// IO operators.
istream &operator>>(istream &in, CListMessage &list)
{
    CMessage msg;
    while (in >> msg)
    {
        if (msg.isValidNumber())
            list.m_Messages.push_back(msg);
    }
    return in;
}

ostream &operator<<(ostream &out, const CListMessage &list)
{
    int n = list.m_Messages.size();
    for (int i = 0; i < n; i++)
        out << list.m_Messages[i] << "\n";
    return out;
}

// Methods.
void CListMessage::ShowMostVotedCode()
{
    unordered_map<int, int> freqVote;
    int n = m_Messages.size();
    int maxFreqVote = -1;

    for (int i = 0; i < n; i++)
    {
        int vote = m_Messages[i].getVote();
        freqVote[vote]++;
        maxFreqVote = max(maxFreqVote, freqVote[vote]);
    }

    ofstream fout("OUTPUT.txt");

    if (!fout)
    {
        cout << "ERROR: Cannot open file OUTPUT.txt\n";
        return;
    }

    for (const pair<int, int> &kv : freqVote)
    {
        if (kv.second == maxFreqVote)
        {
            cout << "Ma so: " << kv.first << "\n";
            cout << "So luot binh chon: " << kv.second << "\n";

            fout << "Ma so: " << kv.first << "\n";
            fout << "So luot binh chon: " << kv.second << "\n";
        }
    }

    fout.close();
}

void CListMessage::ShowMostActivePhone()
{
    unordered_map<string, int> freqNumber;
    int n = m_Messages.size();
    int maxFreqNumber = -1;

    for (int i = 0; i < n; i++)
    {
        string number = m_Messages[i].getNumber();
        freqNumber[number]++;
        maxFreqNumber = max(maxFreqNumber, freqNumber[number]);
    }

    for (const pair<string, int> &kv : freqNumber)
    {
        if (kv.second == maxFreqNumber)
        {
            cout << "So dien thoai: " << kv.first << "\n";
            cout << "So tin nhan: " << kv.second << "\n";
        }
    }
}

void CListMessage::ShowPeakMessageDay()
{
    map<CDate, int> freqDate;
    int n = m_Messages.size();
    int maxFreqDate = -1;

    for (int i = 0; i < n; i++)
    {
        CDate date = m_Messages[i].getDate();
        freqDate[date]++;
        maxFreqDate = max(maxFreqDate, freqDate[date]);
    }

    for (const pair<CDate, int> &kv : freqDate)
    {
        if (kv.second == maxFreqDate)
        {
            cout << "Ngay: " << kv.first << "\n";
            cout << "So tin nhan: " << kv.second << "\n";
        }
    }
}

void CListMessage::ShowPeakVotingHour()
{
    unordered_map<int, int> freqHour;
    int n = m_Messages.size();
    int maxFreqHour = -1;

    for (int i = 0; i < n; i++)
    {
        int hour = m_Messages[i].getTime().getHour();
        freqHour[hour]++;
        maxFreqHour = max(maxFreqHour, freqHour[hour]);
    }

    for (const pair<int, int> &kv : freqHour)
    {
        if (kv.second == maxFreqHour)
        {
            cout << "Khung gio: " << setfill('0') << setw(2) << kv.first << ":00:00 - "
                 << setfill('0') << setw(2) << kv.first << ":59:59\n";
            cout << "So tin nhan: " << kv.second << "\n";
        }
    }
}

void CListMessage::ShowTop10()
{
    unordered_map<int, int> freqVote;
    int n = m_Messages.size();
    for (int i = 0; i < n; i++)
    {
        int vote = m_Messages[i].getVote();
        freqVote[vote]++;
    }

    vector<pair<int, int>> vectorVote;
    for (const pair<int, int> &kv : freqVote)
        vectorVote.push_back(kv);

    sort(vectorVote.begin(), vectorVote.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         { return a.second > b.second; });

    int currentRank = 1;
    for (int i = 0; i < vectorVote.size(); i++)
    {
        if (i > 0 && vectorVote[i].second < vectorVote[i - 1].second)
            currentRank++;

        if (currentRank > 10)
            break;

        cout << "Hang " << currentRank << " | Ma so " << vectorVote[i].first << " | So luot " << vectorVote[i].second << "\n";
    }
}

int main()
{
    ifstream fin("INPUT.txt");

    if (!fin)
    {
        cout << "ERROR: Cannot open file INPUT.txt\n";
        return -1;
    }

    CListMessage list;
    fin >> list;
    fin.close();

    cout << list;
    list.ShowMostVotedCode();
    list.ShowMostActivePhone();
    list.ShowPeakMessageDay();
    list.ShowPeakVotingHour();
    list.ShowTop10();

    return 0;
}