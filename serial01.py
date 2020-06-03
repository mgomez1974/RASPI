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

data="lola".encode('utf-8')
ser.write(data)
sleep(0.1)

