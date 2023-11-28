#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

using namespace std;

class Hotel {
private:
    int idHotel;
    string tenHotel;
    string diaChiHotel;
    float ratingHotel;

public:
    Hotel(int idHotel, const string& ten, const string& diaChi, float saoRating)
        : idHotel(idHotel), tenHotel(ten), diaChiHotel(diaChi), ratingHotel(saoRating) {}

    void hienThiTTHotel() const {
        cout << "\t---------- HOTEL ----------" << endl;
        cout << "\tID khach san: " << idHotel << endl;
        cout << "\tTen khach san: " << tenHotel << endl;
        cout << "\tDia chi khach san: " << diaChiHotel << endl;
        cout << "\tDanh gia sao: " << ratingHotel << " sao" << endl;
        cout << "\t---------------------------" << endl;
    }

    int getMaHotel() const {
        return idHotel;
    }

    string getTenHotel() const {
        return tenHotel;
    }

    string getDiaChiHotel() const {
        return diaChiHotel;
    }

    float getRatingHotel() const {
        return ratingHotel;
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

    BSTNode* getRoot() const {
        return root;
    }

    void addHotel(const Hotel& hotel) {
        if (root == nullptr) {
            root = new BSTNode(hotel);
        }
        else {
            // Kiểm tra xem mã khách sạn đã tồn tại chưa
            if (timHotelBangMaSo(hotel.getMaHotel()) != nullptr) {
                cout << "Khach san voi ma so da ton tai. Khong the them." << endl;
                return;
            }
            root = insertBSTNode(root, hotel);
        }
    }

    Hotel nhapThongTinKhachSanMoi() {
        int idHotel;
        string tenHotel, diaChiHotel;
        float ratingHotel;

        cout << "Nhap thong tin khach san moi:" << endl;
        // mã khách sạn dưới dạng chuỗi
        string strMaHotel;
        bool isValidInput = false;
        do {
            cout << "Ma khach san: ";
            cin >> strMaHotel;

            //kiểm tra xem chuỗi nhập vào có thể chuyển thành số nguyên không
            try {
                idHotel = stoi(strMaHotel);
                isValidInput = true;
            }
            catch (const std::exception&) {
                cout << "Ma khach san khong hop le. Vui long nhap lai." << endl;
            }
        } while (!isValidInput);

        cout << "Ten khach san: ";
        cin.ignore(); // xóa bộ đệm
        getline(cin, tenHotel);
        cout << "Dia chi khach san: ";
        getline(cin, diaChiHotel);
        cout << "Danh gia (tu 1-5 sao): ";
        cin >> ratingHotel;

        return Hotel(idHotel, tenHotel, diaChiHotel, ratingHotel);
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
      //  cout << "\n====== DANH SACH KHACH SAN HIEN CO ======" << endl;
        duyetGocGiua(root);
    }


    Hotel* timHotelBangMaSo(int idCanTim) {
        return searchBSTNode(root, idCanTim);
    }

    void deleteHotel(int idHotel) {
        deleteHotelFromBST(root, idHotel);
    }

    void suaThongTinKhachSan(int idCanTim, const string& tenMoi, const string& diaChiMoi, float ratingMoi) {
        BSTNode* current = root;

        while (current != nullptr) {
            if (idCanTim < current->hotel.getMaHotel()) {
                current = current->left;
            }
            else if (idCanTim > current->hotel.getMaHotel()) {
                current = current->right;
            }
            else {
                current->hotel = Hotel(idCanTim, tenMoi, diaChiMoi, ratingMoi);
                cout << "Da cap nhat thong tin cho khach san co ma " << idCanTim << endl;
                return;
            }
        }
        cout << "Khong tim thay khach san voi ma " << idCanTim << "." << endl;
    }

    static bool soSanhDiaChi(const Hotel& a, const Hotel& b) {
        return a.getDiaChiHotel() < b.getDiaChiHotel();
    }

    void swapHotel(Hotel& a, Hotel& b) {
        Hotel temp = a;
        a = b;
        b = temp;
    }

    //chia mảng theo pivot
    int partition(vector<Hotel>& dsHotel, int batDau, int ketThuc) {
        string pivot = dsHotel[ketThuc].getDiaChiHotel();
        int i = batDau - 1;

        for (int j = batDau; j <= ketThuc - 1; j++) {
            if (dsHotel[j].getDiaChiHotel() < pivot) {
                i++;
                swapHotel(dsHotel[i], dsHotel[j]);
            }
        }
        swapHotel(dsHotel[i + 1], dsHotel[ketThuc]);
        return i + 1;
    }

    // sắp xếp theo địa chỉ (quicksort)
    void quickSort(vector<Hotel>& dsHotel, int batDau, int ketThuc) {
        if (batDau < ketThuc) {
            int pi = partition(dsHotel, batDau, ketThuc);
            quickSort(dsHotel, batDau, pi - 1);
            quickSort(dsHotel, pi + 1, ketThuc);
        }
    }


    void getDSHotelVaoVector(BSTNode* node, vector<Hotel>& dsHotel) {
        if (node != nullptr) {
            getDSHotelVaoVector(node->left, dsHotel);
            dsHotel.push_back(node->hotel);
            getDSHotelVaoVector(node->right, dsHotel);
        }
    }

    void sapXepTheoDiaChi() {
        vector<Hotel> dsHotel;
        getDSHotelVaoVector(root, dsHotel);

        // sắp xếp địa chỉ sử dụng quickssrot 
        quickSort(dsHotel, 0, dsHotel.size() - 1);

        cout << "\n     ====== DANH SACH KHACH SAN SAU KHI SAP XEP THEO DIA CHI ======" << endl;
        for (const auto& hotel : dsHotel) {
            hotel.hienThiTTHotel();
        }
    }

    void ghiDSHotelVaoFile(const string& tenTepTin, BSTNode* node) {
        ofstream fileOut(tenTepTin); // open file
        if (!fileOut.is_open()) {
            cout << "Khong the mo tep tin de ghi!" << endl;
            return;
        }

        vector<Hotel> dsHotel;
        getDSHotelVaoVector(node, dsHotel);

        for (const auto& hotel : dsHotel) {
            fileOut << hotel.getMaHotel() << "," << hotel.getTenHotel() << "," << hotel.getDiaChiHotel() << "," << hotel.getRatingHotel() << endl;
        }

        fileOut.close();
    }
    
    void docDSHotelTuFile(const string& tenTepTin) {
        ifstream fileIn(tenTepTin); // open file
        if (!fileIn.is_open()) {
            cout << "Khong the mo tep tin de doc!" << endl;
            return;
        }

        int idHotel;
        string tenHotel, diaChiHotel, line;
        float ratingHotel;

        while (getline(fileIn, line)) {
            stringstream ss(line);
            string token;

            getline(ss, token, ',');
            idHotel = stoi(token);

            getline(ss, tenHotel, ',');
            getline(ss, diaChiHotel, ',');

            getline(ss, token);
            ratingHotel = stof(token);

            Hotel newHotel(idHotel, tenHotel, diaChiHotel, ratingHotel);
            addHotel(newHotel); // add hotel vao ds
        }

        fileIn.close();
    }


    ~HotelManager() {
        deleteBSTNodes(root);
    }

};




void khungLogin() {
    cout << "+-----------------------+" << endl;
    cout << "|      DANG NHAP        |" << endl;
    cout << "+-----------------------+" << endl;
}

void printLine(int n) {
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "_";
    }
    cout << endl;
}



int main() {
    HotelManager hotelManager;
    string tenHotel, diaChiHotel;
    float ratingHotel;
    Hotel* tempDiaChiHotel = nullptr;
    int luaChon;
    int maHotel;
    string tkAdmin = "admin";
    string mkAdmin = "admin"; //TK va MK
    string username, password;

    hotelManager.docDSHotelTuFile("dsHotel.txt");


    //do {
    //    system("cls");
    //    khungLogin();
    //
    //    cout << "Nhap ten dang nhap: ";
    //    cin >> username;
    //
    //    cout << "Nhap mat khau: ";
    //    cin >> password;
    //
    //    if (username == tkAdmin && password == mkAdmin) {
    //        system("cls");
    //        cout << "+------------------------+" << endl;
    //        cout << "|  DANG NHAP THANH CONG  |" << endl;
    //        cout << "+------------------------+" << endl;
    //        break;
    //    }
    //    else {
    //        system("cls");
    //        khungLogin();
    //        cout << "+-----------------------+" << endl;
    //        cout << "|  Dang nhap that bai.  |" << endl;
    //        cout << "+-----------------------+" << endl;
    //        cout << "Nhan Enter de dang nhap lai...";
    //        cin.ignore(); // Đọc kí tự Enter từ bàn phím
    //        cin.get();     // Đợi người dùng nhấn Enter
    //    }
    //} while (true);

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
            case 1: {
                system("cls");
                int soLuongKhachSan;
                cout << "Nhap so luong khach san muon them: ";
                cin >> soLuongKhachSan;

                for (int i = 0; i < soLuongKhachSan; ++i) {
                    cout << "\n====== THEM KHACH SAN MOI ======" << endl;
                    hotelManager.addHotel(hotelManager.nhapThongTinKhachSanMoi());
                }
                
                cout << "\nThem khach san thanh cong!" << endl;
                // dừng 2 giây trước khi xóa console
                this_thread::sleep_for(chrono::seconds(2));
                system("cls");
                break;
            }
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
            cout << "3. Sap xep theo dia diem khach san" << endl;
            cout << "0. Quay lai menu chinh" << endl;
            cout << "Nhap lua chon cua ban: ";
            cin >> viewLuaChon;

            switch (viewLuaChon) {
            case 1:
                system("cls");
                printLine(55);
                printLine(55);
                cout << "\n     ====== DANH SACH KHACH SAN HIEN CO ======" << endl;


                hotelManager.hienThiTatCaHotel();
                printLine(55);
                printLine(55);
                break;
            case 2:
                system("cls");
                cout << "Nhap ma khach san muon tim: ";
                cin >> maHotel;

                //timHotelBangMaSo của HotelManager thay vì timHotelBangMaSoBST
                tempDiaChiHotel = hotelManager.timHotelBangMaSo(maHotel);

                if (tempDiaChiHotel != nullptr) {
                    cout << "Thong tin khach san tim duoc:" << endl;
                    tempDiaChiHotel->hienThiTTHotel();
                }
                else {
                    cout << "Khong tim thay khach san voi ma " << maHotel << "." << endl;
                }
                break;
            case 3:
                system("cls");
                hotelManager.sapXepTheoDiaChi();
                break;

            case 0:
                break;
            default:
                cout << "Lua chon khong hop le." << endl;
            }
            break;
            
            break;

        case 0:
            hotelManager.ghiDSHotelVaoFile("dsHotel.txt", hotelManager.getRoot());
            cout << "Tam biet!";
            break;

        default:
            cout << "Lua chon khong hop le." << endl;
        }
    } while (luaChon != 0);

    return 0;
}
