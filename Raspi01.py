from time import sleep
import serial
import RPi.GPIO as GPIO
from adafruit_motorkit import MotorKit

kit = MotorKit()
GPIO.setmode(GPIO.BCM)


ser = serial.Serial(                                         
    port='/dev/ttyS0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

state=0
ch=0
speed=0.5
while state!=99:
    if(ser.in_waiting>=1):
        ch=ser.read()
        print(ch)
        if (ch=='f'.encode('utf-8')):
            speed+=0.1
            print(speed)
            print ('vitesse')
        if (ch=='g'.encode('utf-8')):
            speed-=0.1
            print(speed)
            print ('vitesse')
        if (ch=='a'.encode('utf-8')):
            state=1
            print ('gouche')
        if (ch=='d'.encode('utf-8')):
            state=2
            print ('droit')
        if (ch=='w'.encode('utf-8')):
            state=3
            print ('toute droit')
        if (ch=='s'.encode('utf-8')):
            state=4
            print ('arret')
        if (ch=='z'.encode('utf-8')):
            state=5
            print ('revers')
        if (ch=='x'.encode('utf-8')):
            state=99
            print ("state 99")
        
        if state==1:
            kit.motor1.throttle = speed
            kit.motor2.throttle = speed
        if state==2:
            kit.motor1.throttle = speed*-1
            kit.motor2.throttle = speed*-1
        if state==3:
            kit.motor1.throttle = speed
            kit.motor2.throttle = speed*-1
        if state==4:
            kit.motor1.throttle = speed*0
            kit.motor2.throttle = speed*0
        if state==5:
            kit.motor1.throttle = speed*-1
            kit.motor2.throttle = speed
        if state==99:
            print ("exit")

data="sortir".encode('utf-8')
ser.write(data)
sleep(0.1)
kit.motor1.throttle = 0
kit.motor2.throttle = 0
GPIO.cleanup()
