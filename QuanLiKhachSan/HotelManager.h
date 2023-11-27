////HotelManager.h
//#include <iostream>
//#include <string>
//#include "Hotel.h"
//
//#ifndef QUANLIHOTEL_H
//#define QUANLIHOTEL_H
//
//class Node {
//public:
//    Hotel hotel;
//    Node* next;
//
//    Node(const Hotel& h) : hotel(h), next(nullptr) {}
//};
//
//class BSTNode {
//public:
//    Hotel hotel;
//    BSTNode* left;
//    BSTNode* right;
//
//    BSTNode(const Hotel& h) : hotel(h), left(nullptr), right(nullptr) {}
//};
//
//class HotelManager {
//private:
//    Node* head;
//    Node* tail;
//    BSTNode* root;
//
//    BSTNode* insertBSTNode(BSTNode* node, const Hotel& hotel);
//    Hotel* searchBSTNode(BSTNode* node, int code);
//    void deleteBSTNodes(BSTNode* node);
//
//public:
//    HotelManager();
//    ~HotelManager();
//
//    void addHotel(const Hotel& hotel);
//    void hienThiTatCaHotel();
//    Hotel* timHotelBangMaSo(int code);
//    Hotel* timHotelBangMaSoBST(int code);
//    void deleteHotel(int code);
//    void suaThongTinKhachSan(int code, const std::string& tenMoi, float ratingMoi);
//};
//
//#endif
