#include "NhanVien.h"

int main(){
    // // NhanVien nv1;
    // // nv1.input();

    // // NVSanXuat sx1;
    // // sx1.input();

    // // NVCongNhat cn1;
    // // cn1.input();

    // // NhanVien nv1;
    // // cout << "nv1" << endl;
    // // nv1.output();
    // // cout << endl;

    // // NhanVien nv2("1", "Thanh", "TPHCM");
    // // cout << "nv2" << endl;
    // // nv2.output();
    // // cout << endl;

    // // NVSanXuat sx1;
    // // cout << "sx1" << endl;
    // // sx1.output();
    // // cout << endl;

    // // NVSanXuat sx2("2", "Tung", "TPHCM - Khu VIP");
    // // cout << "sx2" << endl;
    // // sx2.output();
    // // cout << endl;

    // // NVSanXuat sx3("3", "Tung Son", "TPHCM - Khu VIP", 1);
    // // cout << "sx3" << endl;
    // // sx3.output();
    // // cout << endl;

    // // NVSanXuat sx4(sx3);
    // // // ko cần code copy cons trong truong hop nay
    // // cout << "sx4" << endl;
    // // sx4.output();
    // // cout << endl;

    // NhanVien nv2("1", "Thanh", "TPHCM");
    // NVSanXuat sx3("3", "Tung Son", "TPHCM - Khu VIP", 1);

    // // f1(nv2);
    // // f1(sx3);

    // // f2(&sx3);

    // // f3(sx3);

    NhanVien *p;
    p = new NVSanXuat("2", "Tung", "TPHCM - Khu VIP");
    delete p;

    return 0;
}

// NhanVien - Cons with 3 args
// NVSanXuat - Cons with 3 args
// NhanVien - Des 

