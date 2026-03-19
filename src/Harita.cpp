#include "Harita.h"
#include "Sabitler.h"

Harita::Harita() {
    dunya_haritasi = 
        "################"
        "#..............#"
        "#.......########"
        "#..............#"
        "#......##......#"
        "#......##......#"
        "#..............#"
        "###............#"
        "##.............#"
        "#......####..###"
        "#......#.......#"
        "#......#.......#"
        "#..............#"
        "#......#########"
        "#..............#"
        "################";
}

bool Harita::duvar_mi(int x, int y) {
    if (x >= 0 && x < HARITA_GENISLIGI && y >= 0 && y < HARITA_YUKSEKLIGI) {
        return dunya_haritasi[y * HARITA_GENISLIGI + x] == '#';
    }
    return true;
}