#include "Terminal.h"
#include <unistd.h>
#include <sys/select.h>
#include <iostream>

TerminalArayuzu::TerminalArayuzu() {
    tcgetattr(STDIN_FILENO, &eski_ayarlar);
    yeni_ayarlar = eski_ayarlar;
    yeni_ayarlar.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &yeni_ayarlar);
    std::cout << "\x1b[2J\x1b[?25l";
}

TerminalArayuzu::~TerminalArayuzu() {
    tcsetattr(STDIN_FILENO, TCSANOW, &eski_ayarlar);
    std::cout << "\x1b[?25h";
}

bool TerminalArayuzu::tus_basildi_mi() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

char TerminalArayuzu::tus_oku() {
    char c = 0;
    if (tus_basildi_mi()) {
        if (read(STDIN_FILENO, &c, 1) < 0) return 0;
    }
    return c;
}