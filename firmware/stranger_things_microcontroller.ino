#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>


char ssid[] = ""; // your network SSID (name)
char password[] = ""; // your network key

const int ledDataPin = 5;
const int numberOfLeds = 30;

WiFiClientSecure client;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(numberOfLeds, ledDataPin, NEO_GRB + NEO_KHZ800);


void setupWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(800);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  client.setInsecure();
}

void setup() {
  Serial.begin(115200);
  strip.begin();
  setupWiFi();
}


static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i, c);
      strip.setPixelColor(i-4, 0);
      strip.show();
      delay(25);
  }
}


int getNumberFromLetter(char x) {
  return (int)x - 97;
}


void flashWordOnStrip(String theWord) {
  for(int i=0; i < strlen(theWord.c_str()); i++ ) {
    char c = theWord.c_str()[i];
    int ledToFlash = getNumberFromLetter(c);
    uint32_t colour = strip.Color(random(0, 128), random(0, 128), random(0, 128));
    strip.setPixelColor(ledToFlash, colour);
    strip.show();
    Serial.println(ledToFlash);
    delay(1000);
    strip.setPixelColor(ledToFlash, 0);
    strip.show();
    delay(300);
  }
}


void displayWord(String wordToDisplay) {
  chase(strip.Color(255, 0, 0)); // Chase Red
  delay(1000);
  flashWordOnStrip(wordToDisplay);
  chase(strip.Color(0, 0, 255)); // Chase Blue
}


String getWordForDisplay() {
  String theWord = "";
  long now;
  char host[] = ""; // host of your server
  if (client.connect(host, 443)) {
    String URL = ""; // endpoint of your server
    client.println("GET " + URL + " HTTP/1.1");
    client.print("Host: "); client.println(host);
    client.println("User-Agent: arduino/1.0");
    client.println("");
    now = millis();
    while (millis() - now < 100) {
      if (client.available()) {
        String response = client.readString();
        int bodypos =  response.indexOf("\r\n\r\n") + 4;
        theWord = response.substring(bodypos);
        Serial.print("word: ");
        Serial.println(theWord);
      }
    }
  }
  return theWord;
}


void loop() {
  String theWord = getWordForDisplay();
  if (theWord != "") {
    displayWord(theWord);
  }
  Serial.println(theWord);
}
