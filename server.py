import socket       #or "from socket import * " this will import each and every function from socket so we donot need to use "soket.****" to excess them but creates lots of warnings of unused imported functions
import sys

#host_ip = socket.gethostname()
#print(host_ip)
#print(socket.gethostbyname(host_ip))

host_ip = '' #Blank is the Symbolic name meaning all available interfaces
port = 8000 #reserves port 8000 for localhost communication with this program. Can be any number except some pre-reserved ports like 80(for HTTP)

server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)   #This creates a server socket with default parameters i.e iPv4 and TCP connection

#server.setblocking(0)
#server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

try:
    server.bind((host_ip, port)) #binds the server to a socket(host_ip + port) so that it can communicate with other sockets through this sock
except socket.error as e:       #above function actually takes single argument which is a tuple of host_ip and port number
    print(str(e))
    print('Terminating program...')
    sys.exit(1) #exit code 1 = some error occoured so program terminated, 0 = sucessful termination of program with no error

server.listen(5)    #specifies how many clients it can handle at a time represented by argument passed to it

conn, addr = server.accept()    #accepts the client connection. This step waits(pauses program) until a client is connected to the server socket
#accept returns a tuple with two data, first one is cient socket which is used to communicate with the client and another one is client address
print(addr, 'connected')


while True:


    data = conn.recv(1024)
    print('Received : ', data.decode() )

    reply = input('Reply: ')
    conn.send(reply.encode())



conn.close()  #close the connection with client
