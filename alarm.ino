#include <U8g2lib.h>
#include <RTClib.h>
#include <Wire.h>
#include <SimpleDHT.h>

#define dhtPin 2
#define resetPin 4
#define null NULL
#define DC 9
#define RST 8;
#define DATA 11;
#define CLOCK 13

SimpleDHT11 dht11(4);
Adafruit_SSD1306 display(resetPin);
U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0,CLOCK,DATA,10,DC,RST);
DS1302 rtc;

byte temp;
byte humi;
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  dht11.read(dhtPin,&temp,&humi,null);
}
