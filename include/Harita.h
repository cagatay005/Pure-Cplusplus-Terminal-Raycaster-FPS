#ifndef HARITA_H
#define HARITA_H

#include <string>

class Harita {
public:
    std::string dunya_haritasi;

    Harita(); // Harita verisini başlatır.
    bool duvar_mi(int x, int y); // Koordinatın duvar olup olmadığını döndürür.
};

#endif