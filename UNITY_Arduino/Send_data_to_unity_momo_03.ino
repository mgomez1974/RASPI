/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438

Mauricio:
cet programme marche avec script10.cs
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!
#define LSM9DS1_SCK SCK
#define LSM9DS1_MISO MISO
#define LSM9DS1_MOSI MOSI
#define LSM9DS1_XGCS 24
#define LSM9DS1_MCS 25
// Or hardware SPI! In this case, only CS pins are passed in
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}


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
  Serial.begin(115200);
  Serial2.begin(115200);           // set up Serial2 library at 9600 bps
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

  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();
}

void loop() {

  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

//  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
//  Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
//  Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

//  Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" uT");
//  Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" uT");
//  Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" uT");

//  Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
//  Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
//  Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");
//        Serial.print("f");   Serial.print  (SensorLine1_answer);  Serial.print  (";");
//        Serial.print("g");   Serial.print  (SensorLine2_answer);  Serial.print  (";"); 
//        Serial.print("h");   Serial.print  (SensorLine3_answer);  Serial.print  (";");
//        Serial.print("i");   Serial.print  (SensorLine4_answer);  Serial.print  (";");
//        Serial.print("e");   Serial.print  (SensorLine5_answer);  Serial.print  (";");
//        Serial.print("z");                                         Serial.println(";");
//        continuer=0;
//
//  Serial.println();

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
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial2.print("sa:");   Serial2.print  (SensorLine1_answer);  Serial2.print  (";");}
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial2.print("sb:");   Serial2.print  (SensorLine2_answer);  Serial2.print  (";");} 
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial2.print("sc:");   Serial2.print  (SensorLine3_answer);  Serial2.print  (";");}
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial2.print("sd:");   Serial2.print  (SensorLine4_answer);  Serial2.print  (";");}
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial2.print("se:");   Serial2.print  (SensorLine5_answer);  Serial2.print  (";");}

        Serial2.print("ga:");   Serial2.print  (a.acceleration.x);    Serial2.print  (";");
        Serial2.print("gb:");   Serial2.print  (a.acceleration.y);    Serial2.print  (";");
        Serial2.print("gc:");   Serial2.print  (a.acceleration.z);    Serial2.print  (";");
        
        Serial2.print("gd:");   Serial2.print  (m.magnetic.x);        Serial2.print  (";");
        Serial2.print("ge:");   Serial2.print  (m.magnetic.y);        Serial2.print  (";");
        Serial2.print("gf:");   Serial2.print  (m.magnetic.z);        Serial2.print  (";");
        
        Serial2.print("gg:");   Serial2.print  (g.gyro.x    );        Serial2.print  (";");
        Serial2.print("gh:");   Serial2.print  (g.gyro.y    );        Serial2.print  (";");
        Serial2.print("gi:");   Serial2.print  (g.gyro.z    );        Serial2.print  (";");
        Serial2.print("z");                                           Serial2.println(";");

        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial.print("sa:");   Serial.print  (SensorLine1_answer);  Serial.print  (";");}
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial.print("sb:");   Serial.print  (SensorLine2_answer);  Serial.print  (";");} 
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial.print("sc:");   Serial.print  (SensorLine3_answer);  Serial.print  (";");}
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial.print("sd:");   Serial.print  (SensorLine4_answer);  Serial.print  (";");}
        if (SensorLine1_answer!=SensorLine1_answer_old) {Serial.print("se:");   Serial.print  (SensorLine5_answer);  Serial.print  (";");}

        Serial.print("ga:");   Serial.print  (a.acceleration.x);      Serial.print  (";");
        Serial.print("gb:");   Serial.print  (a.acceleration.y);      Serial.print  (";");
        Serial.print("gc:");   Serial.print  (a.acceleration.z);      Serial.print  (";");
        
        Serial.print("gd:");   Serial.print  (m.magnetic.x);          Serial.print  (";");
        Serial.print("ge:");   Serial.print  (m.magnetic.y);          Serial.print  (";");
        Serial.print("gf:");   Serial.print  (m.magnetic.z);          Serial.print  (";");
        
        Serial.print("gg:");   Serial.print  (g.gyro.x    );        Serial.print  (";");
        Serial.print("gh:");   Serial.print  (g.gyro.y    );        Serial.print  (";");
        Serial.print("gi:");   Serial.print  (g.gyro.z    );        Serial.print  (";");
        Serial.print("z");                                            Serial.println(";");
        continuer=0;
      }

  SensorLine1_answer_old = SensorLine1_answer;
  SensorLine2_answer_old = SensorLine2_answer;
  SensorLine3_answer_old = SensorLine3_answer;
  SensorLine4_answer_old = SensorLine4_answer;
  SensorLine5_answer_old = SensorLine5_answer;



}
