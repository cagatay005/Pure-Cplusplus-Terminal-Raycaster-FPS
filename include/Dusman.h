#ifndef DUSMAN_H
#define DUSMAN_H

class Dusman {
public:
    float x;
    float y;
    bool hayatta_mi;
    float oyuncuya_uzaklik;

    Dusman(float baslangic_x, float baslangic_y); // Belirlenen koordinatlarda bir düşman oluşturur.
};

#endif