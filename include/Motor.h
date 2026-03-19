#ifndef MOTOR_H
#define MOTOR_H

#include <string>
#include <vector>
#include "Sabitler.h"
#include "Oyuncu.h"
#include "Harita.h"
#include "Dusman.h"

class Motor {
private:
    std::string ekran_matrisi[EKRAN_YUKSEKLIGI][EKRAN_GENISLIGI];
    float derinlik_tamponu[EKRAN_GENISLIGI]; 

public:
    void sahneyi_hazirla(const Oyuncu& oyuncu, Harita& harita); 
    void dusmanlari_ciz(const Oyuncu& oyuncu, std::vector<Dusman>& dusmanlar); 
    void arayuz_ekle(bool ates_ediyor, const Oyuncu& oyuncu, Harita& harita, const std::vector<Dusman>& dusmanlar); // Fonksiyon imzası güncellendi
    void ekrana_bas(); 
};

#endif