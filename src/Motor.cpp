#include "Motor.h"
#include <iostream>
#include <cmath>

void Motor::sahneyi_hazirla(const Oyuncu& oyuncu, Harita& harita) {
    for (int x = 0; x < EKRAN_GENISLIGI; x++) {
        float isin_acisi = (oyuncu.aci - oyuncu.gorus_alani / 2.0f) + ((float)x / (float)EKRAN_GENISLIGI) * oyuncu.gorus_alani;
        float isin_yonu_x = std::cos(isin_acisi);
        float isin_yonu_y = std::sin(isin_acisi);
        float uzaklik_x = std::abs(1.0f / isin_yonu_x);
        float uzaklik_y = std::abs(1.0f / isin_yonu_y);
        int harita_x = (int)oyuncu.x;
        int harita_y = (int)oyuncu.y;
        float yan_uzaklik_x, yan_uzaklik_y;
        int adim_x, adim_y;

        if (isin_yonu_x < 0) {
            adim_x = -1;
            yan_uzaklik_x = (oyuncu.x - harita_x) * uzaklik_x;
        } else {
            adim_x = 1;
            yan_uzaklik_x = (harita_x + 1.0f - oyuncu.x) * uzaklik_x;
        }

        if (isin_yonu_y < 0) {
            adim_y = -1;
            yan_uzaklik_y = (oyuncu.y - harita_y) * uzaklik_y;
        } else {
            adim_y = 1;
            yan_uzaklik_y = (harita_y + 1.0f - oyuncu.y) * uzaklik_y;
        }

        bool carpti = false;
        bool dikey = false;

        while (!carpti) {
            if (yan_uzaklik_x < yan_uzaklik_y) {
                yan_uzaklik_x += uzaklik_x;
                harita_x += adim_x;
                dikey = false;
            } else {
                yan_uzaklik_y += uzaklik_y;
                harita_y += adim_y;
                dikey = true;
            }
            if (harita.duvar_mi(harita_x, harita_y)) {
                carpti = true;
            }
        }

        float gercek_uzaklik;
        if (!dikey) {
            gercek_uzaklik = (harita_x - oyuncu.x + (1 - adim_x) / 2.0f) / isin_yonu_x;
        } else {
            gercek_uzaklik = (harita_y - oyuncu.y + (1 - adim_y) / 2.0f) / isin_yonu_y;
        }

        gercek_uzaklik *= std::cos(isin_acisi - oyuncu.aci);
        if (gercek_uzaklik <= 0.0f) gercek_uzaklik = 0.001f;

        derinlik_tamponu[x] = gercek_uzaklik;

        int tavan = (int)(EKRAN_YUKSEKLIGI / 2.0f - EKRAN_YUKSEKLIGI / gercek_uzaklik);
        int zemin = EKRAN_YUKSEKLIGI - tavan;

        float parlaklik = 1.0f / (1.0f + gercek_uzaklik * 0.15f);
        if (dikey) parlaklik *= 0.6f;

        int r = (int)(255 * parlaklik);
        int g = (int)(150 * parlaklik);
        int b = (int)(50 * parlaklik);
        std::string duvar_renk = "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m\u2588";

        for (int y = 0; y < EKRAN_YUKSEKLIGI; y++) {
            if (y <= tavan) {
                ekran_matrisi[y][x] = "\x1b[0m ";
            } else if (y > tavan && y <= zemin) {
                ekran_matrisi[y][x] = duvar_renk;
            } else {
                float zemin_degeri = 1.0f - ((float)y - EKRAN_YUKSEKLIGI / 2.0f) / ((float)EKRAN_YUKSEKLIGI / 2.0f);
                int z_r = (int)(60 * (1.0f - zemin_degeri));
                int z_g = (int)(60 * (1.0f - zemin_degeri));
                int z_b = (int)(60 * (1.0f - zemin_degeri));
                ekran_matrisi[y][x] = "\x1b[38;2;" + std::to_string(z_r) + ";" + std::to_string(z_g) + ";" + std::to_string(z_b) + "m.";
            }
        }
    }
}

void Motor::arayuz_ekle(bool ates_ediyor, const Oyuncu& oyuncu, Harita& harita, const std::vector<Dusman>& dusmanlar) {
    int orta_x = EKRAN_GENISLIGI / 2;
    int orta_y = EKRAN_YUKSEKLIGI / 2;
    
    ekran_matrisi[orta_y][orta_x] = "\x1b[31m+\x1b[0m"; 
    std::string silah_rengi = ates_ediyor ? "\x1b[33m" : "\x1b[37m";
    ekran_matrisi[EKRAN_YUKSEKLIGI - 2][orta_x] = silah_rengi + "H\x1b[0m"; 
    ekran_matrisi[EKRAN_YUKSEKLIGI - 1][orta_x - 1] = silah_rengi + "/M\\\x1b[0m";

    std::string hud = " SKOR: " + std::to_string(oyuncu.skor) + " | MERMI: " + std::to_string(oyuncu.cephane) + " ";
    for (size_t i = 0; i < hud.length() && i < EKRAN_GENISLIGI; i++) {
        ekran_matrisi[0][i] = "\x1b[44;37m" + std::string(1, hud[i]) + "\x1b[0m"; 
    }

    int radar_baslangic_x = EKRAN_GENISLIGI - HARITA_GENISLIGI - 2;
    int radar_baslangic_y = 1;

    for (int y = 0; y < HARITA_YUKSEKLIGI; y++) {
        for (int x = 0; x < HARITA_GENISLIGI; x++) {
            std::string hucre = " ";
            
            if (harita.duvar_mi(x, y)) {
                hucre = "\x1b[47m \x1b[0m";
            } else {
                bool uzerinde_nesne_var = false;
                
                if ((int)oyuncu.x == x && (int)oyuncu.y == y) {
                    hucre = "\x1b[1;36mP\x1b[0m";
                    uzerinde_nesne_var = true;
                } else {
                    for (const auto& d : dusmanlar) {
                        if (d.hayatta_mi && (int)d.x == x && (int)d.y == y) {
                            hucre = "\x1b[1;31m@\x1b[0m";
                            uzerinde_nesne_var = true;
                            break;
                        }
                    }
                }

                if (!uzerinde_nesne_var) {
                    hucre = "\x1b[1;30m.\x1b[0m";
                }
            }
            ekran_matrisi[radar_baslangic_y + y][radar_baslangic_x + x] = hucre;
        }
    }
}

void Motor::ekrana_bas() {
    std::string cikti = "\x1b[H";
    for (int y = 0; y < EKRAN_YUKSEKLIGI; y++) {
        for (int x = 0; x < EKRAN_GENISLIGI; x++) {
            cikti += ekran_matrisi[y][x];
        }
        cikti += "\x1b[0m\n";
    }
    std::cout << cikti << std::flush;
}

void Motor::dusmanlari_ciz(const Oyuncu& oyuncu, std::vector<Dusman>& dusmanlar) {
    for (auto& d : dusmanlar) {
        if (!d.hayatta_mi) continue;

        float d_x = d.x - oyuncu.x;
        float d_y = d.y - oyuncu.y;
        d.oyuncuya_uzaklik = std::sqrt(d_x * d_x + d_y * d_y);

        float d_acisi = std::atan2(d_y, d_x) - oyuncu.aci;
        if (d_acisi < -PI) d_acisi += 2 * PI;
        if (d_acisi > PI) d_acisi -= 2 * PI;

        if (std::abs(d_acisi) < oyuncu.gorus_alani / 1.5f) {
            float d_boyutu = (float)EKRAN_YUKSEKLIGI / d.oyuncuya_uzaklik;
            int orta_ekran_x = (int)((0.5f * (d_acisi / (oyuncu.gorus_alani / 2.0f)) + 0.5f) * EKRAN_GENISLIGI);

            for (int dx = -1; dx <= 1; dx++) { // Düşmanı 3 karakter genişliğinde çiz.
                int cizim_x = orta_ekran_x + dx;
                if (cizim_x >= 0 && cizim_x < EKRAN_GENISLIGI && d.oyuncuya_uzaklik < derinlik_tamponu[cizim_x]) {
                    int tavan = (EKRAN_YUKSEKLIGI / 2) - (d_boyutu / 2);
                    int zemin = (EKRAN_YUKSEKLIGI / 2) + (d_boyutu / 2);
                    
                    for (int y = std::max(0, tavan); y < std::min(EKRAN_YUKSEKLIGI, zemin); y++) {
                        ekran_matrisi[y][cizim_x] = "\x1b[32m@\x1b[0m"; // Düşman simgesi: Yeşil @
                    }
                }
            }
        }
    }
}