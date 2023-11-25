//Main.cpp
#include "Hotel.h"
#include <iostream>
#include "HotelManager.h"

using namespace std;

int main() {
    HotelManager hotelManager;

    int luaChon;
    int maHotel;
    string tenHotel;
    float ratingHotel;

    Hotel* tempDiaChiHotel = nullptr; // khởi tạo trước giá trị = nullptr để tránh lỗi C360 C361

    do {

        cout << "====== MENU ======" << endl;
        cout << "1. Quan li khach san" << endl;
        cout << "2. Xem danh sach khach san" << endl;
        cout << "0. Thoat chuong trinh" << endl;
        cout << "Nhap lua chon cua ban: ";
        cin >> luaChon;
        system("cls");

        switch (luaChon) {
        case 1:
            int managerLuaChon;
            cout << "====== QUAN LI KHACH SAN ======" << endl;
            cout << "1. Them khach san" << endl;
            cout << "2. Xoa khach san" << endl;
            cout << "3. Sua thong tin khach san" << endl;
            cout << "0. Quay lai menu chinh" << endl;
            cout << "Nhap lua chon cua ban: ";
            cin >> managerLuaChon;

            switch (managerLuaChon) {
            case 1:
                cout << "\n====== THEM KHACH SAN MOI ======" << endl;
                cout << "Nhap thong tin khach san moi:" << endl;
                cout << "Ma khach san: ";
                cin >> maHotel;
                cout << "Ten khach san: ";
                cin.ignore(); // cclear buffer tránh bị end chương trình hoặc lặp enter
                getline(cin, tenHotel);
                cout << "Danh gia (tu 1-5 sao): ";
                cin >> ratingHotel;

                hotelManager.addHotel(Hotel(maHotel, tenHotel, ratingHotel));
                cout << "Da them khach san moi." << endl;
                break;
            case 2:
                cout << "\n====== XOA KHACH SAN ======" << endl;
                cout << "Danh sach khach san hien co:" << endl;
                hotelManager.hienThiTatCaHotel();
                cout << "Nhap ma khach san muon xoa: ";
                cin >> maHotel;
                hotelManager.deleteHotel(maHotel);
                break;
            case 3:
                cout << "\n====== SUA THONG TIN ======" << endl;
                cout << "Danh sach khach san hien co:" << endl;
                hotelManager.hienThiTatCaHotel();
                cout << "Nhap ma khach san muon sua thong tin: ";
                cin >> maHotel;
                cout << "Nhap thong tin moi cho khach san:" << endl;
                cout << "Ten khach san: ";
                cin.ignore(); // Xóa bộ đệm
                getline(cin, tenHotel);
                cout << "Danh gia (tu 1-5 sao): ";
                cin >> ratingHotel;
                hotelManager.suaThongTinKhachSan(maHotel, tenHotel, ratingHotel);
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
            }
            break;

        case 2:
            int viewLuaChon;
            cout << "====== XEM DANH SACH KHACH SAN ======" << endl;
            cout << "1. Hien thi danh sach khach san" << endl;
            cout << "2. Tim kiem khach san theo ma" << endl;
            cout << "0. Quay lai menu chinh" << endl;
            cout << "Nhap lua chon cua ban: ";
            cin >> viewLuaChon;

            switch (viewLuaChon) {
            case 1:
                cout << "\n====== DANH SACH KHACH SAN HIEN CO ======" << endl;
                hotelManager.hienThiTatCaHotel();
                break;
            case 2:
                cout << "Nhap ma khach san muon tim: ";
                cin >> maHotel;
                /*
                * biến tempDiaChiHotel lưu trữ địa chỉ trỏ tới hotel cần tìm, ban đầu là nullptr
                * nếu sau phuong thức tìm mà khác nullptr tức là tìm đc
                * != thì hiển thị hotel có địa chỉ là tempDiaChiHotel
                */
                tempDiaChiHotel = hotelManager.timHotelBangMaSoBST(maHotel);
                if (tempDiaChiHotel != nullptr) {
                    cout << "Thong tin khach san tim duoc:" << endl;
                    tempDiaChiHotel->hienThiTTHotel();
                }
                else {
                    cout << "Khong tim thay khach san voi ma " << maHotel << "." << endl;
                }
                break;
            case 0:
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
            }

            break;

        case 0:
            cout << "Tam biet!";
            break;

        default:
            cout << "Lua chon khong hop le." << endl;
        }
    } while (luaChon != 0);

    return 0;
}
