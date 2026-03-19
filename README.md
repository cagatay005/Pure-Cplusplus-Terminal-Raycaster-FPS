# Saf C++ Terminal FPS Motoru (Pure C++ Terminal FPS Engine)

Düşük seviyeli algoritmaların ve C++ verimliliğinin yüksek performanslı bir gösterimi olan bu proje; herhangi bir harici kütüphane (OpenGL, SDL, SFML vb.) kullanmadan, tamamen sıfırdan inşa edilmiştir.

---

## TANITIM

Bu motor, klasik Ray Casting algoritmasını kullanarak 2D harita verilerini terminal üzerinde 3D perspektife dönüştürür. Görselleştirme tamamen ASCII karakterleri ve ANSI renk kodları ile Linux terminali üzerinde gerçekleştirilir.

### Teknik Özellikler ve Geliştirme Detayları
* **Çekirdek Render Motoru:** Wolfenstein 3D tarzı, 2D harita verisini 3D perspektife dönüştüren Ray Casting algoritması.
* **Modüler Mimari:** Proje; `Motor`, `Oyuncu`, `Harita`, `Terminal`, `Dusman` ve `Ses` sınıfları ile profesyonel bir yapıya sahiptir.
* **Sprite Sistemi & Z-Buffer:** Düşmanların (yeşil @ karakterleri) derinlik kontrolü yapılarak duvarların arkasında kalması sağlandı.
* **Matematiksel Ses Sentezi:** Dışarıdan ses dosyası yüklemek yerine; sinüs dalgaları ve beyaz gürültü kullanılarak silah patlaması ve vuruş sesleri kodla üretildi.
* **Dinamik Lokal Radar:** Oyuncuyu merkeze alan, hareketle birlikte kayan 9x9 boyutunda modern bir mini harita sistemi eklendi.
* **Varlık Fiziği ve Hasar:** Düşmanların içinden geçmeyi engelleyen çarpışma fiziği ve oyuncuya temas ettiklerinde can azaltan hasar sistemi kuruldu.
* **HUD ve Arayüz:** Skor, mermi ve can durumunu gösteren, can azaldığında renk değiştiren dinamik bir bilgi paneli eklendi.

### Oyun İçi Görünüm
![Oyun İçi Görüntü]<img src="game_preview.gif" width="800">

### Kurulum ve Çalıştırma
1.  **Sesleri Üret:** `g++ ses_uretici.cpp -o ses_uretici && ./ses_uretici`
2.  **Dosyaları Düzenle:** `mkdir -p sesler && mv *.wav sesler/`
3.  **Derle ve Başlat:** `make && ./fps_oyun`

### Kontroller
* **W / S:** İleri - Geri Hareket
* **A / D:** Sağa - Sola Dönüş
* **Space (Boşluk):** Ateş Etme
* **Q:** Oyundan Çıkış

---

## DESCRIPTION

A high-performance demonstration of low-level algorithms and C++ efficiency. This engine translates 2D map data into an immersive 3D perspective rendered entirely through ASCII characters and ANSI color sequences on the Linux terminal.

### Technical Features & Development Details
* **Core Render Engine:** Wolfenstein 3D style Ray Casting algorithm for 3D projection.
* **Modular Architecture:** Structured with professional classes including `Motor`, `Oyuncu`, `Harita`, `Terminal`, `Dusman`, and `Ses`.
* **Sprite System & Z-Buffer:** Implemented a depth buffer to ensure enemies (green @ symbols) are correctly occluded by walls.
* **Procedural Audio Synthesis:** Instead of external assets, gunshots and hit sounds were mathematically synthesized using sine waves and white noise.
* **Dynamic Local Radar:** A modern 9x9 localized mini-map that follows the player in real-time.
* **Entity Physics & Damage:** Per-axis collision physics to prevent ghosting through enemies and a damage system that reduces HP upon contact.
* **HUD & Interface:** Real-time display for Health, Score, and Ammo with dynamic color alerts for low health.

### Gameplay Preview
![Gameplay Preview]<img src="game_preview.gif" width="800">

### Installation & Execution
1.  **Synthesize Audio:** `g++ ses_uretici.cpp -o ses_uretici && ./ses_uretici`
2.  **Organize Assets:** `mkdir -p sesler && mv *.wav sesler/`
3.  **Compile & Run:** `make && ./fps_oyun`

### Controls
* **W / S:** Move Forward / Backward
* **A / D:** Look Left / Right (Rotation)
* **Space:** Fire Weapon
* **Q:** Quit Game

---
**Geliştirici / Developer:** Mustafa Cagatay OZDEM
