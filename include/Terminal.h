#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

class TerminalArayuzu {
private:
    struct termios eski_ayarlar, yeni_ayarlar;

public:
    TerminalArayuzu(); // Terminal ayarlarını yapılandırır ve imleci gizler.
    ~TerminalArayuzu(); // Terminal ayarlarını eski haline getirir ve imleci gösterir.
    bool tus_basildi_mi(); // Klavyeden anlık bir tuşa basılıp basılmadığını kontrol eder.
    char tus_oku(); // Basılan tuşun karakter değerini döndürür.
};

#endif