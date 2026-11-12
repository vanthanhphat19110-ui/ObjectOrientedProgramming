#ifndef _NHANVIEN_
#define _NHANVIEN_
#include<iostream>
using namespace std;
class NhanVien {
private:
    string ten;
    string diaChi;
    string maNV;
public:
    void input(){
        getline(cin, ten);
        getline(cin, diaChi);
        getline(cin, maNV);

    }

    // virtual long long tinhLuong() = 0; // OK
    long long tinhLuong(){
        return 0;
    }

    virtual void output(){
        cout << "Ma NV: " << maNV << endl;
        cout << "Ho ten: " << ten << endl;
        cout << "Dia chi: " << diaChi << endl;

        // cout << "Luong: " << tinhLuong() << endl; 
        // // tra lai luong 1000 cua thay Tung
    }

    NhanVien(): ten("No Name"), diaChi("Binh Duong"), maNV("0") {
        cout << "NhanVien - Def cons" << endl;
    }

    NhanVien(string maNV, string ten, string diaChi){
        cout << "NhanVien - Cons 3 args" << endl;
        this->ten = ten;
        this->diaChi = diaChi;
        this->maNV = maNV;

    }
    virtual ~NhanVien(){
        cout << "NhanVien - Des" << endl;
    }
};

class NVSanXuat : public NhanVien {
private:
    int soSanPham;
public:
    void input(){
        NhanVien::input();
        cout << "Nhap so san pham: ";
        cin >> soSanPham;
    }
    long long tinhLuong(){
        return soSanPham * 1000;
    }

    void output(){
        NhanVien::output();
        cout << "So SP: " << soSanPham << endl;
        cout << "Luong: " << tinhLuong() << endl;
    }

    NVSanXuat(): soSanPham(0) {
        cout << "NVSanXuat - Def cons" << endl;
    };
    NVSanXuat(string maso, string hoten, string diachi)
    :NhanVien(maso, hoten, diachi){
        cout << "NVSanXuat - Cons with 3 args" << endl;
        soSanPham=0;
    }
    NVSanXuat(string maso, string hoten,string diachi,int sosanpham): NhanVien(maso,hoten,diachi){
        cout << "NVSanXuat - Cons with 4 args" << endl;
        soSanPham = sosanpham;
    }

    // // copy cons NVSanXuat
    // NVSanXuat(const NVSanXuat& other) {
    //     cout << "NVSanXuat - Copy cons" << endl;
    //     *this = other;
    // }

    // copy cons NVSanXuat
    NVSanXuat(const NVSanXuat& other): NhanVien(other) {
        cout << "NVSanXuat - Copy cons" << endl;
        soSanPham = other.soSanPham;
    }

    ~NVSanXuat(){
        cout << "NVSanXuat - Des" << endl;
    }

    
        

};

class NVCongNhat : public NhanVien {
private:
    int soNgayLam;
public:
    long long tinhLuong(){
        return soNgayLam * 300000;
    }
};

void f1(NhanVien nv){
    cout << "f1" << endl;
    nv.output();
}

void f2(NhanVien *p){
    cout << "f2" << endl;
    p->output();
}

void f3(NhanVien &nv){
    cout << "f3" << endl;
    nv.output();
}
#endif