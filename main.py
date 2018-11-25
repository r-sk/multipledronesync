from machine import UART,Pin
import time

size = 16
idd = 200
thro1 = 220
thro2 = 5
roll1 = 120
roll2 = 05
pitch1 = 220
pitch2 = 05
yaw1 = 176
yaw2 = 04
auz = 0
crc = 17

D2 = 4

exit = Pin(D2, Pin.IN, Pin.PULL_UP)

naze = UART(0, 9600)  # use uart2 i.e tx2 and rx2 for commununication
naze.init(9600, bits=8, parity=None, stop=1)

while exit.value() == 1:
    naze.write('$M<')
    naze.write(chr(64))
    print(chr(65))
    #naze.wrire(200)

    #naze.write(str(unichr(size)))
    '''
    naze.write(idd)
  
    naze.write(thro1)
    naze.write(thro2)
    
    naze.write(roll1)
    naze.write(roll2)

    naze.write(pitch1)
    naze.write(pitch2)
    
    naze.write(yaw1)
    naze.write(yaw2)
    
    naze.write(aux)
    naze.write(aux)
    
    naze.write(aux)
    naze.write(aux)
    
    naze.write(aux)
    naze.write(aux)
    
    naze.write(aux)
    naze.write(aux)
    
    naze.write(crc)
    '''

    #print('data perhaps sent!! ')

    time.sleep_ms(500)

print('Program terminating')
naze.deinit()

