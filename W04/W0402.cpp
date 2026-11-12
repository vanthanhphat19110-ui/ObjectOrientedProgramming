#include <iostream>
#include <string>
using namespace std;

class BankAccount
{
protected:
    string CCCD;
    string hoTen;
    long long soDu;

public:
    BankAccount() { soDu = 0; }
    BankAccount(const string &CCCD, const string &hoTen, long long soDu)
    {
        this->CCCD = CCCD;
        this->hoTen = hoTen;
        this->soDu = soDu;
    }

    void napTien(long long tienNapThem)
    {
        if (tienNapThem < 0)
        {
            cout << "ERROR: Khong the nap tien am.\n";
            return;
        }

        soDu += tienNapThem;
        cout << "==> Nap tien thanh cong. So du hien tai: " << soDu << ".\n";
    }

    void rutTien(long long tienRutRa)
    {
        if (tienRutRa < 0)
        {
            cout << "ERROR: Khong the rut tien am.\n";
            return;
        }

        if (tienRutRa > soDu)
        {
            cout << "ERROR: So tien muon rut ra nhieu hon so du.\n";
            return;
        }

        soDu -= tienRutRa;
        cout << "==> Rut tien thanh cong. So du hien tai: " << soDu << ".\n";
    }

    void xemSoDu() { cout << "==> So du hien tai: " << soDu << ".\n"; }
};

class SavingAccount : public BankAccount
{
private:
    float laiSuat;
    int kiHan;
    int soThangDaGui;

    long long tinhTienLai() { return (long long)(soDu * (laiSuat / 100.0) * (soThangDaGui / 12.0)); }

public:
    SavingAccount() : BankAccount()
    {
        laiSuat = 0;
        kiHan = 0;
        soThangDaGui = 0;
    }

    SavingAccount(const string &CCCD, const string &hoTen, long long soDu, float laiSuat, int kiHan, int soThangDaGui)
        : BankAccount(CCCD, hoTen, soDu)
    {
        this->laiSuat = laiSuat;
        this->kiHan = kiHan;
        this->soThangDaGui = (soThangDaGui > 0) ? soThangDaGui : 0;
    }

    void capNhatSoThangDaGui(int soThangMoi)
    {
        if (soThangMoi > soThangDaGui)
        {
            soThangDaGui = soThangMoi;
            cout << "==> Cap nhat thanh cong. So thang hien tai: " << soThangDaGui << ".\n";
        }
        else
            cout << "ERROR: So thang moi phai lon hon so thang da gui.\n";
    }

    void napTien(long long tienNapThem)
    {
        if (tienNapThem < 0)
        {
            cout << "ERROR: Khong the nap tien am.\n";
            return;
        }

        if (soThangDaGui < kiHan)
        {
            cout << "ERROR: Chua den ki han thanh toan. Khong the nap them tien.\n";
            return;
        }

        long long tienLai = tinhTienLai();
        soDu = soDu + tienLai + tienNapThem;
        soThangDaGui = 0;
        cout << "==> Nap tien thanh cong. So du hien tai: " << soDu << ".\n";
    }

    void rutTien(long long tienRutRa)
    {
        if (tienRutRa < 0)
        {
            cout << "ERROR: Khong the rut tien am.\n";
            return;
        }

        if (soThangDaGui < kiHan)
        {
            cout << "ERROR: Chua den ki han thanh toan. Khong the rut tien.\n";
            return;
        }

        long long tongSoTien = soDu + tinhTienLai();
        if (tienRutRa > tongSoTien)
        {
            cout << "ERROR: So tien muon rut ra lon hon tong so tien.\n";
            return;
        }

        soDu = tongSoTien - tienRutRa;
        soThangDaGui = 0;
        cout << "==> Rut tien thanh cong. So du hien tai: " << soDu << ".\n";
    }

    void xemSoDu()
    {
        long long hienTai = soDu;
        if (soThangDaGui >= kiHan)
            hienTai += tinhTienLai();

        cout << "==> So du hien tai: " << hienTai << ".\n";
    }

    void tatToan()
    {
        if (soThangDaGui >= kiHan)
            soDu += tinhTienLai();

        soThangDaGui = 0;
        cout << "==> Tat toan thanh cong. So du hien tai: " << soDu << ".\n ";
    }
};