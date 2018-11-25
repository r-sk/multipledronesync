import socket       #or "from socket import * " this will import each and every function from socket so we donot need to use "soket.****" to excess them but creates lots of warnings of unused imported functions

host_ip = '' #can be left blank as it knows ip of itself
port = 8000 #communicate to server via port 8000

client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)   #This creates a client socket with default parameters i.e iPv4 and TCP connection

#client.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

client.connect((host_ip, port)) #connect the client to a server socket
#above function actually takes single argument which is a tuple of host_ip and port number

while True:
    message = input('Your message: ')
    #client.send(str(message))

    client.send(message.encode())

    print('waiting reply...')

    reply = client.recv(1024)
    print('Received: ' , reply.decode() )

client.close()

