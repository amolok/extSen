#include <math.h>
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
#include "SevenSegmentFun.h"

#define LightPIN 0
#define ThermisterPIN 1
#define MQ7PIN 2
#define WetPIN 3
#define CLK 4
#define DIO 5

String str = String(64);
// 22.45°C    980 lux   594 CO   1000 
char buf[6];


// TM1637Display display(CLK, DIO);
// SevenSegmentExtended display(CLK, DIO);
// SevenSegmentTM1637 display(CLK, DIO);
SevenSegmentFun display(CLK, DIO);

double Thermister(int RawADC) {
  double Temp;
  Temp = log(((10240000/RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
  Temp = Temp - 273.15;
// Convert Kelvin to Celcius
  return Temp;
}

void setup() {
  pinMode(LightPIN, INPUT);
  // Serial.begin(9600);
  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %
  // Serial.println("=== Water ===");
  display.scrollingText("Water", 1);
}

void loop() {
  // str[0]=0;
  float l = analogRead(LightPIN);
  float t = Thermister(analogRead(ThermisterPIN));
  float co= analogRead(MQ7PIN);
  float wl= analogRead(WetPIN);
  int d = (int) (t*100);
  // display.print(d);
  // display.showNumberDecDot(d,false,4,0,1);
  // display.write((uint8_t) l);
  // display.write("lux");

/*
  Serial.print(l);
  Serial.print(" lux \t ");
  Serial.print(t);
  Serial.print(" °C \t");
  Serial.print(co);
  Serial.print(" CO sensor \t");
  Serial.print(wl);
  Serial.print(" water level \t");
  Serial.println("<");
*/
  str=' ';
  dtostrf(t,2,1,buf);
  str=buf;
  str+=+"C";
  str+="   ";
  // Serial.print(str);
  dtostrf(l,4,1,buf);
  str+="L ";
  str+=buf;
  str+="   ";
  dtostrf(co,4,1,buf);
  str+="CO ";
  str+=buf;
  str+="   ";
  dtostrf(wl,4,1,buf);
  str+="water ";
  str+=buf;
  str+="   ";

  // display.scrollingText(str,1);
  const char * c = str.c_str();
  // Serial.println(str);
  // Serial.println(c);
  // Serial.println("===");
  display.scrollingText(c, 1);

  // Serial.println(d);
  delay(300);
}