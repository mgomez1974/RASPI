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

#define SERIAL_MONITOR      0
#define ADC                 1
#define SERVO               2
#define GRAPHIC             3
#define SYSTEME_CARTESIENE  4
#define NOTHING_TO_DO       10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void plotter(int graph, int l_xp1, int l_yp1, int l_xp2, int l_yp2, int l_xp3, int l_yp3, int l_valp, int l_vals);

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;

int potpin1 = A1;  // analog pin used to connect the potentiometer
int potpin2 = A2;
int potpin3 = A3;
int val1p, val2p, val3p;  // variable to read the value from the analog pin
int val1s, val2s, val3s;
int val1_aux, val2_aux, val3_aux;
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
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Bonjour momo!");

}

void loop() {
  int
  x1 = 0,
  y1 = 0,
  x2 = 0,
  y2 = 0,
  x3 = 0,
  y3 = 0;
  static int
  x1_old = 0,
  y1_old = 0,
  x2_old = 0,
  y2_old = 0,
  x3_old = 0,
  y3_old = 0;
  int 
  org_x = 10,
  org_y = 20,
  longeur_axe_x=200,
  longeur_axe_y=50,
  dist_y=25;
  int
  xp1 = org_x,                yp1 = org_y+longeur_axe_y,
  xp2 = org_x,                yp2 = org_y,
  xp3 = longeur_axe_x,        yp3 = org_y+longeur_axe_y,

  xp4 = org_x,                yp4 = yp3+longeur_axe_y+dist_y,
  xp5 = org_x,                yp5 = yp3+dist_y,
  xp6 = longeur_axe_x,        yp6 = yp3+longeur_axe_y+dist_y,

  xp7 = org_x,                yp7 = yp6+longeur_axe_y+dist_y,
  xp8 = org_x,                yp8 = yp6+dist_y,
  xp9 = longeur_axe_x,        yp9 = yp6+longeur_axe_y+dist_y;

  static int token = NOTHING_TO_DO;

  static unsigned long previus_Millis_SERIAL_MONITOR = 0;
  static unsigned long previus_Millis_ADC = 0;
  static unsigned long previus_Millis_SERVO = 0;
  static unsigned long previus_Millis_GRAPHIC = 0;

  const long interval_SERIAL_MONITOR = 60;
  const long interval_ADC = 5;
  const long interval_SERVO = 20;
  const long interval_GRAPHIC = 20;

  unsigned long currentMillis = millis();

  if (currentMillis - previus_Millis_SERIAL_MONITOR   >= interval_SERIAL_MONITOR)       token = SERIAL_MONITOR;
  if (currentMillis - previus_Millis_ADC              >= interval_ADC)                  token = ADC;
  if (currentMillis - previus_Millis_SERVO            >= interval_SERVO)                token = SERVO;
  if (currentMillis - previus_Millis_GRAPHIC          >= interval_GRAPHIC)              token = GRAPHIC;

  switch (token)
  {
    case SERIAL_MONITOR:
      {
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
        previus_Millis_SERIAL_MONITOR = millis();
        token = NOTHING_TO_DO;
      } break;

    case ADC:
      {
        val1p = analogRead(potpin1);
        val2p = analogRead(potpin2);
        val3p = analogRead(potpin3);
        previus_Millis_ADC = millis();
        token = NOTHING_TO_DO;
      } break;


    case SERVO:
      {
        val1s = map(val1p, 0, 1023, 0, 180);
        val2s = map(val2p, 0, 1023, 0, 180);
        val3s = map(val3p, 0, 1023, 180, 0);
        myservo1.write(val1s);
        myservo2.write(val2s);
        myservo3.write(val3s);
        previus_Millis_SERVO = millis();
        token = NOTHING_TO_DO;
      } break;

    case GRAPHIC:
      {
        static int gr=0;
        //plotter(int graph, int l_xp1,int l_yp1,int l_xp2,int l_yp2,int l_xp3,int l_yp3, int l_valp, int l_vals)
        switch(gr)
        {
          case 0:
          {
            plotter(1, xp1, yp1, xp2, yp2, xp3, yp3, val1p, val1s);
            gr++;
          }break;
          case 1:
          {
            plotter(2, xp4, yp4, xp5, yp5, xp6, yp6, val2p, val2s);
            gr++;
          }break;
          case 2:
          {
            plotter(3, xp7, yp7, xp8, yp8, xp9, yp9, val3p, val3s);
            gr=0;
          }break;
        }
        
        previus_Millis_GRAPHIC = millis();
        token = NOTHING_TO_DO;
      } break;


     
    case NOTHING_TO_DO:
      {

      } break;

    default:
      {

      } break;
  }

}

void plotter(int graph, int l_xp1, int l_yp1, int l_xp2, int l_yp2, int l_xp3, int l_yp3, int l_valp, int l_vals)
{
  static int x1_old[4] = {0, 0, 0, 0};
  static int y1_old[4] = {0, 0, 0, 0};
  int l_x1, l_y1;
  int l_offset=4;

  tft.setTextSize(1);

  tft.drawLine(l_xp2, l_yp2, l_xp1, l_yp1, ILI9341_WHITE);
  tft.drawLine(l_xp1, l_yp1, l_xp3, l_yp3, ILI9341_WHITE);
  l_x1 = map(l_valp, 0, 1023, l_xp1, l_xp3);
  l_y1 = map(l_vals, 0, 180, l_yp1, l_yp2);
  tft.setTextColor(ILI9341_BLUE);
  tft.setCursor(x1_old[graph]+l_offset,  y1_old[graph]+l_offset);  
  tft.print("[");   tft.print(x1_old[graph]); tft.print(",");  tft.print(y1_old[graph]);  tft.print("]");
  tft.fillCircle(x1_old[graph], y1_old[graph], 5, ILI9341_BLUE);
  
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(l_x1+l_offset,  l_y1+l_offset);  tft.print("[");   tft.print(l_x1); tft.print(",");  tft.print(l_y1);  tft.print("]");
  tft.fillCircle(l_x1,            l_y1,            3, ILI9341_GREEN);

  tft.setCursor(l_xp1+l_offset,l_yp1+l_offset);  tft.print("[");   tft.print(l_xp1); tft.print(",");  tft.print(l_yp1);  tft.print("]");
  tft.setCursor(l_xp2+l_offset,l_yp2+l_offset);  tft.print("[");   tft.print(l_xp2); tft.print(",");  tft.print(l_yp2);  tft.print("]");
  tft.setCursor(l_xp3+l_offset,l_yp3+l_offset);  tft.print("[");   tft.print(l_xp3); tft.print(",");  tft.print(l_yp3);  tft.print("]");
  
  x1_old[graph] = l_x1;
  y1_old[graph] = l_y1;
}
