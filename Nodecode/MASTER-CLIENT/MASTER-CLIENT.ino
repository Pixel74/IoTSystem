#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>


//Credentials for the master node's network
#define SERVER_SSID "SERVER_SSID"
#define SERVER_PASS "SERVER_PASSWORD"


//Change to match the server's IP
String serverNameTemp = "http://xxx.xxx.x.xx/temp";
String serverNameHumi = "http://xxx.xxx.x.xx/hum";
String serverNameSoil = "http://xxx.xxx.x.xx/soil";
String serverNameSleep = "http://xxx.xxx.x.xx/sleep";

//Credentials for the network with internet access
#define INTERNET_SSID "INTERNET_SSID"
#define INTERNET_PASS "INTERNET_PASSWORD"


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


#define enter D5
#define right D0
#define left D6

int right_state = 0;
int selector = 0;


String temperature;
String humidity;
String hum_soil;
String data = "NaN";


String sleep_string;
const long interval = 60000; //1 minute
unsigned long previousMillis = 0;

int relays[] = {D7, D8, D3, D4};
bool states[] = {false, false, false, false};
int command = 99;


void relay1() {

  command = 0;

  if (states[command] == false) {

    //Turn the relay ON
    digitalWrite(relays[command], LOW);
    states[command] = true;

    //Serial.println("Relay "+String(command)+" ON");

    command = 99;

  }
  else if (states[command] == true) {

    //Turn the relay OFF
    digitalWrite(relays[command], HIGH);
    states[command] = false;

    //Serial.println("Relay "+String(command)+" OFF");

    command = 99;
  }
}

void relay2() {

  command = 1;

  if (states[command] == false) {

    //Turn the relay ON
    digitalWrite(relays[command], LOW);
    states[command] = true;

    //Serial.println("Relay "+String(command)+" ON");

    command = 99;

  }
  else if (states[command] == true) {

    //Turn the relay OFF
    digitalWrite(relays[command], HIGH);
    states[command] = false;

    //Serial.println("Relay "+String(command)+" OFF");

    command = 99;
  }
}


void wifi_slave() {

  temperature = "";
  humidity = "";
  hum_soil = "";


  WiFi.begin(SERVER_SSID, SERVER_PASS);
  //Serial.println("Connecting to server: ");
  //Serial.print(SERVER_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }


  //Serial.println("");
  //Serial.print("Connected to server's network with IP Address: ");
  //Serial.println(WiFi.localIP());


  if (WiFi.status() == WL_CONNECTED) {

    while (hum_soil == "") {

      hum_soil = httpGETRequest(serverNameSoil);
      delay(100);
    }

    while (temperature == "") {

      temperature = httpGETRequest(serverNameTemp);
      delay(100);
    }

    while (humidity == "") {

      humidity = httpGETRequest(serverNameHumi);
      delay(100);
    }

    sleep_string = httpGETRequest(serverNameSleep);


    Serial.println(temperature + "," + humidity + "," + hum_soil);
    lcd.clear();
    sensor_screen();

    wifi_internet();

    previousMillis = millis();
  }
}


void wifi_internet() {

  WiFi.begin(INTERNET_SSID, INTERNET_PASS);
  //Serial.println("Connecting to Internet:");
  //Serial.println(INTERNET_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(":");
  }

  //Serial.println("");
  //Serial.print("Connected to Internet with IP Address: ");
  //Serial.println(WiFi.localIP());
}


String httpGETRequest(String serverName) {
  WiFiClient client;
  HTTPClient http;

  http.begin(client, serverName);
  client.connect(serverName, 80);

  int httpResponseCode = http.GET();

  String payload = "NaN";

  if (httpResponseCode != 0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    //Serial.print("Error code: ");
    //Serial.println(httpResponseCode);
  }

  http.end();

  //Serial.println(payload);

  return payload;
}


void setup() {

  Serial.begin(115200);

  pinMode(enter, INPUT);
  pinMode(right, INPUT);
  pinMode(left, INPUT);


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("IoTSystem Master");
  delay(500);
  lcd.clear();

  //set relays to know state (off)
  for (int i = 0; i < 3; i++) {

    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], HIGH);
  }

  sensor_screen();
  wifi_internet();
}

void loop() {

  handle_btn();

  timerf();

  if (WiFi.status() != WL_CONNECTED) {
    lcd.clear();
    lcd.print("WIFI Disconnected");
  }
}

void timerf() {

  unsigned long currentMillis = millis();

  //Serial.println(String(millis()));

  if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

    wifi_slave();
  }
}

void handle_btn() {


  if (digitalRead(right) == HIGH && right_state == 0) {

    relays_screen();
    right_state = 1;
  }

  else if (digitalRead(right) == HIGH && right_state == 1) {

    sensor_screen();
    right_state = 0;
  }

  if (digitalRead(left) == HIGH && right_state == 1) {

    if (selector == 0) {
      selector = 1;
    }
    else if (selector == 1) {
      selector = 0;
    }

    selection();
  }

  if (digitalRead(enter) == HIGH && right_state == 1) {

    if (selector == 0) {
      relay1();
      selection();
      delay(50);
    }

    if (selector == 1) {
      relay2();
      selection();
      delay(50);
    }
  }

  delay(70);
}

void relays_screen() {


  lcd.clear();
  delay(30);
  lcd.setCursor(0, 0);

  if (states[0] == false) {
    lcd.print("Relay1: OFF");
  }

  else if (states[0] == true) {
    lcd.print("Relay1: ON");
  }

  lcd.setCursor(0, 1);

  if (states[1] == false) {
    lcd.print("Relay2: OFF");
  }

  else if (states[1] == true) {
    lcd.print("Relay2: ON");
  }
}

void selection() {

  relays_screen();

  lcd.setCursor(15, selector);
  lcd.print("*");
  delay(70);
}

void sensor_screen() {


  lcd.clear();
  delay(30);
  lcd.setCursor(0, 0);
  lcd.print("Temp:" + String(temperature) + "C " + "Hum:" + String(humidity) + "%");
  lcd.setCursor(0, 1);
  lcd.print("Soil:" + String(hum_soil) + "%");
}
