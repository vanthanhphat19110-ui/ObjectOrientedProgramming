#include <iostream>
#include <cstring>
using namespace std;

// Câu 01:
class Bike
{
private:
    char *brand; // hiệu xe.

public:
    // Default constructor.
    Bike(const char *b = "Unknown")
    {
        int n = strlen(b);
        brand = new char[n + 1];
        for (int i = 0; b[i] != '\0'; i++)
            brand[i] = b[i];
        brand[n] = '\0';
    }

    // Copy constructor.
    Bike(const Bike &other)
    {
        int n = strlen(other.brand);
        brand = new char[n + 1];
        for (int i = 0; other.brand[i] != '\0'; i++)
            brand[i] = other.brand[i];
        brand[n] = '\0';
    }

    // Copy assignment operator.
    Bike &operator=(const Bike &other)
    {
        if (this == &other)
            return *this;

        delete[] brand;
        int n = strlen(other.brand);
        brand = new char[n + 1];
        for (int i = 0; other.brand[i] != '\0'; i++)
            brand[i] = other.brand[i];
        brand[n] = '\0';
        return *this;
    }

    // Virtual destructor.
    virtual ~Bike() { delete[] brand; }

    virtual void move(int t1) { cout << "Brand: " << t1 * 12 << ".\n"; }
};

class EBike : public Bike
{
public:
    void move(int t2) override { Bike::move(t2 * 2); }
};

void display(Bike &a, Bike &b)
{
    a.move(2);
    b.move(2);
}

int main()
{
    EBike b1, b2;
    display(b1, b2);
    return 0;
}

/* Ý c:
- Sự khác biệt giữa lớp đối tượng và các đối tượng cụ thể:
+ Lớp đối tượng (class) là khuôn mẫu/bản thiết kế định nghĩa các thuộc tính và phương thức chung cho các đối tượng thuộc lớp đó.
Class chưa chiếm không gian bộ nhớ cho dữ liệu cụ thể.
+ Đối tượng cụ thể (object) là một thực thể cụ thể được tạo ra từ class, sở hữu một vùng nhớ riêng cho các thuộc tính
và có trạng thái dữ liệu rõ ràng.
- Danh sách lớp đối tượng và các đối tượng cụ thể đoạn code trên:
+ Lớp đối tượng (class): Bike, EBike.
+ Các đối tượng cụ thể (objects): b1, b2 (được khai báo trong hàm main).
 */