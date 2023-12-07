#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "5ot53KwxCSNxeu-NvaWpKEMqq8wUcQBv"; 

char ssid[] = "Karthik";  
char pass[] = "eswar@12345";  

#define DHTPIN D1          // Digital pin D1


#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, h);  //V0 is for Humidity
  Blynk.virtualWrite(V1, t);  //V1 is for Temperature
}

void setup()
{
  Serial.begin(9600); 
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run(); 
}