#création d'une machine à états finis
from time import sleep
import serial


ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=1
)

state=0
ch=0
while state!=99:
    var_aux='lola'.encode('utf-8')
    ser.write(var_aux)
    sleep(0.1)
    if(ser.in_waiting>=1):
        ch=ser.read()
        print(ch)
        if   (ch=='a'.encode('utf-8')):
             state=1
             print ('a')
        elif (ch=='x'.encode('utf-8')):
             state=99
             print ("state 99")
        else:
             state=2
        if   state==1:
             print("premier etat")
        elif state==2:
             print("diferent")
        elif state==99:
             print ("exit")

data="sortir".encode('utf-8')
ser.write(data)
sleep(0.1)

