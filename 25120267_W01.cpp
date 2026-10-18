#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

long long modEuclidean(long long a, long long b)
{
    long long m = a % b;
    return (m >= 0) ? m : (m + b);
}

class CDate
{
private:
    int Day, Month, Year;
    int getMaxDayInMonth(int month, int year);
    long long convertToABSDays();

public:
    CDate(int day = 1, int month = 1, int year = 1) : Day(day), Month(month), Year(year) {};

    bool InspectLeapYear();
    bool CheckDate();

    void InputDate();
    void OutputDate();

    CDate IncreaseYear();
    CDate IncreaseMonth();
    CDate IncreaseDay();

    CDate DecreaseYear();
    CDate DecreaseMonth();
    CDate DecreaseDay();

    CDate IncreaseYear(int n);
    CDate IncreaseMonth(int n);
    CDate IncreaseDay(int n);

    CDate DecreaseYear(int n);
    CDate DecreaseMonth(int n);
    CDate DecreaseDay(int n);

    int DayOrderInYear();
    int WeekOrderInYear();

    void ConvertDate();
    int DeductDateToDate(CDate other);
};

bool CDate::InspectLeapYear()
{
    return ((Year % 400 == 0) || ((Year % 4 == 0) && (Year % 100 != 0)));
}

int CDate::getMaxDayInMonth(int month, int year)
{
    static const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))))
        return 29;
    return days[month];
}

bool CDate::CheckDate()
{
    if (Year < 1 || Month < 1 || Month > 12 || Day < 1 || Day > 31)
        return false;
    return Day <= getMaxDayInMonth(Month, Year);
}

void CDate::InputDate()
{
    string line;
    getline(cin, line);

    stringstream ss(line);
    string dayStr, monthStr, yearStr;
    getline(ss, dayStr, '/');
    getline(ss, monthStr, '/');
    getline(ss, yearStr);

    if (dayStr.size() != 2 || monthStr.size() != 2 || yearStr.size() != 4)
    {
        cout << "ERROR! The date must be dd/mm/yyyy.\n";
        return;
    }

    int day = stoi(dayStr);
    int month = stoi(monthStr);
    int year = stoi(yearStr);
    CDate temp(day, month, year);

    if (!temp.CheckDate())
    {
        cout << "ERROR! The date is not valid.\n";
        return;
    }
    else
    {
        Day = day;
        Month = month;
        Year = year;
    }
}

void CDate::OutputDate()
{
    cout << setfill('0')
         << setw(2) << Day << "/"
         << setw(2) << Month << "/"
         << setw(4) << Year;
}

CDate CDate::IncreaseYear(int n)
{
    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }

    int newYear = Year + n;
    int newDay = min(Day, getMaxDayInMonth(Month, newYear));
    return CDate(newDay, Month, newYear);
}

CDate CDate::IncreaseYear()
{
    return IncreaseYear(1);
}

CDate CDate::DecreaseYear(int n)
{
    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }

    if (Year - n < 1)
    {
        cout << "ERROR: Year < 1.\n";
        return *this;
    }

    int newYear = Year - n;
    int newDay = min(Day, getMaxDayInMonth(Month, newYear));
    return CDate(newDay, Month, newYear);
}

CDate CDate::DecreaseYear()
{
    return DecreaseYear(1);
}

CDate CDate::IncreaseMonth(int n)
{
    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }

    int totalMonths = (Year - 1) * 12 + (Month - 1) + n;
    int newYear = (totalMonths / 12) + 1;
    int newMonth = (totalMonths % 12) + 1;
    int newDay = min(Day, getMaxDayInMonth(newMonth, newYear));
    return CDate(newDay, newMonth, newYear);
}

CDate CDate::IncreaseMonth()
{
    return IncreaseMonth(1);
}

CDate CDate::DecreaseMonth(int n)
{
    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }

    int totalMonths = (Year - 1) * 12 + (Month - 1) - n;

    if (totalMonths % 12 < 0)
    {
        cout << "ERROR: Year < 1.\n";
        return *this;
    }

    int newYear = (totalMonths / 12) + 1;
    int newMonth = (totalMonths % 12) + 1;
    int newDay = min(Day, getMaxDayInMonth(newMonth, newYear));
    return CDate(newDay, newMonth, newYear);
}

CDate CDate::DecreaseMonth()
{
    return DecreaseMonth(1);
}

long long CDate::convertToABSDays()
{
    int day = Day, month = Month, year = Year;
    if (month <= 2)
    {
        year--;
        month += 12;
    }
    return (365LL * year + year / 4 - year / 100 + year / 400 + (153 * month - 457) / 5 + day - 306);
}

CDate CDate::IncreaseDay(int n)
{
    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }
    CDate ans = *this;
    ans.Day += n;
    while (ans.Day > ans.getMaxDayInMonth(ans.Month, ans.Year))
    {
        ans.Day -= getMaxDayInMonth(ans.Month, ans.Year);
        ans.Month++;
        if (ans.Month > 12)
        {
            ans.Month = 1;
            ans.Year++;
        }
    }
    return ans;
}

CDate CDate::IncreaseDay()
{
    return IncreaseDay(1);
}

CDate CDate::DecreaseDay(int n)
{
    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return *this;
    }

    CDate ans = *this;
    ans.Day -= n;
    while (ans.Day < 1)
    {
        ans.Day += getMaxDayInMonth(ans.Month, ans.Year);
        ans.Month--;
        if (ans.Month < 1)
        {
            ans.Month = 12;
            ans.Year--;
            if (ans.Year < 1)
            {
                cout << "ERROR: Year < 1.\n";
                return *this;
            }
        }
    }
    return ans;
}

CDate CDate::DecreaseDay()
{
    return DecreaseDay(1);
}

int CDate::DayOrderInYear()
{
    int dayOrderInYear = 0;
    for (int i = 1; i < Month; i++)
        dayOrderInYear += getMaxDayInMonth(i, Year);
    dayOrderInYear += Day;
    return dayOrderInYear;
}

int CDate::WeekOrderInYear()
{
    long long absDays = convertToABSDays();
    int dayOfWeek = (int)modEuclidean(absDays + 5, 7);
    long long thursday = absDays + (3 - dayOfWeek);
    CDate temp;
    CDate firstThursday = temp.IncreaseDay((int)(thursday - temp.convertToABSDays()));
    int isoYear = firstThursday.Year;
    CDate jan4(4, 1, isoYear);
    long long jan4Abs = jan4.convertToABSDays();
    int jan4DayOfWeek = (int)modEuclidean(jan4Abs + 5, 7);
    long long week1StartAbs = jan4Abs - jan4DayOfWeek;
    return (int)((thursday - week1StartAbs) / 7 + 1);
}

void CDate::ConvertDate()
{
    static const string months[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    cout << months[Month] << " " << Day << ", " << Year;
}

int CDate::DeductDateToDate(CDate other)
{
    return abs((int)(convertToABSDays() - other.convertToABSDays()));
}

int main()
{
    CDate d1;
    cout << "- Input d1 (dd/mm/yyyy): ";
    d1.InputDate();
    if (!d1.CheckDate())
    {
        cout << "ERROR! The date is not valid.\n";
        return 0;
    }

    cout << "- Output d1: ";
    d1.OutputDate();
    cout << ".\n";

    CDate d2;

    cout << "- IncreaseYear(): ";
    d2 = d1.IncreaseYear();
    d2.OutputDate();
    cout << ".\n";

    cout << "- IncreaseMonth(): ";
    d2 = d1.IncreaseMonth();
    d2.OutputDate();
    cout << ".\n";

    cout << "- IncreaseDay(): ";
    d2 = d1.IncreaseDay();
    d2.OutputDate();
    cout << ".\n";

    cout << "- DecreaseYear(): ";
    d2 = d1.DecreaseYear();
    d2.OutputDate();
    cout << ".\n";

    cout << "- DecreaseMonth(): ";
    d2 = d1.DecreaseMonth();
    d2.OutputDate();
    cout << ".\n";

    cout << "- DecreaseDay(): ";
    d2 = d1.DecreaseDay();
    d2.OutputDate();
    cout << ".\n";

    int n;
    cout << "- Input n: ";
    cin >> n;
    cin.ignore();

    if (n < 0)
    {
        cout << "ERROR: n < 0.\n";
        return 0;
    }

    cout << "- IncreaseYear(n): ";
    d2 = d1.IncreaseYear(n);
    d2.OutputDate();
    cout << ".\n";

    cout << "- IncreaseMonth(n): ";
    d2 = d1.IncreaseMonth(n);
    d2.OutputDate();
    cout << ".\n";

    cout << "- IncreaseDay(n): ";
    d2 = d1.IncreaseDay(n);
    d2.OutputDate();
    cout << ".\n";

    cout << "- DecreaseYear(n): ";
    d2 = d1.DecreaseYear(n);
    d2.OutputDate();
    cout << ".\n";

    cout << "- DecreaseMonth(n): ";
    d2 = d1.DecreaseMonth(n);
    d2.OutputDate();
    cout << ".\n";

    cout << "- DecreaseDay(n): ";
    d2 = d1.DecreaseDay(n);
    d2.OutputDate();
    cout << ".\n";

    cout << "- DayOrderInYear(): " << d1.DayOrderInYear() << ".\n";
    cout << "- WeekOrderInYear(): " << d1.WeekOrderInYear() << ".\n";
    cout << "- ConverDate(): ";
    d1.ConvertDate();
    cout << ".\n";

    cout << "- Input d2 (dd/mm/yyyy): ";
    d2.InputDate();
    if (!d2.CheckDate())
    {
        cout << "ERROR! The date is not valid.\n";
        return 0;
    }

    cout << "- DeductDateToDate(): " << d1.DeductDateToDate(d2) << ".\n";
    return 0;
}