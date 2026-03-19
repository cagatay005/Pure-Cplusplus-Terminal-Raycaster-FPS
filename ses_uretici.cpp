#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>

const int SAMPLE_RATE = 44100;

// Standart bir .wav dosyasının başlığını ve verisini yazar
void wav_olustur(const std::string& dosya_adi, const std::vector<short>& veriler) {
    std::ofstream f(dosya_adi, std::ios::binary);
    
    f << "RIFF";
    int chunk_size = 36 + veriler.size() * 2;
    f.write((char*)&chunk_size, 4);
    f << "WAVEfmt ";
    
    int subchunk1_size = 16; 
    short audio_format = 1; 
    short num_channels = 1;
    int sample_rate = SAMPLE_RATE;
    int byte_rate = SAMPLE_RATE * 2; 
    short block_align = 2; 
    short bits_per_sample = 16;
    
    f.write((char*)&subchunk1_size, 4); 
    f.write((char*)&audio_format, 2); 
    f.write((char*)&num_channels, 2);
    f.write((char*)&sample_rate, 4); 
    f.write((char*)&byte_rate, 4);
    f.write((char*)&block_align, 2); 
    f.write((char*)&bits_per_sample, 2);
    
    f << "data";
    int subchunk2_size = veriler.size() * 2;
    f.write((char*)&subchunk2_size, 4);
    
    // Ses verisini dosyaya yaz
    f.write((char*)veriler.data(), veriler.size() * 2);
    f.close();
}

int main() {
    std::vector<short> ates_sesi;
    int ates_uzunluk = SAMPLE_RATE / 2; 
    for (int i = 0; i < ates_uzunluk; i++) {
        float azalma = 1.0f - ((float)i / ates_uzunluk);
        short gurultu = (rand() % 32767 * 2 - 32767); 
        ates_sesi.push_back(gurultu * azalma * azalma);
    }
    wav_olustur("ates.wav", ates_sesi);
    
    std::vector<short> vurus_sesi;
    int vurus_uzunluk = SAMPLE_RATE / 5; 
    for (int i = 0; i < vurus_uzunluk; i++) {
        float azalma = 1.0f - ((float)i / vurus_uzunluk);
        short dalga = std::sin(i * 1000.0 * 2.0 * 3.14159 / SAMPLE_RATE) * 20000;
        vurus_sesi.push_back(dalga * azalma);
    }
    wav_olustur("vurus.wav", vurus_sesi);

    std::cout << "Kendi ozel ses dosyalarimiz basariyla uretildi (ates.wav ve vurus.wav)!\n";
    return 0;
}