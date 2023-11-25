//HotelManager.cpp
#include "HotelManager.h"

using namespace std;

HotelManager::HotelManager() : head(nullptr), tail(nullptr), root(nullptr) {}

HotelManager::~HotelManager() {
    deleteBSTNodes(root);

    Node* temp = head;
    while (temp != nullptr) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
}

//hỗ trợ thêm node vào BST
BSTNode* HotelManager::insertBSTNode(BSTNode* node, const Hotel& hotel) {
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

Hotel* HotelManager::searchBSTNode(BSTNode* node, int code) {
    //hỗ trợ tìm kiếm node trong BST
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

void HotelManager::deleteBSTNodes(BSTNode* node) {
    //giải phóng bộ nhớ của BST
        if (node != nullptr) {
            deleteBSTNodes(node->left);
            deleteBSTNodes(node->right);
            delete node;
        }
}

void HotelManager::addHotel(const Hotel& hotel) {   
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

void HotelManager::hienThiTatCaHotel() {
        Node* temp = head;
        while (temp != nullptr) {
            temp->hotel.hienThiTTHotel();
            cout << "--------------------" << endl;
            temp = temp->next;
        }
    
}

Hotel* HotelManager::timHotelBangMaSo(int code) {
    // tim kiem khach san dua tren makhachsan
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->hotel.getMaHotel() == code) {
                return &(temp->hotel);
            }
            temp = temp->next;
        }
        return nullptr;
}

Hotel* HotelManager::timHotelBangMaSoBST(int code) {
    return searchBSTNode(root, code);
}

void HotelManager::deleteHotel(int code) {
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

void HotelManager::suaThongTinKhachSan(int code, const std::string& tenMoi, float ratingMoi) {
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