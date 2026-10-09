#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

class DateTime
{
private:
    int second, minute, hour;
    int day, month, year;

public:
    DateTime() : second(0), minute(0), hour(0), day(1), month(1), year(2000) {};

    DateTime(int second, int minute, int hour, int day, int month, int year)
    {
        this->second = second;
        this->minute = minute;
        this->hour = hour;
        this->day = day;
        this->month = month;
        this->year = year;
    }

    static DateTime getCurrentTime()
    {
        time_t temp = time(0);      // lấy thời gian hiện tại của hệ thống, tính bằng số giây.
        tm *now = localtime(&temp); // đổi số giây thành giờ địa phương.
        int second = now->tm_sec;
        int minute = now->tm_min;
        int hour = now->tm_hour;
        int day = now->tm_mday;
        int month = now->tm_mon + 1;
        int year = now->tm_year + 1900;
        return DateTime(second, minute, hour, day, month, year);
    }

    bool operator<(const DateTime &other) const
    {
        if (year != other.year)
            return year < other.year;
        if (month != other.month)
            return month < other.month;
        if (day != other.day)
            return day < other.day;
        if (hour != other.hour)
            return hour < other.hour;
        if (minute != other.minute)
            return minute < other.minute;
        return second < other.second;
    }

    string toString()
    {
        stringstream ss;
        ss << setfill('0')
           << setw(2) << hour << ":"
           << setw(2) << minute << ":"
           << setw(2) << second << ", "
           << setw(2) << day << "/"
           << setw(2) << month << "/"
           << setw(4) << year;
        return ss.str();
    }
};

class Book
{
private:
    string isbn;   // mã sách: tối đa 13 kí tự.
    string title;  // tên sách: tối đa 100 kí tự.
    string author; // tên tác giả: tối đa 100 kí tự.
    string language;
    int publishedYear;
    double price;
    int stockLevel;     // số lượng sách có trong nhà sách.
    DateTime inputDate; // ngày nhập sách.

public:
    string getIsbn()
    {
        return isbn;
    }

    string getTitle()
    {
        return title;
    }

    string getAuthor()
    {
        return author;
    }

    string getLanguage()
    {
        return language;
    }

    int getPublishedYear()
    {
        return publishedYear;
    }

    double getPrice()
    {
        return price;
    }

    int getStockLevel()
    {
        return stockLevel;
    }

    DateTime getInputDate()
    {
        return inputDate;
    }

    void setStockLevel(int stock)
    {
        stockLevel = stock;
    }

    void setInputDate(const DateTime &date)
    {
        inputDate = date;
    }

    void display()
    {
        cout << setw(15) << "- Mã sách" << ":" << isbn << ".\n"
             << setw(15) << "- Tên sách" << ":" << title << ".\n"
             << setw(15) << "- Tác giả" << ":" << author << ".\n"
             << setw(15) << "- Ngôn ngữ" << ":" << language << ".\n"
             << setw(15) << "- Năm xuất bản" << ":" << publishedYear << ".\n"
             << setw(15) << "- Giá bán" << ":" << price << ".\n"
             << setw(15) << "- Tồn kho" << ":" << stockLevel << ".\n";
    }

    string toString()
    {
        stringstream ss;
        return ss.str();
    }
};

class BookStore
{
private:
    string name;
    vector<Book> data; // lưu trữ thông tin các sách mà nhà sách có.

public:
};

int main()
{
}