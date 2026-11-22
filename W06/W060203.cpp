#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

string trim(const string &s)
{
    int first = s.find_first_not_of(" \t\r\n");
    if (first == string::npos)
        return "";
    int last = s.find_last_not_of(" \t\r\n");
    return s.substr(first, (last - first + 1));
}

class Config
{
private:
    double donGiaGoi;
    double donGiaTruyCap;
    double VAT;
    double dataFixTiLeGiamGiaCuocDienThoai;
    double dataFixCuocInternetCoDinh;

    // Private constructor.
    Config()
    {
        donGiaGoi = 1000.0;
        donGiaTruyCap = 200.0;
        VAT = 0.1;
        dataFixTiLeGiamGiaCuocDienThoai = 0.1;
        dataFixCuocInternetCoDinh = 1000000.0;
    }

public:
    // Remove copy constructor and copy assignment operator.
    Config(const Config &) = delete;
    Config &operator=(const Config &) = delete;

    // Apply Singleton Design Pattern.
    static Config &getInstance()
    {
        static Config instance;
        return instance;
    }

    // Đọc file cấu hình.
    void docFileConfig(const string &filename)
    {
        ifstream fin(filename);

        if (!fin)
        {
            cout << "ERROR: Khong the mo file \"" << filename << "\".\n"
                 << "==> Chuong trinh se su dung gia tri mac dinh.\n";
            return;
        }

        string line;
        while (getline(fin, line))
        {
            line = trim(line);

            // Bỏ qua dòng rỗng hoặc dòng comment.
            if (line.empty() || line[0] == '#')
                continue;

            int pos = line.find('=');
            if (pos != string::npos)
            {
                // Xác định key và value.
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);
                key = trim(key);
                value = trim(value);

                try
                {
                    if (key == "DON_GIA_GOI")
                        donGiaGoi = stod(value);
                    else if (key == "DON_GIA_TRUY_CAP")
                        donGiaTruyCap = stod(value);
                    else if (key == "VAT")
                        VAT = stod(value);
                    else if (key == "TI_LE_GIAM_GIA_CUOC_DIEN_THOAI")
                        dataFixTiLeGiamGiaCuocDienThoai = stod(value);
                    else if (key == "CUOC_INTERNET_CO_DINH")
                        dataFixCuocInternetCoDinh = stod(value);
                }
                catch (...)
                {
                    cout << "ERROR: Gia tri khong hop le o dong: " << line << "\n";
                }
            }
        }

        fin.close();
        cout << "==> Da doc du lieu tu file \"" << filename << "\" thanh cong.\n";
    }

    // Getters.
    double getDonGiaGoi() const { return donGiaGoi; }
    double getDonGiaTruyCap() const { return donGiaTruyCap; }
    double getVAT() const { return VAT; }
    double getTiLeGiamGiaCuocDienThoai() const { return dataFixTiLeGiamGiaCuocDienThoai; }
    double getCuocInternetCoDinh() const { return dataFixCuocInternetCoDinh; }
};

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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "- Nhap ho ten: ";
        getline(cin, hoTen);
        cout << "- Nhap CMND: ";
        getline(cin, cmnd);
        cout << "- Nhap dia chi: ";
        getline(cin, diaChi);
    }

    virtual void xuatHopDong() const
    {
        cout << "   + Ho ten: " << hoTen << ".\n"
             << "   + CMND: " << cmnd << ".\n"
             << "   + Dia chi: " << diaChi << ".\n";
    }

    // Thời gian: phút, Lưu lượng: MB.
    virtual double tinhCuoc(int thoiGian, int luuLuong) const = 0;
};

class CuocBasic : public HopDong
{
public:
    double tinhCuoc(int thoiGian, int luuLuong) const override
    {
        const Config &cfg = Config::getInstance();
        double cuocDienThoai = thoiGian * cfg.getDonGiaGoi();
        double cuocInternet = luuLuong * cfg.getDonGiaTruyCap();
        double cuocTong = cuocDienThoai + cuocInternet;
        return (cuocTong * (1 + cfg.getVAT()));
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
        const Config &cfg = Config::getInstance();
        double cuocDienThoai = thoiGian * cfg.getDonGiaGoi();
        double cuocInternet = cuocThueBao;

        if (luuLuong > luuLuongMienPhi)
            cuocInternet += (luuLuong - luuLuongMienPhi) * cfg.getDonGiaTruyCap();

        double cuocTong = cuocDienThoai + cuocInternet;
        return (cuocTong * (1 + cfg.getVAT()));
    }
};

class CuocDataFix : public HopDong
{
public:
    double tinhCuoc(int thoiGian, int luuLuong) const override
    {
        const Config &cfg = Config::getInstance();
        double cuocDienThoai = thoiGian * cfg.getDonGiaGoi() * (1.0 - cfg.getTiLeGiamGiaCuocDienThoai());
        double cuocInternet = cfg.getCuocInternetCoDinh();
        double cuocTong = cuocDienThoai + cuocInternet;
        return (cuocTong * (1 + cfg.getVAT()));
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
            cout << "   + Tong cuoc (da co VAT): " << (long long)danhSach[i]->tinhCuoc(thoiGian, luuLuong) << " VND.\n";
        }
        cout << "============================================================\n";
    }
};

int main()
{
    Config::getInstance().docFileConfig("config.txt");
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