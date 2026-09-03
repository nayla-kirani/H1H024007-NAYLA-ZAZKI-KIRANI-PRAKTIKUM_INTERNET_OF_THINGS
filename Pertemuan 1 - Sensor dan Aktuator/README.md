# Pertemuan 1 - Sensor dan Aktuator

## Praktikum Internet of Things

Repository ini berisi dokumentasi dan program hasil praktikum Internet of Things pada modul **Sensor dan Aktuator** menggunakan mikrokontroler ESP32.

Pada praktikum ini dilakukan implementasi pembacaan data sensor DHT22 dan pengendalian aktuator berdasarkan kondisi suhu yang terbaca.

Percobaan yang dilakukan:

1. Percobaan 1A - Akuisisi Data Sensor DHT22
2. Percobaan 2A - Kendali Aktuator Relay Berdasarkan Suhu


# Percobaan 1A
## Akuisisi Data Sensor DHT22


## Tujuan

Percobaan ini bertujuan untuk memahami proses pembacaan data suhu dan kelembaban menggunakan sensor DHT22 yang terhubung dengan ESP32. Data hasil pembacaan sensor kemudian ditampilkan melalui Serial Monitor.


## Alat dan Bahan

| No | Komponen | Jumlah |
|---|---|---|
| 1 | ESP32 DevKit | 1 |
| 2 | Sensor DHT22 | 1 |
| 3 | Breadboard | 1 |
| 4 | Kabel jumper | Secukupnya |
| 5 | Laptop dengan Arduino IDE | 1 |


## Rangkaian Percobaan 1A

Konfigurasi pin yang digunakan:

| DHT22 | ESP32 |
|---|---|
| VCC | 3.3V |
| DATA | GPIO 4 |
| GND | GND |


## Library yang Digunakan

Library yang digunakan:

- DHT sensor library
- ESP32 Board Package


## Penjelasan Program

Program menggunakan library DHT agar ESP32 dapat berkomunikasi dengan sensor DHT22.

Pin DATA sensor dihubungkan dengan GPIO 4 pada ESP32.


### Fungsi setup()

Fungsi setup() digunakan untuk melakukan konfigurasi awal sebelum program dijalankan.

Pada bagian ini dilakukan:

- Mengaktifkan komunikasi Serial Monitor dengan baud rate 115200.
- Melakukan inisialisasi sensor DHT22.


### Fungsi loop()

Fungsi loop() berjalan secara berulang untuk melakukan pembacaan data sensor.

Tahapan proses:

1. Membaca nilai kelembaban menggunakan fungsi readHumidity().
2. Membaca nilai suhu menggunakan fungsi readTemperature().
3. Mengecek validitas data sensor.
4. Menampilkan hasil pembacaan pada Serial Monitor.


### Fungsi isnan()

Fungsi isnan() digunakan untuk mengecek apakah data hasil pembacaan sensor valid atau tidak.

Jika sensor gagal membaca data, program akan memberikan informasi bahwa pembacaan sensor mengalami kegagalan.


## Hasil Pengamatan

Berdasarkan percobaan yang dilakukan, sensor DHT22 berhasil membaca nilai suhu dan kelembaban lingkungan.

Data hasil pembacaan ditampilkan melalui Serial Monitor dengan interval waktu tertentu.


Dokumentasi hasil:

Serial Monitor Percobaan 1A:
https://drive.google.com/drive/folders/1cuzSr7aecO1EMeMUkU6ifeoblSAAA2ZQ?usp=sharing


# Percobaan 2A
## Kendali Aktuator Relay Berdasarkan Suhu


## Tujuan

Percobaan ini bertujuan untuk membuat sistem kendali otomatis menggunakan ESP32 dengan memanfaatkan data suhu dari sensor DHT22 sebagai input untuk mengontrol relay sebagai aktuator.


## Rangkaian Percobaan 2A

Konfigurasi pin yang digunakan:

| Komponen | ESP32 |
|---|---|
| DATA DHT22 | GPIO 4 |
| Relay IN | GPIO 26 |
| Relay VCC | VIN 5V |
| Relay GND | GND |


## Prinsip Kerja Sistem

Sistem membaca nilai suhu dari sensor DHT22 kemudian membandingkan nilai tersebut dengan batas suhu yang telah ditentukan.

Nilai batas tersebut disebut sebagai threshold.


Logika sistem:

```
Jika suhu > 30°C
        |
        ↓
Relay ON


Jika suhu <= 30°C
        |
        ↓
Relay OFF
```


## Penjelasan Program

Pada program digunakan variabel:

```cpp
const float suhuThreshold = 30.0;
```

Variabel tersebut digunakan sebagai nilai batas suhu untuk menentukan kondisi relay.


## Percabangan Program

Program menggunakan kondisi:

```cpp
if (suhu > suhuThreshold)
```

Jika kondisi bernilai benar:

- GPIO relay diberi nilai HIGH.
- Relay aktif.
- Aktuator berada pada kondisi ON.


Jika kondisi bernilai salah:

- GPIO relay diberi nilai LOW.
- Relay mati.
- Aktuator berada pada kondisi OFF.


## Hasil Pengamatan

Berdasarkan hasil percobaan, sistem dapat melakukan pengendalian relay berdasarkan perubahan suhu yang terbaca oleh sensor DHT22.

Ketika suhu melebihi nilai threshold, relay akan aktif. Sedangkan ketika suhu berada di bawah threshold, relay akan mati.


Dokumentasi hasil:

 Serial Monitor Percobaan 2A:
 https://drive.google.com/drive/folders/1cuzSr7aecO1EMeMUkU6ifeoblSAAA2ZQ?usp=sharing
 



# Jawaban Pertanyaan Praktikum


## 1. Apa fungsi isnan() pada program?

Fungsi isnan() digunakan untuk melakukan pengecekan apakah hasil pembacaan sensor merupakan data yang valid atau tidak.

Jika data tidak valid, program akan menampilkan pesan bahwa sensor gagal membaca data.


## 2. Mengapa diberikan delay pada program?

Delay digunakan untuk memberikan jeda waktu antar pembacaan sensor sehingga data yang ditampilkan lebih stabil dan pembacaan sensor tidak dilakukan terlalu cepat.


## 3. Apa fungsi threshold pada sistem?

Threshold digunakan sebagai nilai batas yang menjadi acuan mikrokontroler dalam mengambil keputusan.

Pada percobaan ini threshold digunakan untuk menentukan kapan relay aktif atau tidak aktif.


## 4. Perbedaan threshold dan hysteresis

Threshold hanya menggunakan satu nilai batas untuk menentukan perubahan kondisi.

Sedangkan hysteresis menggunakan dua batas nilai sehingga perubahan kondisi aktuator menjadi lebih stabil dan mengurangi perubahan ON/OFF yang terlalu sering.


---

# Dokumentasi Praktikum

Dokumentasi yang dilampirkan:

- Diagram rangkaian Percobaan 1A
- Diagram rangkaian Percobaan 2A
- Foto proses perangkaian
- Screenshot Serial Monitor
- Dokumentasi pengujian aktuator


## Struktur Folder

Pertemuan 1 - Sensor dan Aktuator

│
├── code
│   ├── Percobaan_1A_DHT22_Akuisisi_Data.ino
│   └── Percobaan_2A_DHT22_Relay_Control.ino
│
├── dokumentasi
│   ├── rangkaian_percobaan_1A.png
│   ├── rangkaian_percobaan_2A.png
│   ├── foto_praktikum.jpg
│   └── serial_monitor.png
│
└── README.md



# Kesimpulan

Pada praktikum ini telah dilakukan implementasi sistem IoT menggunakan ESP32, sensor DHT22, dan relay sebagai aktuator.

ESP32 berhasil digunakan untuk membaca data suhu dan kelembaban dari sensor DHT22. Data suhu tersebut kemudian digunakan sebagai dasar pengambilan keputusan untuk mengontrol relay berdasarkan nilai threshold yang telah ditentukan.
