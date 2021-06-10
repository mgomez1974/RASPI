/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 36
#define TFT_CS 38
#define TFT_MOSI MOSI
#define TFT_CLK SCK
#define TFT_MISO MISO
#define TFT_RST 32

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


const long SERIAL_REFRESH_TIME = 100;
long refresh_time;

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;

int potpin1 = A1;  // analog pin used to connect the potentiometer
int potpin2 = A2;
int potpin3 = A3;
int val1p,val2p,val3p;    // variable to read the value from the analog pin
int val1s,val2s,val3s;
int val1_aux,val2_aux,val3_aux;
static int continuer;

void setup() {
//  Serial2.begin(115200);
  Serial.begin(9600);
  //Serial.begin(9600);
  myservo1.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(7);
  myservo3.attach(8);

  tft.begin();
uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

  tft.fillScreen(ILI9341_BLUE);
      
}

void loop() {
  int 
  x1=0,
  y1=0,
  x2=0,
  y2=0,
  x3=0,
  y3=0;
  static int 
  x1_old=0,
  y1_old=0,
  x2_old=0,
  y2_old=0,
  x3_old=0,
  y3_old=0;
  int  
  xp1=10,    yp1=60, 
  xp2=10,    yp2=10, 
  xp3=200,   yp3=60, 
  
  xp4=10,    yp4=120, 
  xp5=10,    yp5=70, 
  xp6=200,   yp6=120, 
  
  xp7=10,    yp7=180, 
  xp8=10,    yp8=130, 
  xp9=200,   yp9=180;

  
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Bonjour momo!");

  val1p = analogRead(potpin1);            
  val2p = analogRead(potpin2);
  val3p = analogRead(potpin3);
  
  
  val1s = map(val1p, 0, 1023, 0, 180);
  val2s = map(val2p, 0, 1023, 0, 180);
  val3s = map(val3p, 0, 1023, 180, 0); 
  
  myservo1.write(val1s); 
  myservo2.write(val2s);
  myservo3.write(val3s); 
  
      Serial.print("min:");
      Serial.print(0);
      Serial.print(" s1:");
      Serial.print((int)val1s);
      Serial.print(" s2:");
      Serial.print((int)val2s);
      Serial.print(" s3:");
      Serial.print((int)val3s);
      Serial.print(" max:");
      Serial.println(180);

       Serial.print("min:");
      Serial.print(0);
      Serial.print(" s1:");
      Serial.print((int)val1s);
      Serial.print(" s2:");
      Serial.print((int)val2s);
      Serial.print(" s3:");
      Serial.print((int)val3s);
      Serial.print(" max:");
      Serial.println(180);          

      Serial.print("min:");
      Serial.print(0);
      Serial.print(" s1:");
      Serial.print((int)val1s);
      Serial.print(" s2:");
      Serial.print((int)val2s);
      Serial.print(" s3:");
      Serial.print((int)val3s);
      Serial.print(" max:");
      Serial.println(180);

      Serial.print("min:");
      Serial.print(0);
      Serial.print(" s1:");
      Serial.print((int)val1s);
      Serial.print(" s2:");
      Serial.print((int)val2s);
      Serial.print(" s3:");
      Serial.print((int)val3s);
      Serial.print(" max:");
      Serial.println(180);      
  tft.drawLine(xp2, yp2, xp1, yp1, ILI9341_WHITE);
  tft.drawLine(xp1, yp1, xp3, yp3, ILI9341_WHITE);
  x1=map(val1p,0,1023,xp1,xp3);
  y1=map(val1s,0,180,yp1,yp2);
  tft.fillCircle(x1_old, y1_old, 3, ILI9341_BLUE);
  tft.fillCircle(x1,     y1,     3, ILI9341_GREEN);
  x1_old=x1;
  y1_old=y1;

  tft.drawLine(xp5, yp5, xp4, yp4, ILI9341_WHITE);
  tft.drawLine(xp4, yp4, xp6, yp6, ILI9341_WHITE);
  tft.fillCircle(x2, y2, 15, ILI9341_GREEN);

  tft.drawLine(xp8, yp8, xp7, yp7, ILI9341_WHITE);
  tft.drawLine(xp7, yp7, xp9, yp9, ILI9341_WHITE);
  tft.fillCircle(x3, y3, 15, ILI9341_GREEN);

  
 
  //delay(15);                           // waits for the servo to get there
}
