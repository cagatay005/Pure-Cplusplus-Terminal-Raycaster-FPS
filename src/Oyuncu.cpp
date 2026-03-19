#include "Oyuncu.h"
#include "Sabitler.h"
#include <cmath>

Oyuncu::Oyuncu(float baslangic_x, float baslangic_y, float baslangic_acisi) {
    x = baslangic_x;
    y = baslangic_y;
    aci = baslangic_acisi;
    gorus_alani = PI / 3.0f;
    cephane = 15;
    skor = 0;     
}

void Oyuncu::hareket_et(float ileri_hiz, float donus_hizi, Harita& harita) {
    aci += donus_hizi;

    float yeni_x = x + std::cos(aci) * ileri_hiz;
    float yeni_y = y + std::sin(aci) * ileri_hiz;

    if (!harita.duvar_mi((int)yeni_x, (int)y)) {
        x = yeni_x;
    }
    if (!harita.duvar_mi((int)x, (int)yeni_y)) {
        y = yeni_y;
    }
}