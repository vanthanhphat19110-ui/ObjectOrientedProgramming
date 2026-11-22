#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const long long donGiaPhongA = 1400000;
const long long donGiaPhongB = 900000;
const long long donGiaPhongC = 600000;

class HoSoBenhAn
{
private:
    vector<string> log;

public:
    void ghiHoSo(int ngay, const string &noiDung)
    {
        stringstream ss;
        ss << "         . Ngay " << setfill('0') << setw(2) << ngay << ": " << noiDung << ".";
        log.push_back(ss.str());
    }

    void inHoSo() const
    {
        if (log.empty())
        {
            cout << "       (Ho so benh an trong rong).\n";
            return;
        }

        for (const string &s : log)
            cout << s << "\n";
    }
};

class BenhNhan
{
protected:
    int id;
    long long tongVienPhi;
    HoSoBenhAn hoSo;

public:
    // Constructor.
    BenhNhan(int id) : id(id), tongVienPhi(0) {}

    // Virtual destructor.
    virtual ~BenhNhan() {}

    // Getter.
    int getId() const { return id; }
    virtual long long getTongVienPhi() const { return tongVienPhi; }

    // Methods.
    virtual bool laBenhNhanNoiTru() const = 0;

    virtual void inThongTinBenhNhan() const
    {
        cout << "- Ma so benh nhan: " << setfill('0') << setw(3) << id << ".\n";
        if (laBenhNhanNoiTru())
            cout << "   + Loai benh nhan: Noi tru.\n";
        else
            cout << "   + Loai benh nhan: Ngoai tru.\n";
        cout << "   + Tong vien phi: " << tongVienPhi << " VND.\n";
    }

    void xemHoSo() const
    {
        cout << "- Ma so benh nhan: " << setfill('0') << setw(3) << id << ".\n";
        if (laBenhNhanNoiTru())
            cout << "   + Loai benh nhan: Noi tru.\n";
        else
            cout << "   + Loai benh nhan: Ngoai tru.\n";
        cout << "   + Ho so benh an:\n";
        hoSo.inHoSo();
        cout << "==> Tong vien phi: " << tongVienPhi << " VND.\n";
    }
};

class BenhNhanNgoaiTru : public BenhNhan
{
public:
    // Constructor.
    BenhNhanNgoaiTru(int id, int ngayKhamBenh, long long phiKhamBenh) : BenhNhan(id) { congDonVienPhi(ngayKhamBenh, phiKhamBenh); }

    // Methods.
    void congDonVienPhi(int ngayKhamBenh, long long phiKhamBenh)
    {
        tongVienPhi += phiKhamBenh;

        string noiDung;
        noiDung = "Kham benh ngoai tru | Phi kham benh: " + to_string(phiKhamBenh) + " VND";
        hoSo.ghiHoSo(ngayKhamBenh, noiDung);
    }

    bool laBenhNhanNoiTru() const override { return false; }
};

class BenhNhanNoiTru : public BenhNhan
{
private:
    int ngayNhapVien;
    long long phiKhamBenhMoiNgay;
    char loaiPhong;
    bool daXuatVien;

public:
    // Constructor.
    BenhNhanNoiTru(int id, int ngayNhapVien, long long phiKhamBenhMoiNgay, char loaiPhong) : BenhNhan(id)
    {
        taiNhapVien(ngayNhapVien, phiKhamBenhMoiNgay, loaiPhong);
    }

    // Getter.
    long long getDonGiaPhong() const
    {
        switch (loaiPhong)
        {
        case 'A':
            return donGiaPhongA;
        case 'B':
            return donGiaPhongB;
        case 'C':
            return donGiaPhongC;
        default:
            return 0;
        }
    }

    // Methods.
    void taiNhapVien(int ngayNhapVien, long long phiKhamBenhMoiNgay, char loaiPhong)
    {
        this->ngayNhapVien = ngayNhapVien;
        this->phiKhamBenhMoiNgay = phiKhamBenhMoiNgay;
        this->loaiPhong = loaiPhong;
        this->daXuatVien = false;

        string noiDung;
        noiDung = "Nhap vien | Phi kham benh: " + to_string(phiKhamBenhMoiNgay) + " VND/ngay | Phong: " + this->loaiPhong;
        hoSo.ghiHoSo(ngayNhapVien, noiDung);
    }

    void xuatVien(int ngayXuatVien)
    {
        if (!daXuatVien)
        {
            int soNgayNhapVien = ngayXuatVien - ngayNhapVien;
            long long donGiaPhong = getDonGiaPhong();
            tongVienPhi = soNgayNhapVien * (phiKhamBenhMoiNgay + donGiaPhong);
            daXuatVien = true;

            string noiDung;
            noiDung = "Xuat vien | So ngay nhap vien: " + to_string(soNgayNhapVien) + " ngay | Vien phi: " + to_string(tongVienPhi) + " VND";
            hoSo.ghiHoSo(ngayXuatVien, noiDung);
        }
    }

    void tongKetVienPhi(int ngayTongKetVienPhi)
    {
        if (!daXuatVien)
        {
            int soNgayNhapVien = ngayTongKetVienPhi - ngayNhapVien;
            long long donGiaPhong = getDonGiaPhong();
            tongVienPhi = soNgayNhapVien * (phiKhamBenhMoiNgay + donGiaPhong);
            daXuatVien = true;

            string noiDung;
            noiDung = "Tong ket vien phi | Tinh trang: Chua xuat vien | Vien phi tam tinh: " + to_string(tongVienPhi) + " VND";
            hoSo.ghiHoSo(ngayTongKetVienPhi, noiDung);
        }
    }

    bool laBenhNhanNoiTru() const override { return true; }
};

class BenhVien
{
private:
    vector<BenhNhan *> danhSachBenhNhan;

    BenhNhan *timBenhNhan(int id) const
    {
        for (BenhNhan *p : danhSachBenhNhan)
        {
            if (p->getId() == id)
                return p;
        }
        return nullptr;
    }

public:
    // Destructor.
    ~BenhVien()
    {
        for (BenhNhan *p : danhSachBenhNhan)
        {
            delete p;
            p = nullptr;
        }
        danhSachBenhNhan.clear();
    }

    // Methods.
    void docFileLog(const string &tenFile)
    {
        ifstream fin(tenFile);
        if (!fin)
        {
            cerr << "ERROR: Khong the mo file: " << tenFile << ".\n";
            return;
        }

        while (true)
        {
            int ngay, id;
            string lenh;
            fin >> ngay >> id >> lenh;

            if (lenh == "KB")
            {
                long long phiKhamBenh;
                fin >> phiKhamBenh;

                BenhNhan *p = timBenhNhan(id);
                if (p == nullptr)
                {
                    p = new BenhNhanNgoaiTru(id, ngay, phiKhamBenh);
                    danhSachBenhNhan.push_back(p);
                }
                else
                {
                    BenhNhanNgoaiTru *outP = dynamic_cast<BenhNhanNgoaiTru *>(p);
                    if (outP != nullptr)
                        outP->congDonVienPhi(ngay, phiKhamBenh);
                }
            }
            else if (lenh == "NV")
            {
                long long phiKhamBenhMoiNgay;
                char loaiPhong;
                fin >> phiKhamBenhMoiNgay >> loaiPhong;

                BenhNhan *p = timBenhNhan(id);
                if (p == nullptr)
                {
                    p = new BenhNhanNoiTru(id, ngay, phiKhamBenhMoiNgay, loaiPhong);
                    danhSachBenhNhan.push_back(p);
                }
                else
                {
                    BenhNhanNoiTru *inP = dynamic_cast<BenhNhanNoiTru *>(p);
                    if (inP != nullptr)
                        inP->taiNhapVien(ngay, phiKhamBenhMoiNgay, loaiPhong);
                }
            }
            else if (lenh == "XV")
            {
                BenhNhan *p = timBenhNhan(id);
                BenhNhanNoiTru *inP = dynamic_cast<BenhNhanNoiTru *>(p);
                if (inP != nullptr)
                    inP->xuatVien(ngay);
            }
            else if (lenh == "TKVP")
            {
                for (BenhNhan *p : danhSachBenhNhan)
                {
                    BenhNhanNoiTru *inP = dynamic_cast<BenhNhanNoiTru *>(p);
                    if (inP != nullptr)
                        inP->tongKetVienPhi(ngay);
                }
                break;
            }
        }

        fin.close();
    }

    void inDanhSachBenhNhan() const
    {
        int demBenhNhanNgoaiTru = 0, demBenhNhanNoiTru = 0;
        long long tongDoanhThu = 0;

        cout << "================================================== BANG THONG KE VIEN PHI ==================================================\n";
        for (BenhNhan *p : danhSachBenhNhan)
        {
            p->inThongTinBenhNhan();

            if (p->laBenhNhanNoiTru())
                demBenhNhanNoiTru++;
            else
                demBenhNhanNgoaiTru++;

            tongDoanhThu += p->getTongVienPhi();
        }

        cout << "----------------------------------------------------------------------------------------------------------------------------\n"
             << "- So benh nhan ngoai tru: " << demBenhNhanNgoaiTru << ".\n"
             << "- So benh nhan noi tru: " << demBenhNhanNoiTru << ".\n"
             << "- Tong doanh thu cua benh vien: " << tongDoanhThu << " VND.\n"
             << "============================================================================================================================\n";
    }

    void traCuuHoSoBenhAn(int id) const
    {
        cout << "================================================== TRA CUU HO SO BENH AN ===================================================\n";
        BenhNhan *p = timBenhNhan(id);
        if (p == nullptr)
            cout << "==> Khong tim thay benh nhan co id = " << id << ".\n";
        else
            p->xemHoSo();
        cout << "============================================================================================================================\n";
    }

    void inTatCaHoSoBenhAn() const
    {
        cout << "================================================== DANH SACH HO SO BENH AN =================================================\n";
        for (BenhNhan *p : danhSachBenhNhan)
            p->xemHoSo();
        cout << "============================================================================================================================\n";
    }
};

int main()
{
    BenhVien bv115;

    // Đọc file và in kết quả.
    bv115.docFileLog("HospitalLog.txt");
    bv115.inDanhSachBenhNhan();

    // Tra cứu hồ sơ bệnh án.
    bv115.traCuuHoSoBenhAn(1);
    bv115.traCuuHoSoBenhAn(2);
    bv115.traCuuHoSoBenhAn(3);
    bv115.traCuuHoSoBenhAn(4);
    bv115.traCuuHoSoBenhAn(5);
    bv115.traCuuHoSoBenhAn(6);

    return 0;
}