/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
Mauricio:
Connexion du capteur de distance analogique

*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Encoder.h>

Encoder knobGauche(2, 4);
Encoder knobDroite(3, 5);


uint8_t token = 0;
// Create the motor shield object with the default I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
 Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);
  

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotorGauche = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorDroite = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

static unsigned long lastMilli  = 0;
static unsigned long lastMilli2 = 0;


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


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotorGauche->setSpeed(150);
  myMotorGauche->run(FORWARD);
  // turn on motor
  myMotorGauche->run(RELEASE);

  myMotorDroite->setSpeed(150);
  myMotorDroite->run(FORWARD);
  // turn on motor
  myMotorDroite->run(RELEASE);
  token=0;
  lastMilli  = millis();
  lastMilli2 = millis();
  pinMode(SensorLine1_pin, INPUT);
  pinMode(SensorLine2_pin, INPUT);
  pinMode(SensorLine3_pin, INPUT);
  pinMode(SensorLine4_pin, INPUT);
  pinMode(SensorLine5_pin, INPUT);
  
}

void loop() {
  uint8_t i;
  long newGauche, newDroite;
  static long limit_knob_Gauche=0;
  static long limit_knob_Droite=0;
  
  newGauche = knobGauche.read();
  newDroite = knobDroite.read();

  switch (token)
  {
    case 0:
    {
      if(millis()-lastMilli > 10){ 
      myMotorGauche->setSpeed(0);
      myMotorDroite->setSpeed(0);
      knobGauche.write(0);
      knobDroite.write(0);
      myMotorGauche->run(RELEASE);
      myMotorDroite->run(RELEASE);
      lastMilli = millis();
      }
    }break;
    
    case 1:
    {
      Serial.println("case1");
      
      myMotorGauche->run(FORWARD);
      myMotorGauche->setSpeed(200);
      
      limit_knob_Gauche=5000;
      token = 99;
      Serial.print ("Encoder=");
      Serial.println(newGauche);
    }break;

    case 2:
    {
      Serial.println("case2");
      
      myMotorGauche->run(FORWARD);
      myMotorGauche->setSpeed(200);
      
      limit_knob_Gauche=15000;
      token = 99;
      Serial.print ("Encoder=");
      Serial.println(newGauche);
    }break;

    case 3:
    {
      Serial.println("case3");
      
      myMotorDroite->run(FORWARD);
      myMotorDroite->setSpeed(200);
      
      limit_knob_Droite=5000;
      token = 99;
      Serial.print ("Encoder=");
      Serial.println(newDroite);
    }break;

    case 4:
    {
      Serial.println("case4");
      
      myMotorDroite->run(FORWARD);
      myMotorDroite->setSpeed(200);
      
      limit_knob_Droite=15000;
      token = 99;
      Serial.print ("Encoder=");
      Serial.println(newDroite);
    }break;


    case 99:
    {
      if (newGauche>limit_knob_Gauche) 
      {
        token = 0;
        Serial.println("ending case");
        Serial.print ("Encoder=");
        Serial.println(newGauche);
      }
      if (newDroite>limit_knob_Droite) 
      {
        token = 0;
        Serial.println("ending case");
        Serial.print ("Encoder=");
        Serial.println(newDroite);
      }
    }break;
  }
  
  if (Serial.available()>0) 
  {
    char var_read;
    var_read=Serial.read();
    if (var_read=='a') token = 1;
    if (var_read=='b') token = 2;
    if (var_read=='c') token = 3;
    if (var_read=='d') token = 4;
    if (var_read=='x') 
    {
      token = 0;
      Serial.print ("Encoder=");
      Serial.println(newGauche);
      Serial.println("exit");
      
    }

    if (var_read=='r') 
    {
      token = 0;
      Serial.print ("Retablir I2C");
      AFMS.begin();  // create with the default frequency 1.6KHz
    }
    
    
  }
  SensorLine1_answer = digitalRead(SensorLine1_pin);
  SensorLine2_answer = digitalRead(SensorLine2_pin);
  SensorLine3_answer = digitalRead(SensorLine3_pin);
  SensorLine4_answer = digitalRead(SensorLine4_pin);
  SensorLine5_answer = digitalRead(SensorLine5_pin);
  if (SensorLine1_answer != SensorLine1_answer_old ||
      SensorLine2_answer != SensorLine2_answer_old ||
      SensorLine3_answer != SensorLine3_answer_old ||
      SensorLine4_answer != SensorLine4_answer_old ||
      SensorLine5_answer != SensorLine5_answer_old)
      {
        Serial.print(" S1:");   Serial.print  (SensorLine1_answer);
        Serial.print(" S2:");   Serial.print  (SensorLine2_answer);
        Serial.print(" S3:");   Serial.print  (SensorLine3_answer);
        Serial.print(" S4:");   Serial.print  (SensorLine4_answer);
        Serial.print(" S5:");   Serial.println(SensorLine5_answer);
      }

  SensorLine1_answer_old = SensorLine1_answer;
  SensorLine2_answer_old = SensorLine2_answer;
  SensorLine3_answer_old = SensorLine3_answer;
  SensorLine4_answer_old = SensorLine4_answer;
  SensorLine5_answer_old = SensorLine5_answer;

  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
 
  if(millis()-lastMilli2 > 100)
  { 
    Serial.println(voltage);
    lastMilli2 = millis();
  }
  
  
}
