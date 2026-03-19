#include "Ses.h"
#include <cstdlib>

void Ses::ates_sesi_cal() {
    int sonuc = std::system("aplay sesler/ates.wav -q 2>/dev/null &");
    (void)sonuc;
}

void Ses::dusman_vuruldu_sesi_cal() {
    int sonuc = std::system("aplay sesler/vurus.wav -q 2>/dev/null &");
    (void)sonuc;
}