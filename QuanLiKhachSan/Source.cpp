/*
* 
* ===================== KHÔNG THAO TÁC Ở ĐÂY ========================
#include <iostream>
#include <string>

using namespace std;

class Hotel {
private:
    int maHotel;
    string tenHotel;
    float ratingHotel;

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

class BSTNode {
public:
    Hotel hotel;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Hotel& h) : hotel(h), left(nullptr), right(nullptr) {}
};

class quanLiHotel {
private:
    Node* head;
    Node* tail;
    BSTNode* root;

    //hỗ trợ thêm node vào BST
    BSTNode* insertBSTNode(BSTNode* node, const Hotel& hotel) {
        if (node == nullptr) {
            return new BSTNode(hotel);
        }

        if (hotel.getMaHotel() < node->hotel.getMaHotel()) {
            node->left = insertBSTNode(node->left, hotel);
        }
        else if (hotel.getMaHotel() > node->hotel.getMaHotel()) {
            node->right = insertBSTNode(node->right, hotel);
        }

        return node;
    }

    //hỗ trợ tìm kiếm node trong BST
    Hotel* searchBSTNode(BSTNode* node, int code) {
        if (node == nullptr || node->hotel.getMaHotel() == code) {
            if (node != nullptr) {
                return &(node->hotel);
            }
            return nullptr;
        }

        if (code < node->hotel.getMaHotel()) {
            return searchBSTNode(node->left, code);
        }
        else {
            return searchBSTNode(node->right, code);
        }
    }

    //giải phóng bộ nhớ của BST
    void deleteBSTNodes(BSTNode* node) {
        if (node != nullptr) {
            deleteBSTNodes(node->left);
            deleteBSTNodes(node->right);
            delete node;
        }
    }

public:
    quanLiHotel() : head(nullptr), tail(nullptr), root(nullptr) {}

    void addHotel(const Hotel& hotel) {
        root = insertBSTNode(root, hotel);

        Node* newNode = new Node(hotel);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
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

    Hotel* timHotelBangMaSoBST(int code) {
        return searchBSTNode(root, code);
    }

    void deleteHotel(int code) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->hotel.getMaHotel() == code) {
                if (current == head) {
                    head = current->next;
                }
                else {
                    prev->next = current->next;
                    if (current == tail) {
                        tail = prev;
                    }
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Khong tim thay khach san voi ma " << code << " de xoa." << endl;
    }

    void suaThongTinKhachSan(int code, const string& tenMoi, float ratingMoi) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->hotel.getMaHotel() == code) {
                temp->hotel = Hotel(code, tenMoi, ratingMoi);
                return;
            }
            temp = temp->next;
        }
        cout << "Khong tim thay khach san voi ma " << code << " de sua thong tin." << endl;
    }

    // giai phong' bo nho'
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
*/