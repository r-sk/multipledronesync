import usocket as socket
from machine import UART,Pin
from utime import sleep_ms


# GPIOs :
D1 = 5
D2 = 4
D3 = 0
D4 = 2   #TX1
D5 = 14
D6 = 12
D7 = 13
D8 = 15

mode = Pin(D1, Pin.IN, Pin.PULL_UP)
exit = Pin(D2, Pin.IN, Pin.PULL_UP)

status = Pin(D3, Pin.OUT)
status.off()

# Web Socket :
host = '192.168.1.102'  #IP of laptop as a HOST
port = 12345
c = socket.socket()
c.connect((host,port))

# UART Communication :
naze = UART(0, 9600)
naze.init(9600, bits=8, parity=None, stop=1)

while mode.value() == 1:
    status.on()
    sleep_ms(100)
    status.off()
    sleep_ms(100)

status.on()

msg = 'i am happy'
while exit.value() == 1:


    naze.write('$M<')
    
    c.send(msg.encode())
    sleep_ms(1000)

    #msg = c.recv(1024)
    #print('Server : ' , msg.decode() )


status.off()
exit_msg = 'client 1 offline'
c.send(exit_msg.encode())
c.close()
