#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const long long donGiaPhongA = 1400000;
const long long donGiaPhongB = 900000;
const long long donGiaPhongC = 600000;

class BenhNhan
{
protected:
    int id;
    long long tongVienPhi;

public:
    // Constructor.
    BenhNhan(int id) : id(id) {}

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
            cout << "   + Loai benh nhan: noi tru.\n";
        else
            cout << "   + Loai benh nhan: ngoai tru.\n";
        cout << "   + Tong vien phi: " << tongVienPhi << " VND.\n";
    }
};

class BenhNhanNgoaiTru : public BenhNhan
{
public:
    // Constructor.
    BenhNhanNgoaiTru(int id, long long phiKhamBenh) : BenhNhan(id) { tongVienPhi = phiKhamBenh; }

    // Methods.
    void congDonVienPhi(long long phiKhamBenh) { tongVienPhi += phiKhamBenh; }

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
        this->ngayNhapVien = ngayNhapVien;
        this->phiKhamBenhMoiNgay = phiKhamBenhMoiNgay;
        this->loaiPhong = loaiPhong;
        this->daXuatVien = false;
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
    }

    void xuatVien(int ngayXuatVien)
    {
        if (!daXuatVien)
        {
            int soNgayNhapVien = ngayXuatVien - ngayNhapVien;
            long long donGiaPhong = getDonGiaPhong();
            tongVienPhi = soNgayNhapVien * (phiKhamBenhMoiNgay + donGiaPhong);
            daXuatVien = true;
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
                    p = new BenhNhanNgoaiTru(id, phiKhamBenh);
                    danhSachBenhNhan.push_back(p);
                }
                else
                {
                    BenhNhanNgoaiTru *outP = dynamic_cast<BenhNhanNgoaiTru *>(p);
                    if (outP != nullptr)
                        outP->congDonVienPhi(phiKhamBenh);
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

        cout << "============================ BANG THONG KE VIEN PHI ============================\n";
        for (BenhNhan *p : danhSachBenhNhan)
        {
            p->inThongTinBenhNhan();

            if (p->laBenhNhanNoiTru())
                demBenhNhanNoiTru++;
            else
                demBenhNhanNgoaiTru++;

            tongDoanhThu += p->getTongVienPhi();
        }

        cout << "--------------------------------------------------------------------------------\n"
             << "- So benh nhan ngoai tru: " << demBenhNhanNgoaiTru << ".\n"
             << "- So benh nhan noi tru: " << demBenhNhanNoiTru << ".\n"
             << "- Tong doanh thu cua benh vien: " << tongDoanhThu << " VND.\n"
             << "================================================================================\n";
    }
};

int main()
{
    BenhVien bv115;
    bv115.docFileLog("HospitalLog.txt");
    bv115.inDanhSachBenhNhan();
    return 0;
}