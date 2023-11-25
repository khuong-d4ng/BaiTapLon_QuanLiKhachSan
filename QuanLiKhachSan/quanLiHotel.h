// quanLiHotel.h
#include <iostream>
#include <string>
using namespace std;

#ifndef QUANLIHOTEL_H
#define QUANLIHOTEL_H

#include "Hotel.h"




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

#endif
