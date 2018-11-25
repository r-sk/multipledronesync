import socket
import sys
from time import sleep

s = socket.socket()

host = ''
port = 12345

try:
    s.bind((host, port))
except socket.error as e:
    print(str(e))
    print('Program Terminated !')
    sys.exit(1)

print('Server Started!!! Listening on port ', port)

s.listen(1)

c,c_addr = s.accept()
print(c_addr, 'online')

while True:
    #msg = c.recv(50)

    # if msg.decode() == 'client 1 offline':
    #     c.close()
    #     print('Client ko last msg : ', msg.decode() )
    #     break


    
    #print( msg.decode() )

    # sleep(0.1)

    # reply = '1100,1200,1300,1400,1500,1600,1700,1800\n'

    # c.send(reply.encode())


    cmd = input('>>')
    c.send( cmd.encode() )




print('Program terminated !!! ')

