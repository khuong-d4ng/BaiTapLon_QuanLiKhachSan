#include <iostream>
#include <string>

using namespace std;

class Hotel {
private:
    int maHotel;        //id khach san
    string tenHotel;    
    float ratingHotel;   //danh gia: sao 1-5

public:
    Hotel(int maHotel, const string& ten, float saoRating) : maHotel(maHotel), tenHotel(ten), ratingHotel(saoRating) {}

    void hienThiTTHotel() {
        cout << "Hotel Code: " << maHotel << endl;
        cout << "Hotel Name: " << tenHotel << endl;
        cout << "Star Rating: " << ratingHotel << " stars" << endl;
    }

    int getMaHotel() const {
       return maHotel;
    }
};

class Node {
public:
    Hotel hotel;
    Node* next;

    Node(const Hotel& h) : hotel(h), next(nullptr) {}
};

class quanLiHotel {
private:
    Node* head;

public:
    quanLiHotel() : head(nullptr) {}

    void addHotel(const Hotel& hotel) {
        Node* newNode = new Node(hotel);
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void hienThiTatCaHotel() {
        Node* temp = head;
        while (temp != nullptr) {
            temp->hotel.hienThiTTHotel();
            cout << "--------------------" << endl;
            temp = temp->next;
        }
    }

    // tim kiem khach san dua tren makhachsan
    Hotel* timHotelBangMaSo(int code) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->hotel.getMaHotel() == code) {
                return &(temp->hotel);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // giai phong' bo nho' kkk
    ~quanLiHotel() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    quanLiHotel hotelManager;

    int luaChon;
    int maHotel;
    string tenHotel;
    float ratingHotel;

    Hotel* tempDiaChiHotel = nullptr; //khai bao = nullptr de tranh loi C2360, C2361


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
            cout << "0. Quay lai menu chinh" << endl;
            cout << "Nhap lua chon cua ban: ";
            cin >> managerLuaChon;

            switch (managerLuaChon) {
            case 1:
                cout << "Nhap thong tin khach san moi:" << endl;
                cout << "Ma khach san: ";
                cin >> maHotel;
                cout << "Ten khach san: ";
                cin.ignore(); // Clear buffer
                getline(cin, tenHotel);
                cout << "Danh gia (tu 1-5 sao): ";
                cin >> ratingHotel;

                hotelManager.addHotel(Hotel(maHotel, tenHotel, ratingHotel));
                cout << "Da them khach san moi." << endl;
                break;
            case 2:
                cout << "Nhap ma khach san muon xoa: ";
                cin >> maHotel;
                // Viết code để xóa khách sạn với mã tương ứng (maHotel)
                // hotelManager.deleteHotel(maHotel);
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
                cout << "Danh sach khach san hien co:" << endl;
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
                tempDiaChiHotel = hotelManager.timHotelBangMaSo(maHotel); 
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
