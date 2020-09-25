/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438

Mauricio:
cet programme marche avec script07.cs
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

uint8_t ciclo=0;
// Create the motor shield object with the default I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
 Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);
  static unsigned long lastMilli  = 0;

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor_gauche = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor_droite = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

const int SensorLine1_pin = 27;
const int SensorLine2_pin = 26;
const int SensorLine3_pin = 29;
const int SensorLine4_pin = 28;
const int SensorLine5_pin = 31;

static int SensorLine1_answer = 0 ;
static int SensorLine2_answer = 0 ;
static int SensorLine3_answer = 0 ;
static int SensorLine4_answer = 0 ;
static int SensorLine5_answer = 0 ;

static int SensorLine1_answer_old = 0 ;
static int SensorLine2_answer_old = 0 ;
static int SensorLine3_answer_old = 0 ;
static int SensorLine4_answer_old = 0 ;
static int SensorLine5_answer_old = 0 ;

static int continuer;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);           // set up Serial2 library at 9600 bps
  Serial2.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor_gauche->setSpeed(150);
  myMotor_gauche->run(FORWARD);
  // turn on motor
  myMotor_gauche->run(RELEASE);

  myMotor_droite->setSpeed(150);
  myMotor_droite->run(FORWARD);
  // turn on motor
  myMotor_droite->run(RELEASE);
  ciclo=0;
    pinMode(SensorLine1_pin, INPUT);
  pinMode(SensorLine2_pin, INPUT);
  pinMode(SensorLine3_pin, INPUT);
  pinMode(SensorLine4_pin, INPUT);
  pinMode(SensorLine5_pin, INPUT);
  continuer=1;
}

void loop() {

  if (Serial2.available()>0){
    char variable_read;
    variable_read=Serial2.read();
    if (variable_read == 'y')
    {
      continuer=1;
    }

  }

    SensorLine1_answer = digitalRead(SensorLine1_pin);
    SensorLine2_answer = digitalRead(SensorLine2_pin);
    SensorLine3_answer = digitalRead(SensorLine3_pin);
    SensorLine4_answer = digitalRead(SensorLine4_pin);
    SensorLine5_answer = digitalRead(SensorLine5_pin);

        if (continuer==1)
        {
        Serial2.print("a");   Serial2.print  (SensorLine1_answer);  Serial2.print  (";");
        Serial2.print("b");   Serial2.print  (SensorLine2_answer);  Serial2.print  (";"); 
        Serial2.print("c");   Serial2.print  (SensorLine3_answer);  Serial2.print  (";");
        Serial2.print("d");   Serial2.print  (SensorLine4_answer);  Serial2.print  (";");
        Serial2.print("e");   Serial2.print  (SensorLine5_answer);  Serial2.print  (";");
        Serial2.print("z");                                         Serial2.println(";");

        Serial.print("a");   Serial.print  (SensorLine1_answer);  Serial.print  (";");
        Serial.print("b");   Serial.print  (SensorLine2_answer);  Serial.print  (";"); 
        Serial.print("c");   Serial.print  (SensorLine3_answer);  Serial.print  (";");
        Serial.print("d");   Serial.print  (SensorLine4_answer);  Serial.print  (";");
        Serial.print("e");   Serial.print  (SensorLine5_answer);  Serial.print  (";");
        Serial.print("z");                                         Serial.println(";");
        continuer=0;
      }

  SensorLine1_answer_old = SensorLine1_answer;
  SensorLine2_answer_old = SensorLine2_answer;
  SensorLine3_answer_old = SensorLine3_answer;
  SensorLine4_answer_old = SensorLine4_answer;
  SensorLine5_answer_old = SensorLine5_answer;
}

//void loop() {
//  uint8_t i;
//  
//  if (ciclo==0)
//  {
//  Serial2.print("tick");
//
//  myMotor_gauche->run(FORWARD);
//  for (i=0; i<255; i++) {
//    myMotor_gauche->setSpeed(i);  
//    delay(10);
//  }
//  for (i=255; i!=0; i--) {
//    myMotor_gauche->setSpeed(i);  
//    delay(10);
//  }
//  
//  Serial2.print("tock");
//
//  myMotor_gauche->run(BACKWARD);
//  for (i=0; i<255; i++) {
//    myMotor_gauche->setSpeed(i);  
//    delay(10);
//  }
//  for (i=255; i!=0; i--) {
//    myMotor_gauche->setSpeed(i);  
//    delay(10);
//  }
//
//  Serial2.print("techa");
//  myMotor_gauche->run(RELEASE);
//  delay(1000);
//  
//  if (Serial2.available()>0) 
//  {
//    Serial2.println("   bye-bye");
//    Serial2.println("   bye-bye");
//    ciclo=1;
//    myMotor_gauche->setSpeed(0);
//  }
//  if (ciclo==1)
//  {
//    //do nothing
//    }
//  }
//  
//}
