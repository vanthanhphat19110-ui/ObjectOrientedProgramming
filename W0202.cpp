#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
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
    Book(const string &isbn, const string &title, const string &author, const string &language, int publishedYear,
         double price, int stockLevel, const DateTime &inputDate)
    {
        this->isbn = isbn;
        this->title = title;
        this->author = author;
        this->language = language;
        this->publishedYear = publishedYear;
        this->price = price;
        this->stockLevel = stockLevel;
        this->inputDate = inputDate;
    }

    string getIsbn() const
    {
        return isbn;
    }

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    string getLanguage() const
    {
        return language;
    }

    int getPublishedYear() const
    {
        return publishedYear;
    }

    double getPrice() const
    {
        return price;
    }

    int getStockLevel() const
    {
        return stockLevel;
    }

    DateTime getInputDate() const
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
        cout << setw(20) << "- Tên sách" << ":" << title << ".\n"
             << setw(20) << "   + Tác giả" << ":" << author << ".\n"
             << setw(20) << "   + Ngôn ngữ" << ":" << language << ".\n"
             << setw(20) << "   + Năm xuất bản" << ":" << publishedYear << ".\n"
             << setw(20) << "   + Giá bán" << ":" << price << ".\n"
             << setw(20) << "   + Tồn kho" << ":" << stockLevel << ".\n";
    }

    string toString()
    {
        stringstream ss;
        ss << isbn << "," << title << "," << author << "," << language << ","
           << to_string(publishedYear) << "," << to_string(price) << "," << to_string(stockLevel) << ","
           << inputDate.toString();
        return ss.str();
    }
};

struct CartItem
{
    Book book;
    int quantity;
};

class BookStore
{
private:
    string name;
    vector<Book> data; // lưu trữ thông tin các sách mà nhà sách có.

public:
    BookStore(const string &name) : name(name) {};

    bool loadFromFile(const string &filename)
    {
        ifstream input(filename);
        if (!input)
            return false;
        data.clear();

        string line;
        while (getline(input, line))
        {
            if (line.empty())
                continue;

            stringstream ss;
            string isbn, title, author, language, publishedYear, price, stockLevel, inputDate;

            getline(ss, isbn, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, language, ',');
            getline(ss, publishedYear, ',');
            getline(ss, price, ',');
            getline(ss, stockLevel, ',');
            getline(ss, inputDate, ',');

            int py = stoi(publishedYear); // py = published year
            double cost = stod(price);
            int stock = stoi(stockLevel);
            int second, minute, hour, day, month, year;
            sscanf(inputDate.c_str(), "%d:%d:%d, %d/%d/%d", &hour, &minute, &second, &day, &month, &year);
            DateTime date(second, minute, hour, day, month, year);

            data.push_back(Book(isbn, title, author, language, py, cost, stock, date));
        }

        input.close();
        return true;
    }

    void saveToFile(const string &filename)
    {
        ofstream output(filename);
        for (auto &b : data)
            output << b.toString() << "\n";
        output.close();
    }

    // Question 01.
    void displaySortedByPrice()
    {
        vector<Book> temp = data;
        sort(temp.begin(), temp.end(), [](const Book &a, const Book &b)
             {  if (a.getPrice() != b.getPrice()) return a.getPrice() < b.getPrice(); 
                return a.getTitle() < b.getTitle(); });
        cout << "THE LIST OF BOOKS SORTED BY PRICE\n";
        for (auto &b : temp)
            b.display();
    }

    // Question 02.
    void displayTopKLatest(int k = 10)
    {
        vector<Book> temp = data;
        sort(temp.begin(), temp.end(), [](const Book &a, const Book &b)
             { return b.getInputDate() < a.getInputDate(); });
        cout << "THE LIST OF TOP " << k << " LASTEST BOOKS\n";
        for (int i = 0; i < k; i++)
            temp[i].display();
    }

    // Question 03.
    void importBook()
    {
        string isbn;
        cout << "Input ISBN: ";
        cin >> isbn;
        cin.ignore();

        auto it = find_if(data.begin(), data.end(), [&](const Book &b)
                          { return b.getIsbn() == isbn; });

        if (it != data.end())
        {
            int addStock;
            cout << "This book already existed.\n"
                 << "Please input an additional quantity: ";
            cin >> addStock;
            it->setStockLevel(it->getStockLevel() + addStock);
            it->setInputDate(DateTime::getCurrentTime());
            cout << "Successfully updated.\n";
        }
        else
        {
            string title, author, language;
            int publishedYear, stockLevel;
            double price;

            cout << "Input title: ";
            cin >> title;
            cout << "Input author: ";
            cin >> author;
            cout << "Input language: ";
            cin >> language;
            cin.ignore();
            cout << "Input published year: ";
            cin >> publishedYear;
            cout << "Input price: ";
            cin >> price;
            cout << "Input stock level: ";
            cin >> stockLevel;
            DateTime date = DateTime::getCurrentTime();

            data.push_back(Book(isbn, title, author, language, publishedYear, price, stockLevel, date));
            cout << "Successfully updated.\n";
        }
    }

    // Question 04.
    void addToCart(vector<CartItem> &cart)
    {
        string isbn;
        cout << "Input ISBN: ";
        cin >> isbn;
        cin.ignore();

        auto it = find_if(data.begin(), data.end(), [&](const Book &b)
                          { return b.getIsbn() == isbn; });

        if (it == data.end())
        {
            cout << "This ISBN is not found.\n";
            return;
        }

        int quantity;
        cout << "Input quantity: ";
        cin >> quantity;

        if (quantity <= 0)
        {
            cerr << "ERROR! The quantiy must be greater than 0.\n";
            return;
        }

        if (quantity > it->getStockLevel())
        {
            cerr << "ERROR! The stock is not enough.\n";
            cout << "The current stock level: " << it->getStockLevel() << ".\n";
            return;
        }

        cart.push_back({*it, quantity});
        cout << "Successfully added to cart.\n";
    }
};

int main()
{
}