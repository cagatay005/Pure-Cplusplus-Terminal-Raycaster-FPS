#include "Terminal.h"
#include "Harita.h"
#include "Oyuncu.h"
#include "Motor.h"
#include "Dusman.h"
#include "Ses.h"
#include <vector>
#include <unistd.h>
#include <cmath>

int main() {
    TerminalArayuzu terminal;
    Harita harita;
    Oyuncu oyuncu(8.0f, 8.0f, 0.0f);
    Motor motor;
    
    std::vector<Dusman> dusmanlar;
    dusmanlar.push_back(Dusman(12.0f, 12.0f)); 
    dusmanlar.push_back(Dusman(3.0f, 3.0f));   

    bool calisiyor = true;

    while (calisiyor) {
        bool ates_ediyor = false;
        char tus = terminal.tus_oku();

        if (tus == 'q') {
            calisiyor = false;
        } else if (tus == 'w') {
            oyuncu.hareket_et(0.3f, 0.0f, harita);
        } else if (tus == 's') {
            oyuncu.hareket_et(-0.3f, 0.0f, harita);
        } else if (tus == 'a') {
            oyuncu.hareket_et(0.0f, -0.10f, harita);
        } else if (tus == 'd') {
            oyuncu.hareket_et(0.0f, 0.10f, harita);
        } else if (tus == ' ') {
            if (oyuncu.cephane > 0) { 
                ates_ediyor = true;
                oyuncu.cephane--;     
                Ses::ates_sesi_cal();
                
                for (auto& d : dusmanlar) {
                    if (!d.hayatta_mi) continue;
                    
                    float d_x = d.x - oyuncu.x;
                    float d_y = d.y - oyuncu.y;
                    float d_acisi = std::atan2(d_y, d_x) - oyuncu.aci;
                    
                    while (d_acisi < -PI) d_acisi += 2 * PI;
                    while (d_acisi > PI) d_acisi -= 2 * PI;

                    if (std::abs(d_acisi) < 0.1f) {
                        d.hayatta_mi = false;
                        oyuncu.skor += 100; 
                        Ses::dusman_vuruldu_sesi_cal();
                    }
                }
            }
        }

        motor.sahneyi_hazirla(oyuncu, harita);
        motor.dusmanlari_ciz(oyuncu, dusmanlar);
        motor.arayuz_ekle(ates_ediyor, oyuncu, harita, dusmanlar);
        motor.ekrana_bas();

        usleep(30000);
    }

    return 0;
}