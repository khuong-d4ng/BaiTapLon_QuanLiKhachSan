// Hotel.cpp
#include "Hotel.h"
#include <iostream>

Hotel::Hotel(int maHotel, const std::string& ten, float saoRating) : maHotel(maHotel), tenHotel(ten), ratingHotel(saoRating) {}

void Hotel::hienThiTTHotel() {
    std::cout << "Hotel Code: " << maHotel << std::endl;
    std::cout << "Hotel Name: " << tenHotel << std::endl;
    std::cout << "Star Rating: " << ratingHotel << " stars" << std::endl;
}

int Hotel::getMaHotel() const {
    return maHotel;
}
