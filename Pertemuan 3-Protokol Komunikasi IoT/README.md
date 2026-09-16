# Modul 3 — Protokol Komunikasi IoT

> [!IMPORTANT]
> Pada praktikum ini dilakukan pengujian komunikasi perangkat IoT melalui jaringan WiFi dengan dua protokol, yaitu **HTTP** dan **MQTT**. Data sensor dikemas dalam format **JSON**, kemudian dikirim menuju endpoint HTTP dan broker MQTT.

## Daftar Isi

- [Library yang Digunakan](#library-yang-digunakan)
- [Percobaan 3A — HTTP](#percobaan-3a--http)
- [Percobaan 3B — MQTT](#percobaan-3b--mqtt)
- [Jawaban Pertanyaan Praktikum](#jawaban-pertanyaan-praktikum)
- [Dokumentasi](#dokumentasi)

## Library yang Digunakan

Beberapa library yang diperlukan pada praktikum ini antara lain:

- `ESP8266WiFi.h` — mengatur koneksi ESP8266 ke jaringan WiFi.
- `ESP8266HTTPClient.h` — menangani komunikasi HTTP/HTTPS.
- `WiFiClientSecure.h` — menyediakan koneksi berbasis TLS/HTTPS.
- `PubSubClient.h` — digunakan untuk koneksi dan komunikasi MQTT.
- `ArduinoJson.h` — membantu membuat serta melakukan serialisasi data JSON.

## Percobaan 3A — HTTP

**Source:** `Code/Percobaan3A.cpp`

Program ini menghubungkan ESP8266 ke WiFi, membuat payload JSON yang berisi data suhu dan kelembaban, lalu mengirimkannya menggunakan metode HTTP POST ke endpoint yang telah ditentukan.

```cpp
#include <ESP8266WiFi.h> // Library untuk koneksi WiFi
#include <ESP8266HTTPClient.h> // Library untuk HTTP
#include <WiFiClientSecure.h> // Library untuk koneksi HTTPS
#include <ArduinoJson.h> // Library pengolahan JSON

const char *ssid = "wifi-anda"; // SSID WiFi
const char *password = "password"; // Password WiFi
const char *serverUrl = "https://httpbin.org/post"; // URL endpoint

void setup() {
    Serial.begin(115200); // Memulai komunikasi serial

    WiFi.begin(ssid, password); // Memulai koneksi WiFi

    Serial.print("Menghubungkan ke WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("WiFi berhasil terhubung!");
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http; // Membuat objek HTTP
        WiFiClientSecure client; // Membuat client HTTPS
        client.setInsecure(); // Menonaktifkan verifikasi sertifikat

        http.begin(client, serverUrl); // Menentukan endpoint
        http.addHeader("Content-Type", "application/json"); // Header JSON

        JsonDocument doc; // Menyiapkan dokumen JSON
        doc["suhu"] = 28.5; // Data suhu
        doc["kelembaban"] = 65.0; // Data kelembaban

        String requestBody; // Menampung JSON dalam bentuk string
        serializeJson(doc, requestBody); // Mengubah JSON menjadi string

        Serial.print("Mengirim data: ");
        Serial.println(requestBody);

        int httpResponseCode = http.POST(requestBody); // Mengirim POST

        if (httpResponseCode > 0) {
            Serial.print("Kode Respon HTTP: ");
            Serial.println(httpResponseCode);
            Serial.println("Isi Respon:");
            Serial.println(http.getString());
        } else {
            Serial.print("Pengiriman gagal, kode error: ");
            Serial.println(httpResponseCode);
        }

        http.end(); // Mengakhiri koneksi HTTP
    }

    delay(10000); // Interval pengiriman 10 detik
}
```

## Percobaan 3B — MQTT

**Source:** `Code/Percobaan3B.cpp`

Percobaan kedua menggunakan MQTT. ESP8266 terlebih dahulu terhubung ke WiFi, kemudian melakukan koneksi ke broker MQTT melalui port yang telah disediakan. Data suhu dan kelembaban dikirim dalam bentuk JSON melalui topic `test/sensor`.

```cpp
#include <ESP8266WiFi.h> // Library WiFi
#include <WiFiClientSecure.h> // Library koneksi TLS
#include <PubSubClient.h> // Library MQTT
#include <ArduinoJson.h> // Library JSON

const char *ssid = "nama-wifi";
const char *password = "password";

const char *mqttServer = "mqtt.server";
const int mqttPort = 8883;

const char *mqttUsername = "test";
const char *mqttPassword = "12345678";

const char *mqttTopic = "test/sensor";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void hubungkanWiFi()
{
    WiFi.begin(ssid, password);

    Serial.print("Menghubungkan ke WiFi");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi berhasil terhubung!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

void hubungkanMQTT()
{
    while (!client.connected())
    {
        Serial.println();
        Serial.print("Menghubungkan ke broker MQTT...");

        String clientId =
            "ESP8266Client-" +
            String(ESP.getChipId(), HEX);

        Serial.print(" Client ID: ");
        Serial.println(clientId);

        if (client.connect(
                clientId.c_str(),
                mqttUsername,
                mqttPassword))
        {
            Serial.println("MQTT berhasil terhubung!");

            Serial.print("Broker : ");
            Serial.println(mqttServer);

            Serial.print("Port   : ");
            Serial.println(mqttPort);

            Serial.println("================================");
        }
        else
        {
            Serial.print("MQTT gagal, rc=");
            Serial.println(client.state());

            Serial.println("Mencoba lagi dalam 2 detik...");

            delay(2000);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("================================");
    Serial.println(" ESP8266 MQTT - HiveMQ Cloud");
    Serial.println("================================");

    hubungkanWiFi();

    espClient.setInsecure();

    client.setServer(
        mqttServer,
        mqttPort);

    hubungkanMQTT();
}

void loop()
{
    if (!client.connected())
    {
        Serial.println();
        Serial.println("MQTT terputus!");

        hubungkanMQTT();
    }

    client.loop();

    JsonDocument doc;

    doc["suhu"] = 28.5;
    doc["kelembaban"] = 65.0;

    char buffer[128];

    serializeJson(doc, buffer);

    bool berhasil =
        client.publish(
            mqttTopic,
            buffer);

    if (berhasil)
    {
        Serial.println();
        Serial.println("Data berhasil dikirim!");

        Serial.print("Topic   : ");
        Serial.println(mqttTopic);

        Serial.print("Payload : ");
        Serial.println(buffer);
    }
    else
    {
        Serial.println();
        Serial.println("Gagal mengirim data!");
    }

    delay(5000);
}
```

## Jawaban Pertanyaan Praktikum

### Modifikasi Percobaan 3A

**File:** `Code/Percobaan3A-Answer.cpp`

Modifikasi dilakukan dengan menambahkan informasi **uptime**, yaitu lama waktu perangkat telah berjalan sejak dinyalakan. Nilainya diperoleh menggunakan fungsi `millis()` dan dimasukkan ke dalam objek JSON sebelum data dikirim.

Bagian yang ditambahkan:

```cpp
doc["uptime"] = millis();
```

Keterangan:

1. `millis()` mengambil waktu berjalan perangkat dalam satuan milidetik sejak board mulai aktif.
2. Nilai tersebut disimpan pada properti JSON bernama `uptime`.
3. Dengan demikian, payload yang dikirim sekarang memuat suhu, kelembaban, dan waktu operasi perangkat.

Contoh payload:

```json
{
  "suhu": 28.5,
  "kelembaban": 65.0,
  "uptime": 12345
}
```

## Dokumentasi

### Percobaan 3A

[![Dokumentasi Percobaan 3A](Dokumentasi/Dokumentasi-Percobaan3A.jpg)](https://drive.google.com/drive/folders/1fwxat9GcEHR9K5VbgMMQqpaUJNix45-k?usp=sharing)

### Percobaan 3B

[![Dokumentasi Percobaan 3B](Dokumentasi/Dokumentasi-Percobaan3B.jpg)](https://drive.google.com/drive/folders/1fwxat9GcEHR9K5VbgMMQqpaUJNix45-k?usp=sharing)
