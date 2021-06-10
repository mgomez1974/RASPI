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

#define SERIAL_MONITOR  0
#define ADC             1
#define SERVO           2
#define GRAPHIC         3
#define NOTHING_TO_DO   10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void plotter(int graph, int l_xp1,int l_yp1,int l_xp2,int l_yp2,int l_xp3,int l_yp3, int l_valp, int l_vals);

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
  tft.setRotation(3);
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Bonjour momo!");
      
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
 
  static int token = NOTHING_TO_DO;
  
  static unsigned long previus_Millis_SERIAL_MONITOR=0;
  static unsigned long previus_Millis_ADC=0;
  static unsigned long previus_Millis_SERVO=0;
  static unsigned long previus_Millis_GRAPHIC=0;

  const long interval_SERIAL_MONITOR = 60;  
  const long interval_ADC = 5;  
  const long interval_SERVO = 20;  
  const long interval_GRAPHIC = 20;  
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previus_Millis_SERIAL_MONITOR   >= interval_SERIAL_MONITOR)       token = SERIAL_MONITOR;
  if (currentMillis - previus_Millis_ADC        >= interval_ADC)                        token = ADC;
  if (currentMillis - previus_Millis_SERVO      >= interval_SERVO)                      token = SERVO;
  if (currentMillis - previus_Millis_GRAPHIC    >= interval_GRAPHIC)                    token = GRAPHIC;
  
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
    }break;

    case ADC:
    {
        val1p = analogRead(potpin1);            
        val2p = analogRead(potpin2);
        val3p = analogRead(potpin3);  
        previus_Millis_ADC = millis();
        token = NOTHING_TO_DO;
    }break;
    
    
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
    }break;

    case GRAPHIC:
    {
        //plotter(int graph, int l_xp1,int l_yp1,int l_xp2,int l_yp2,int l_xp3,int l_yp3, int l_valp, int l_vals)
        plotter(1, xp1,yp1,xp2,yp2,xp3,yp3,val1p,val1s);
        plotter(2, xp4,yp4,xp5,yp5,xp6,yp6,val2p,val2s);
        plotter(3, xp7,yp7,xp8,yp8,xp9,yp9,val3p,val3s);
        previus_Millis_GRAPHIC = millis();
        token = NOTHING_TO_DO;
    }break;
    
    case NOTHING_TO_DO:
    {
        
    }break;
    

    default:
    {
     
      }break;            
  }

}

void plotter(int graph, int l_xp1,int l_yp1,int l_xp2,int l_yp2,int l_xp3,int l_yp3, int l_valp, int l_vals)
{
  static int x1_old[4]={0,0,0,0};
  static int y1_old[4]={0,0,0,0};
  int l_x1,l_y1;
  tft.drawLine(l_xp2, l_yp2, l_xp1, l_yp1, ILI9341_WHITE);
  tft.drawLine(l_xp1, l_yp1, l_xp3, l_yp3, ILI9341_WHITE);
  l_x1=map(l_valp,0,1023,l_xp1,l_xp3);
  l_y1=map(l_vals,0,180,l_yp1,l_yp2);
  tft.fillCircle(x1_old[graph], y1_old[graph], 3, ILI9341_BLUE);
  tft.fillCircle(l_x1,            l_y1,            3, ILI9341_GREEN);
  x1_old[graph]=l_x1;
  y1_old[graph]=l_y1;

}
