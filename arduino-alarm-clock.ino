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
#define EEPROM_
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
bool alarmStop;
unsigned char temp;
unsigned char humi;
const unsigned char alarmSize = sizeof(Alarm);
String date;
RtcDateTime now;
struct Alarm{
	unsigned char hour;
	unsigned char minute;
	unsigned char dayOfWeek;
};
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
/*EEPROM first byte
	empty	empty  alarmNum
0b    00        00		0000
*/
/*void readAlarm() {
	EEPROM.get(0,)
}
*/
void loop() {
  // put your main code here, to run repeatedly:
  getSensors();
  printData();
  delay(900);
}
void alarm() {
	//if()
	while (alarmStop) {
		tone(9, 440, 50);
		delay(100);
		if (!digitalRead(OKpin)) {
			alarmStop = false;
			continue;
		}
		tone(9, 440, 50);
		delay(100);
		if (!digitalRead(OKpin)) {
			alarmStop = false;
			continue;
		}
		tone(9, 440, 50);
		delay(100);
		if (!digitalRead(OKpin)) {
			alarmStop = false;
			continue;
		}
		tone(9, 440, 50);
		delay(600);
		if (!digitalRead(OKpin)) {
			alarmStop = false;
			continue;
		}
	}
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
    u8g2.setFont(u8g2_font_ncenB12_tr);
    u8g2.setCursor(0, 16);
    u8g2.print(now.Year());
    u8g2.print('-');
	u8g2.print(now.Month());
    u8g2.print('-');
	u8g2.print(now.Day());
	u8g2.print(' ');
	u8g2.print(getDay(now.DayOfWeek()));
	u8g2.setFont(u8g2_font_ncenB24_tr);
	u8g2.setCursor(4, 42);
	u8g2.print(now.Hour());
	u8g2.print(':');
	u8g2.print(now.Minute());
	u8g2.setFont(u8g2_font_ncenB14_tr);
	u8g2.print(':');
	u8g2.print(now.Second());
	u8g2.setCursor(3,64);
	u8g2.print(temp);
	u8g2.print("oC ");
	u8g2.print(humi);
	u8g2.print("%RH");
	Serial.println(now.Hour());
	Serial.println(now.Minute());
	Serial.println(now.Second());
  } while (u8g2.nextPage());
}
String getDay(unsigned char DOW) {
  switch(DOW){
    case 0:
      return "Sun.";
    case 1:
      return "Mon.";
    case 2:
      return "Tue.";
    case 3:
      return "Wed.";
    case 4:
      return "Thu.";
    case 5:
      return "Fri.";
    case 6:
      return "Sat.";
    default:
      return "Err.";
  }
}

