#ifndef OYUNCU_H
#define OYUNCU_H

#include "Harita.h"

class Oyuncu {
public:
    float x;
    float y;
    float aci;
    float gorus_alani;
    int cephane;
    int skor;    

    Oyuncu(float baslangic_x, float baslangic_y, float baslangic_acisi);
    void hareket_et(float ileri_hiz, float donus_hizi, Harita& harita);
};

#endif