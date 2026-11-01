#ifndef _NHANVIEN_
#define _NHANVIEN_

#include <iostream>
#include <string>
using namespace std;

class NhanVien
{
private:
    string ten;
    string diaChi;
    string maNV;

public:
    virtual void input()
    {
        getline(cin, ten);
        getline(cin, diaChi);
        getline(cin, maNV);
    }

    // virtual long long tinhLuong() = 0; // OK
    virtual long long tinhLuong()
    {
        return 0;
    }
};

class NVSanXuat : public NhanVien
{
private:
    int soSanPham;

public:
    void input()
    {
        NhanVien::input();
        cout << "Nhap so san pham: ";
        cin >> soSanPham;
    }
    long long tinhLuong()
    {
        return soSanPham * 1000;
    }
};

class NVCongNhat : public NhanVien
{
private:
    int soNgayLam;

public:
    long long tinhLuong()
    {
        return soNgayLam * 300000;
    }
};

#endif