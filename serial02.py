from time import sleep
import serial


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
while state!=99:
    if(ser.in_waiting>=1):
        ch=ser.read()
        print(ch)
        if (ch=='a'.encode('utf-8')):
            state=1
            print ('a')
        if (ch=='x'.encode('utf-8')):
            state=99
            print ("state 99")
        if state==1:
            print("premier etat")
        if state==99:
            print ("exit")

data="sortir".encode('utf-8')
ser.write(data)
sleep(0.1)
