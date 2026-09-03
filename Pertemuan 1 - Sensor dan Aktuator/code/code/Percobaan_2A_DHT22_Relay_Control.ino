#include <DHT.h>


#define DHTPIN 4
#define DHTTYPE DHT22

#define RELAYPIN 26


DHT dht(DHTPIN, DHTTYPE);


float suhuThreshold = 30.0;



void setup() {


  Serial.begin(115200);


  dht.begin();


  pinMode(RELAYPIN, OUTPUT);


  digitalWrite(RELAYPIN, LOW);


  Serial.println("Sistem Relay Aktif");

}



void loop() {


  float suhu = dht.readTemperature();



  if(isnan(suhu)) {


    Serial.println("Sensor gagal membaca data");


  }

  else {


    Serial.print("Suhu : ");

    Serial.print(suhu);

    Serial.println(" C");



    if(suhu > suhuThreshold) {


      digitalWrite(RELAYPIN, HIGH);


      Serial.println("Relay ON");


    }


    else {


      digitalWrite(RELAYPIN, LOW);


      Serial.println("Relay OFF");


    }


  }



  delay(2000);


}
