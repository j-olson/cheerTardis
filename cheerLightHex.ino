

#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include <Adafruit_NeoPixel.h>

#define PIN         4   //pin for neopixels data line
#define NUMPIXELS   32  //number of neopixels attached

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS,PIN, NEO_GRB + NEO_KHZ800); //create the neopixel object


WiFiClient client;

const char* ssid = "sasquatch";
const char* pwd = "pizzap1zza";
const char* host = "api.thingspeak.com";
unsigned long cheerLightsChannelNumber = 1417;
const int delayval = 500;
const int brightness = 10;  //0-100 brightness level of neopixels

void setup(){

  pixels.begin();
  pixels.setBrightness(brightness);
  pixels.show();
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to Wifi - ");
  Serial.println(ssid);

  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("Wifi Connected");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);

}


void loop() {

  //check to see if we can reach api.thingspeak.com
  const int httpPort = 80;
  if(!client.connect(host, httpPort)){
    Serial.println("connection failed!");
    return;
  }

  delay(500); // Just a quick pause to let everything settle
  
  String colorHex = ThingSpeak.readStringField(cheerLightsChannelNumber, 2); //connect to ThingSpeak and get HEX value of color

  //convert HEX string into rgb values
  int colorRGB = (int)strtol(&colorHex[1], NULL, 16);
  int r = colorRGB >> 16;
  int g = colorRGB >> 8 & 0xFF;
  int b = colorRGB & 0xFF;
  
  setColor(r,g,b);
  delay(18000);
    
  }

  void setColor(int r,int g, int b)
{
    for (int i = 0; i <= NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(r,g,b));
    }
    pixels.show();
    //delay(delayval);
    
}

