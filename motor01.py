import time
from adafruit_motorkit import MotorKit

kit = MotorKit()

kit.motor1.throttle = 0
kit.motor2.throttle = 0
a=0
while (a==0):
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
        a=1
