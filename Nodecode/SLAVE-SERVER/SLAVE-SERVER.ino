#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

#define AP_SSID "SERVER_SSID"
#define AP_PASS "SERVER_PASSWORD"


//set server IP
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 22);
IPAddress subnet(255, 255, 255, 0);


#include <Wire.h>
#include <DHT.h>

#define DHTTYPE DHT11

DHT dht(D2, DHTTYPE);

#define sensorPin A0
#define led D2

#define transistor D5

int humidity = 0;
int temperature = 0;
int hum_soil = 0;
int last_temperature = 0;
int last_humidity = 0;


void readTemp() {

  digitalWrite(transistor, HIGH);
  DataLED();
  
  delay(3000);
  
  temperature = dht.readTemperature();

  //Error value
  last_temperature = ((temperature == 2147483647) ? last_temperature : temperature);

/*
  if(temperature == 2147483647){
    temperature = last_temperature;
  }else{
    last_temperature = temperature;
  }
*/

  server.send(200, "text/html", String(temperature));
  
  //Serial.println("TEMP Sended: "+String(temperature));

  digitalWrite(transistor, LOW);
}

void readHumi() {
  
  digitalWrite(transistor, HIGH);
  DataLED();
  
  delay(3000);
  
  humidity = dht.readHumidity();

  if(humidity == 2147483647){

    humidity = last_humidity;
  }else{
    last_humidity = humidity;
  }

  server.send(200,"text/html", String(humidity));
  
  //Serial.println("HUM Sended: "+String(humidity));

  digitalWrite(transistor, LOW);
}

void readSoil() {
  
  digitalWrite(transistor, HIGH);
  DataLED();
  
  delay(3000);
  
  hum_soil = analogRead(sensorPin);
  hum_soil = map(hum_soil, 400, 120, 0, 100);

  //Bounds checking for sensor failure
  if(hum_soil >= 100){
    hum_soil = 100; 
  }
  if(hum_soil <= 0){
    hum_soil = 0;
  }

  server.send(200, "text/html", String(hum_soil));

  //Serial.println("SOIL Sended: "+String(hum_soil));

  digitalWrite(transistor, LOW);
}


void DataLED() {
  
  digitalWrite(led, HIGH);
  delay(70);
  digitalWrite(led, LOW);
}

void Deep_sleep() {

  
  //Serial.println("DeepSleep ON");
  server.send(200, "text/html", "DeepSleep: 30 Seconds (30000)");
  delay(100);
  ESP.deepSleep(5.5e+7);

  //Serial.println("DeepSleep OFF");
  delay(100);

  return;
}


void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected server1</h1>");
}

void setup() {

  Serial.begin(115200);
  dht.begin();

  delay(500);

  pinMode(led, OUTPUT);
  pinMode(transistor, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(transistor, LOW);
  pinMode(sensorPin, INPUT);
  
/*
  Serial.print("Setting AP configuration ...");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed");

  Serial.println("Setting AP...");
  Serial.println(WiFi.softAP(AP_SSID, AP_PASS) ? "Ready" : "Failed");
*/

  if (WiFi.softAPConfig(local_IP, gateway, subnet)){
    Serial.print("Ready");
  }else{
    Serial.print("Failed");
  }

  if (WiFi.softAP(AP_SSID, AP_PASS)){
    Serial.print("Ready");
  }else{
    Serial.print('Failed');
  }


/*
  IPAddress IP = WiFi.softAPIP();

  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println("AP Ready!");
*/

  server.on("/", handleRoot);
  server.on("/temp", HTTP_GET, readTemp);
  server.on("/hum", HTTP_GET, readHumi);
  server.on("/soil", HTTP_GET, readSoil);
  server.on("/sleep", HTTP_GET, Deep_sleep);
  
  server.begin();

  //Serial.println("HTTP server started");
}

void loop() {

  server.handleClient();
}
