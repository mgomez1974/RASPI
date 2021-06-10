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

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;

int potpin1 = A1;  // analog pin used to connect the potentiometer
int potpin2 = A2;
int potpin3 = A3;
int val1,val2,val3;    // variable to read the value from the analog pin
int val1_aux,val2_aux,val3_aux;
static int continuer;

void setup() {
//  Serial2.begin(115200);
  Serial.begin(9600);
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
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Bonjour fsm!");

  val1 = analogRead(potpin1);            
  val2 = analogRead(potpin2);
  val3 = analogRead(potpin3);
  
  
  val1 = map(val1, 0, 1023, 0, 180);
  val2 = map(val2, 0, 1023, 0, 180);
  val3 = map(val3, 0, 1023, 180, 0); 
  
  myservo1.write(val1); 
  myservo2.write(val2);
  myservo3.write(val3); 
  
      Serial.print("min:");
      Serial.print(0);
      Serial.print(" s1:");
      Serial.print((int)val1);
      Serial.print(" s2:");
      Serial.print((int)val2);
      Serial.print(" s3:");
      Serial.print((int)val3);
      Serial.print(" max:");
      Serial.println(180);
 
  //delay(15);                           // waits for the servo to get there
}
