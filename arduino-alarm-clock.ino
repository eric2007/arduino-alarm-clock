#include <EEPROM.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SimpleDHT.h>
#include <String.h>
#include <ThreeWire.h> 
#include <RtcDS1302.h>
#include <Arduino.h>
#define DHTpin 2
#define null NULL //my way
#define DC 9
#define RST 8
#define DATA 11
#define CLOCK 13
#define CLK_CE 7 //RST for old
#define IO 6
#define SCLK 5
#define OKpin 3
#define UPpin A0
#define DOWNpin A1
#define BUZZERpin 4
ThreeWire myWire(IO,SCLK,CLK_CE); // IO, SCLK, CE
RtcDS1302<ThreeWire> rtc(myWire);
SimpleDHT11 dht11(DHTpin);
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);
bool OKbutton;
bool UPbutton;
bool DOWNbutton;
byte temp;
byte humi;
String date;
RtcDateTime now;
void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  Serial.begin(19200);
  rtc.Begin();
  pinMode(BUZZERpin,OUTPUT);
  pinMode(UPpin,INPUT_PULLUP);
  pinMode(DOWNpin,INPUT_PULLUP);
  pinMode(OKpin,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  getSensors();
  delay(1000);
}
void getSensors(){
  now = rtc.GetDateTime();
  dht11.read(DHTpin,&temp,&humi,null);
  OKbutton = digitalRead(OKpin);
  DOWNbutton = floor(analogRead(DOWNpin) / 128);
  UPbutton = floor(analogRead(UPpin) / 128);
}
void printData() {
  u8g2.firstPage();
  do{
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0, 16);
    char tmp[50];
    sprintf(tmp, "%4d-%2d-%2d    %s", now.Year(),now.Month(),now.Day(),getDay(now.DayOfWeek()));
    u8g2.print(tmp);
  }while (u8g2.nextPage());
}
String getDay(byte DOW) {
  switch (DOW){
    case 0:
      return "Sunday";
    case 1:
      return "Monday";
    case 2:
      return "Tuesday";
    case 3:
      return "Wednesday";
    case 4:
      return "Thursday";
    case 5:
      return "Friday";
    case 6:
      return "Saturday";
    default:
      return "Error";
  }
}
