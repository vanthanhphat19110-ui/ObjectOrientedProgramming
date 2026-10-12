#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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

    string toString() const
    {
        stringstream ss;
        ss << setfill('0')
           << setw(2) << hour << ":"
           << setw(2) << minute << ":"
           << setw(2) << second << ","
           << setw(2) << day << "/"
           << setw(2) << month << "/"
           << setw(4) << year;
        return ss.str();
    }
};

string inputStringWithLimit(const string &prompt, int maxLength)
{
    string s;
    while (true)
    {
        cout << prompt;
        getline(cin, s);
        if (!s.empty() && s.length() <= maxLength)
            return s;
        cout << "- ERROR! Max length: " << maxLength << " and cannot be empty.\n";
    }
}

class Book
{
private:
    string isbn;   // mã sách: tối đa 13 kí tự.
    string title;  // tên sách: tối đa 100 kí tự.
    string author; // tên tác giả: tối đa 100 kí tự.
    string language;
    int publishedYear;
    double price;       // VND
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

    // Getters and Setters.
    string getIsbn() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getLanguage() const { return language; }
    int getPublishedYear() const { return publishedYear; }
    double getPrice() const { return price; }
    int getStockLevel() const { return stockLevel; }
    DateTime getInputDate() const { return inputDate; }
    void setStockLevel(int stock) { stockLevel = stock; }
    void setInputDate(const DateTime &date) { inputDate = date; }

    void display() const
    {
        cout << "- Book: " << title << ".\n"
             << "   + Author: " << author << ".\n"
             << "   + Language: " << language << ".\n"
             << "   + Publised year: " << publishedYear << ".\n"
             << "   + Price: " << fixed << setprecision(0) << price << " VND.\n"
             << "   + Stock: " << stockLevel << ".\n";
    }

    string toString() const
    {
        stringstream ss;
        ss << isbn << "," << title << "," << author << "," << language << ","
           << publishedYear << "," << fixed << setprecision(0) << price << "," << stockLevel << ","
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

            stringstream ss(line);
            string isbn, title, author, language, publishedYear, price, stockLevel, inputDate;

            getline(ss, isbn, ',');
            getline(ss, title, ',');
            getline(ss, author, ',');
            getline(ss, language, ',');
            getline(ss, publishedYear, ',');
            getline(ss, price, ',');
            getline(ss, stockLevel, ',');
            getline(ss, inputDate);

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

    void saveToFile(const string &filename) const
    {
        ofstream output(filename);
        for (const Book &b : data)
            output << b.toString() << "\n";
        output.close();
    }

    // Request 01.
    void displaySortedByPrice() const
    {
        if (data.empty())
        {
            cout << "==> There are no books in the bookstore.\n";
            return;
        }

        vector<Book> temp = data;
        sort(temp.begin(), temp.end(), [](const Book &a, const Book &b)
             {  if (a.getPrice() != b.getPrice()) return a.getPrice() < b.getPrice(); 
                return a.getTitle() < b.getTitle(); });
        cout << "===================== THE LIST OF BOOKS SORTED BY PRICE =====================\n";
        for (const Book &b : temp)
            b.display();
    }

    // Request 02.
    void displayTopKLatest(int ka = 10) const
    {
        if (data.empty())
        {
            cout << "==> There are no books in the bookstore.\n";
            return;
        }

        vector<Book> temp = data;
        sort(temp.begin(), temp.end(), [](const Book &a, const Book &b)
             { return b.getInputDate() < a.getInputDate(); });
        cout << "===================== THE LIST OF TOP " << ka << " LASTEST BOOKS ======================\n";
        int limit = min((size_t)ka, temp.size());
        for (int i = 0; i < limit; i++)
            temp[i].display();
    }

    // Request 03.
    void importBook()
    {
        clearInputBuffer();
        string isbn = inputStringWithLimit("--> Input ISBN: ", 13);

        auto it = find_if(data.begin(), data.end(), [&](const Book &b)
                          { return b.getIsbn() == isbn; });

        if (it != data.end())
        {
            int addStock;
            cout << "- This book already existed.\n"
                 << "- Please enter an additional quantity: ";
            cin >> addStock;

            while (cin.fail() || addStock <= 0)
            {
                if (cin.fail())
                {
                    clearInputBuffer();
                    cout << "- ERROR! The quantity must be a positive integer.\n";
                }
                cout << "- Please enter the quantity again: ";
                cin >> addStock;
            }

            it->setStockLevel(it->getStockLevel() + addStock);
            it->setInputDate(DateTime::getCurrentTime());
        }
        else // not found
        {
            string language;
            int publishedYear, stockLevel;
            double price;

            string title = inputStringWithLimit("--> Input title: ", 100);
            string author = inputStringWithLimit("--> Input author: ", 100);
            cout << "--> Input language: ";
            getline(cin, language);

            cout << "--> Input published year: ";
            cin >> publishedYear;
            while (cin.fail() || publishedYear <= 0)
            {
                if (cin.fail())
                {
                    clearInputBuffer();
                    cout << "- ERROR! The publised year must be a positive integer.\n";
                }
                cout << "- Please enter the publised year again: ";
                cin >> publishedYear;
            }

            cout << "--> Input price: ";
            cin >> price;
            while (cin.fail() || price <= 1000)
            {
                if (cin.fail())
                {
                    clearInputBuffer();
                    cout << "- ERROR! The price must be greater than 1000 VND.\n";
                }
                cout << "- Please enter the price again: ";
                cin >> price;
            }

            cout << "--> Input stock level: ";
            cin >> stockLevel;
            while (cin.fail() || stockLevel <= 0)
            {
                if (cin.fail())
                {
                    clearInputBuffer();
                    cout << "- ERROR! The stock level must be a positive integer.\n";
                }
                cout << "- Please enter the stock level again: ";
                cin >> stockLevel;
            }

            DateTime date = DateTime::getCurrentTime();

            data.push_back(Book(isbn, title, author, language, publishedYear, price, stockLevel, date));
        }
        cout << "==> Successfully updated.\n";
    }

    // Request 04.
    void addToCart(vector<CartItem> &cart)
    {
        clearInputBuffer();
        string isbn = inputStringWithLimit("--> Input ISBN: ", 13);

        auto it = find_if(data.begin(), data.end(), [&](const Book &b)
                          { return b.getIsbn() == isbn; });

        if (it == data.end())
        {
            cout << "==> This ISBN is not found.\n";
            return;
        }

        int quantity;
        cout << "--> Input quantity: ";
        cin >> quantity;

        while (cin.fail() || quantity <= 0)
        {
            if (cin.fail())
            {
                clearInputBuffer();
                cout << "- ERROR! The quantity must be a positive integer.\n";
            }
            cout << "- Please enter the quantity again: ";
            cin >> quantity;
        }

        if (quantity > it->getStockLevel())
        {
            cerr << "- ERROR! The stock is not enough.\n";
            cout << "- Current stock: " << it->getStockLevel() << ".\n";
            return;
        }

        cart.push_back({*it, quantity});
        cout << "==> Successfully added to cart.\n";
    }

    // Request 05.
    void checkout(vector<CartItem> &cart, const string &orderFilename)
    {
        if (cart.empty())
        {
            cout << "==> The cart is empty.\n";
            return;
        }

        clearInputBuffer();
        string customerName;
        cout << "--> Input customer's name: ";
        getline(cin, customerName);
        DateTime date = DateTime::getCurrentTime();

        double total = 0;
        stringstream orderDetail;
        orderDetail << "======================== BILL ========================\n"
                    << "- Date: " << date.toString() << ".\n"
                    << "- Customer: " << customerName << ".\n"
                    << "- Detail:\n";
        for (const CartItem &item : cart)
        {
            for (Book &book : data)
            {
                if (book.getIsbn() == item.book.getIsbn())
                {
                    book.setStockLevel(book.getStockLevel() - item.quantity);
                    break;
                }
            }
            double subTotal = item.book.getPrice() * item.quantity;
            total += subTotal;
            orderDetail << "+ " << item.book.getTitle() << " x " << item.quantity << " = " << fixed << setprecision(0) << subTotal << " VND.\n";
        }
        orderDetail << "- Total: " << fixed << setprecision(0) << total << " VND.\n"
                    << "======================================================\n";

        string oldOrder = "";
        ifstream input(orderFilename);
        if (input)
        {
            string line;
            while (getline(input, line))
                oldOrder += line + "\n";
        }
        input.close();

        ofstream output(orderFilename);
        if (output)
            output << orderDetail.str() << oldOrder;
        output.close();

        cart.clear();
        cout << "==> Successful payment.\n";
    }

    // Request 06.
    void displayLowStock(int kb = 50) const
    {
        if (data.empty())
        {
            cout << "==> There are no books in the bookstore.\n";
            return;
        }

        cout << "====================== THE LIST OF BOOKS WITH LOW STOCK ======================\n";
        bool isFound = false;
        for (const Book &b : data)
        {
            if (b.getStockLevel() < kb)
            {
                b.display();
                isFound = true;
            }
        }

        if (!isFound)
            cout << "==> There are no books below stock level.\n";
    }
};

int main()
{
    BookStore bookStore("HCMUS BookStore");

    if (!bookStore.loadFromFile("HCMUSBookStore.txt"))
        cout << "ERROR! Cannot load from file: HCMUSBookStore.txt\n";

    vector<CartItem> cart;
    int choice;

    do
    {
        cout << "============================== HCMUS BOOKSTORE ==============================\n"
             << "| 1. Display books sorted by price.                                         |\n"
             << "| 2. Display top k latest books.                                            |\n"
             << "| 3. Import books.                                                          |\n"
             << "| 4. Add to cart.                                                           |\n"
             << "| 5. Payment.                                                               |\n"
             << "| 6. Display books with low stock.                                          |\n"
             << "| 0. Exit.                                                                  |\n"
             << "=============================================================================\n";
        cout << "--> Your choice: ";
        cin >> choice;

        while (cin.fail() || choice < 0 || choice > 6)
        {
            if (cin.fail())
            {
                clearInputBuffer();
                cout << "- ERROR! The choice must be an integer from 0 to 6.\n";
            }
            cout << "- Please enter your choice again: ";
            cin >> choice;
        }

        switch (choice)
        {
        case 1:
        {
            bookStore.displaySortedByPrice();
            break;
        }
        case 2:
        {
            int ka;
            cout << "--> Input ka: ";
            cin >> ka;

            while (cin.fail() || ka <= 0)
            {
                if (cin.fail())
                {
                    clearInputBuffer();
                    cout << "- ERROR! The ka must be a positive integer.\n";
                }
                cout << "- Please enter ka again: ";
                cin >> ka;
            }

            bookStore.displayTopKLatest(ka);
            break;
        }
        case 3:
        {
            bookStore.importBook();
            break;
        }
        case 4:
        {
            bookStore.addToCart(cart);
            break;
        }
        case 5:
        {
            bookStore.checkout(cart, "Orders.txt");
            break;
        }
        case 6:
        {
            int kb;
            cout << "--> Input kb: ";
            cin >> kb;

            while (cin.fail() || kb <= 0)
            {
                if (cin.fail())
                {
                    clearInputBuffer();
                    cout << "- ERROR! The kb must be a positive integer.\n";
                }
                cout << "- Please enter kb again: ";
                cin >> kb;
            }

            bookStore.displayLowStock(kb);
            break;
        }
        case 0:
        {
            bookStore.saveToFile("HCMUSBookStore.txt");
            cout << "==> Goodbye. See you again.\n";
            break;
        }
        };
    } while (choice != 0);

    return 0;
}