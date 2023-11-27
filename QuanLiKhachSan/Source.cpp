#include <iostream>
#include <string>

using namespace std;

class Hotel {
private:
    int maHotel;
    string tenHotel;
    string diaChiHotel;
    float ratingHotel;

public:
    Hotel(int maHotel, const string& ten, const string& diaChi, float saoRating)
        : maHotel(maHotel), tenHotel(ten), diaChiHotel(diaChi), ratingHotel(saoRating) {}

    void hienThiTTHotel() {
        cout << "ID khach san: " << maHotel << endl;
        cout << "Ten khach san: " << tenHotel << endl;
        cout << "Dia chi khach san: " << diaChiHotel << endl;
        cout << "Danh gia sao: " << ratingHotel << " sao" << endl;
    }

    int getMaHotel() const {
        return maHotel;
    }
};

class BSTNode {
public:
    Hotel hotel;
    BSTNode* left;
    BSTNode* right;

    BSTNode(const Hotel& h) : hotel(h), left(nullptr), right(nullptr) {}
};

class HotelManager {
private:
    BSTNode* root;

    // Hỗ trợ thêm node vào BST
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


    // Hỗ trợ tìm kiếm node trong BST
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

    // Hỗ trợ xóa node trong BST
    void deleteBSTNodes(BSTNode* node) {
        if (node != nullptr) {
            deleteBSTNodes(node->left);
            deleteBSTNodes(node->right);
            delete node;
        }
    }

    // Hàm tìm node nhỏ nhất từ một node cho trước trong BST
    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Hỗ trợ xóa node trong BST
    void deleteHotelFromBST(BSTNode*& node, int code) {
        if (node == nullptr) {
            return;
        }

        if (code < node->hotel.getMaHotel()) {
            deleteHotelFromBST(node->left, code);
        }
        else if (code > node->hotel.getMaHotel()) {
            deleteHotelFromBST(node->right, code);
        }
        else {
            if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                node = temp;
            }
            else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                node = temp;
            }
            else {
                BSTNode* temp = findMin(node->right);
                node->hotel = temp->hotel;
                deleteHotelFromBST(node->right, temp->hotel.getMaHotel());
            }
        }
    }

public:
    HotelManager() : root(nullptr) {}

    void addHotel(const Hotel& hotel) {
        if (root == nullptr) {
            root = new BSTNode(hotel);
        }
        else {
            root = insertBSTNode(root, hotel);
        }
    }

    Hotel nhapThongTinKhachSanMoi() {
        int maHotel;
        string tenHotel, diaChiHotel;
        float ratingHotel;

        cout << "Nhap thong tin khach san moi:" << endl;
        cout << "Ma khach san: ";
        cin >> maHotel;
        cout << "Ten khach san: ";
        cin.ignore(); // Xóa bộ đệm
        getline(cin, tenHotel);
        cout << "Dia chi khach san: ";
        getline(cin, diaChiHotel); // Nhập địa chỉ khách sạn
        cout << "Danh gia (tu 1-5 sao): ";
        cin >> ratingHotel;

        return Hotel(maHotel, tenHotel, diaChiHotel, ratingHotel);
    }

    //In-Oder Traversal <- BST giup hien thi khach san theo thu tu dang dan cua ma khach san
    void duyetGocGiua(BSTNode* node) {
        if (node != nullptr) {
            duyetGocGiua(node->left);
            node->hotel.hienThiTTHotel();
            duyetGocGiua(node->right);
        }
    }

    void hienThiTatCaHotel() {
        cout << "\n====== DANH SACH KHACH SAN HIEN CO ======" << endl;
        duyetGocGiua(root);
    }


    Hotel* timHotelBangMaSo(int code) {
        return searchBSTNode(root, code);
    }

    void deleteHotel(int code) {
        deleteHotelFromBST(root, code);
    }

    void suaThongTinKhachSan(int code, const string& tenMoi, const string& diaChiMoi, float ratingMoi) {
        BSTNode* current = root;

        while (current != nullptr) {
            if (code < current->hotel.getMaHotel()) {
                current = current->left;
            }
            else if (code > current->hotel.getMaHotel()) {
                current = current->right;
            }
            else {
                current->hotel = Hotel(code, tenMoi, diaChiMoi, ratingMoi);
                cout << "Da cap nhat thong tin cho khach san co ma " << code << endl;
                return;
            }
        }
        cout << "Khong tim thay khach san voi ma " << code << "." << endl;
    }


    ~HotelManager() {
        deleteBSTNodes(root);
    }
};

int main() {
    HotelManager hotelManager;
    string tenHotel, diaChiHotel;
    float ratingHotel;
    Hotel* tempDiaChiHotel = nullptr;
    int luaChon;
    int maHotel;

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
                system("cls");
            case 1:
                cout << "\n====== THEM KHACH SAN MOI ======" << endl;
                hotelManager.addHotel(hotelManager.nhapThongTinKhachSanMoi());
                cout << "Da them khach san moi." << endl;
                break;
            case 2:
                system("cls");
                cout << "\n====== XOA KHACH SAN ======" << endl;
                cout << "Danh sach khach san hien co:" << endl;
                hotelManager.hienThiTatCaHotel();
                cout << "Nhap ma khach san muon xoa: ";
                cin >> maHotel;
                hotelManager.deleteHotel(maHotel);
                break;
            case 3:
                system("cls");
                cout << "\n====== SUA THONG TIN ======" << endl;
                cout << "Danh sach khach san hien co:" << endl;
                hotelManager.hienThiTatCaHotel();
                cout << "Nhap ma khach san muon sua thong tin: ";
                cin >> maHotel;
                cout << "Nhap thong tin moi cho khach san:" << endl;
                cout << "Ten khach san: ";
                cin.ignore(); // xoa buffer
                getline(cin, tenHotel);
                cout << "Dia chi khach san: ";
                getline(cin, diaChiHotel);
                cout << "Danh gia (tu 1-5 sao): ";
                cin >> ratingHotel;
                hotelManager.suaThongTinKhachSan(maHotel, tenHotel, diaChiHotel, ratingHotel);
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
                system("cls");
                cout << "\n====== DANH SACH KHACH SAN HIEN CO ======" << endl;
                hotelManager.hienThiTatCaHotel();
                break;
            case 2:
                system("cls");
                cout << "Nhap ma khach san muon tim: ";
                cin >> maHotel;

                // Sử dụng hàm timHotelBangMaSo của HotelManager thay vì timHotelBangMaSoBST
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
