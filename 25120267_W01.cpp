#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

class CDate
{
private:
    int Day, Month, Year;

public:
    CDate(int d, int m, int y) : Day(d), Month(m), Year(y) {};
    int getDay() { return Day; }
    int getMonth() { return Month; }
    int getYear() { return Year; }
    void setDay(int d) { Day = d; }
    void setMonth(int m) { Month = m; }
    void setYear(int y) { Year = y; }
    void InputDate();
    void OutputDate();
    bool CheckDate();
    bool InspectLeapYear();
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
    int DeductDateToDate(CDate);
};