#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;
const double donGiaGoi = 1000.0;
const double donGiaTruyCap = 200.0;
const double VAT = 0.1;

class HopDong
{
private:
    string hoTen;
    string cmnd;
    string diaChi;

public:
    HopDong() {};
    virtual ~HopDong() {};

    virtual void nhapHopDong()
    {
        cin.ignore();
        cout << "- Nhap ho ten: ";
        getline(cin, hoTen);
        cout << "- Nhap CMND: ";
        getline(cin, cmnd);
        cout << "- Nhap dia chi: ";
        getline(cin, diaChi);
    }

    virtual void xuatHopDong() const
    {
        cout << "+ Ho ten: " << hoTen << ".\n"
             << "+ CMND: " << cmnd << ".\n"
             << "+ Dia chi: " << diaChi << ".\n";
    }

    // Thời gian: phút, Lưu lượng: MB.
    virtual double tinhCuoc(int thoiGian, int luuLuong) const = 0;
};

class CuocBasic : public HopDong
{
public:
    double tinhCuoc(int thoiGian, int luuLuong) const override
    {
        double cuocDienThoai = thoiGian * donGiaGoi;
        double cuocInternet = luuLuong * donGiaTruyCap;
        double cuocTong = cuocDienThoai + cuocInternet;
        return (cuocTong * (1 + VAT));
    }
};

class CuocDataFree : public HopDong
{
private:
    double cuocThueBao;
    int luuLuongMienPhi;

public:
    void nhapHopDong() override
    {
        HopDong::nhapHopDong();
        cout << "- Nhap cuoc thue bao: ";
        cin >> cuocThueBao;
        cout << "- Nhap luu luong mien phi: ";
        cin >> luuLuongMienPhi;
    }

    double tinhCuoc(int thoiGian, int luuLuong) const override
    {
        double cuocDienThoai = thoiGian * donGiaGoi;
        double cuocInternet = cuocThueBao;

        if (luuLuong > luuLuongMienPhi)
            cuocInternet += (luuLuong - luuLuongMienPhi) * donGiaTruyCap;

        double cuocTong = cuocDienThoai + cuocInternet;
        return (cuocTong * (1 + VAT));
    }
};

class CuocDataFix : public HopDong
{
public:
    double tinhCuoc(int thoiGian, int luuLuong) const override
    {
        double cuocDienThoai = thoiGian * donGiaGoi * 0.9;
        double cuocInternet = 1000000.0;
        double cuocTong = cuocDienThoai + cuocInternet;
        return (cuocTong * (1 + VAT));
    }
};

class QuanLyHopDong
{
private:
    vector<HopDong *> danhSach;

public:
    ~QuanLyHopDong()
    {
        for (int i = 0; i < danhSach.size(); i++)
            delete danhSach[i];
        danhSach.clear();
    }

    void dangKyHopDong()
    {
        int luaChon;

        cout << "===================== DANG KY HOP DONG =====================\n"
             << "| 1. Cuoc Basic.                                           |\n"
             << "| 2. Cuoc Data Free.                                       |\n"
             << "| 3. Cuoc Data Fix.                                        |\n"
             << "| 0. Thoat.                                                |\n"
             << "============================================================\n";

        cout << "--> Lua chon cua ban: ";
        cin >> luaChon;

        while (cin.fail() || luaChon < 0 || luaChon > 3)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "==> ERROR: Lua chon phai la so nguyen tu 0 den 3.\n"
                 << "--> Vui long nhap lai lua chon cua ban: ";
            cin >> luaChon;
        }

        if (luaChon == 0)
        {
            cout << "==> Quay tro lai menu chinh: QUAN LY HOP DONG.\n";
            return;
        }

        HopDong *hd = nullptr;
        if (luaChon == 1)
            hd = new CuocBasic();
        else if (luaChon == 2)
            hd = new CuocDataFree();
        else if (luaChon == 3)
            hd = new CuocDataFix();
        hd->nhapHopDong();
        danhSach.push_back(hd);
        cout << "==> Da dang ky hop dong thanh cong.\n";
    }

    void thongBaoCuoc()
    {
        if (danhSach.empty())
        {
            cout << "==> Danh sach hop dong dang rong.\n";
            return;
        }

        int thoiGian, luuLuong;
        cout << "- Nhap thoi gian (phut): ";
        cin >> thoiGian;
        cout << "- Nhap luu luong (MB): ";
        cin >> luuLuong;

        cout << "================= THONG BAO CUOC CUOI THANG ================\n";
        for (int i = 0; i < danhSach.size(); i++)
        {
            cout << "- Hop dong thu " << i + 1 << ":\n";
            danhSach[i]->xuatHopDong();
            cout << "+ Tong cuoc (da co VAT): " << (long long)danhSach[i]->tinhCuoc(thoiGian, luuLuong) << " VND.\n";
        }
        cout << "============================================================\n";
    }
};

int main()
{
    QuanLyHopDong quanLy;
    int luaChon;

    while (true)
    {
        cout << "===================== QUAN LY HOP DONG =====================\n"
             << "| 1. Dang ky hop dong.                                     |\n"
             << "| 2. Thong bao cuoc cuoi thang.                            |\n"
             << "| 0. Thoat.                                                |\n"
             << "============================================================\n";

        cout << "--> Lua chon cua ban: ";
        cin >> luaChon;

        while (cin.fail() || luaChon < 0 || luaChon > 2)
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cout << "==> ERROR: Lua chon phai la so nguyen tu 0 den 2.\n"
                 << "--> Vui long nhap lai lua chon cua ban: ";
            cin >> luaChon;
        }

        if (luaChon == 0)
        {
            cout << "==> Tam biet. Hen gap lai.\n";
            break;
        }

        if (luaChon == 1)
            quanLy.dangKyHopDong();
        else if (luaChon == 2)
            quanLy.thongBaoCuoc();
    }
    return 0;
}