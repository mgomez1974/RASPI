import time
import RPi.GPIO as GPIO
from adafruit_motorkit import MotorKit

kit = MotorKit()
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN)
GPIO.setup(17, GPIO.IN)

GPIO.setup(22, GPIO.IN)
GPIO.setup(23, GPIO.IN)

class Encoder:
    a_local=0
    b_local=0

    def my_callback_18(self,channel):
        self.a_local=self.a_local+1
        #return a_local

    def my_callback_22(self,channel):
        self.b_local=self.b_local+1
        #return b_local

    def imprimir(self):
        print("a:")
        print(self.a_local)
        print("b:")
        print(self.b_local)

call = Encoder()
GPIO.add_event_detect(18, GPIO.FALLING, callback=call.my_callback_18,bouncetime=2)
GPIO.add_event_detect(22, GPIO.FALLING, callback=call.my_callback_22,bouncetime=2)


kit.motor1.throttle = 0
kit.motor2.throttle = 0
flag_out=0
while (flag_out==0):
        print("Forward!")
        kit.motor1.throttle = 0
        kit.motor2.throttle = 0
        time.sleep(1)

        print("Speed up...")
        for i in range(0, 101):
            speed = i * 0.01
            kit.motor1.throttle = speed
            kit.motor2.throttle = speed*-1
            time.sleep(0.01)

        print("Slow down...")
        for i in range(100, -1, -1):
            speed = i * 0.01
            kit.motor1.throttle = speed
            kit.motor2.throttle = speed*-1
            time.sleep(0.01)

        print("Stop!")
        kit.motor1.throttle = 0
        kit.motor2.throttle = 0
        time.sleep(1)
        flag_out=1
        
call.imprimir()
GPIO.cleanup()


