#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


void setup() {

  Serial.begin(115200);

  dht.begin();

  Serial.println("Pembacaan Sensor DHT22 Dimulai");

}


void loop() {

  float suhu = dht.readTemperature();

  float kelembaban = dht.readHumidity();


  if (isnan(suhu) || isnan(kelembaban)) {

    Serial.println("Gagal membaca sensor DHT22");

  } 
  else {

    Serial.print("Suhu : ");
    Serial.print(suhu);
    Serial.println(" C");


    Serial.print("Kelembaban : ");
    Serial.print(kelembaban);
    Serial.println(" %");

  }


  delay(2000);

}
