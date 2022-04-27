"""
The client program supports three message types
including dentification, Authentication  and data
message.
python client.py Host Port
python client.py 127.0.0.1 50005
@author Shaohu Zhang

"""
import socket
import sys

# HOST = "127.0.0.1"    # remote host
# PORT = 49996          # same port as used by the server
HOST = sys.argv[1]
PORT = int(sys.argv[2])
s = None
false = b'False'

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
with s:
    s.connect((HOST, PORT))
    while True:
        print("Please enter your ID:")
        ID = input().encode()
        s.sendall(ID)
        data = s.recv(1024)
        print('Received', repr(data))
        if data == false:
            print("Your ID is not correct!")
        else:
            break
    while True:
        print("Enter your user password:")
        PW = input().encode()
        s.sendall(PW)
        data = s.recv(1024)
        print('Received ', repr(data))
        if data == false:
            print("Your password is not correct!")
        else:
            break
    while True:
        print("Please type your message(type <exit> to stop):")
        msgs = input()
        if msgs != 'exit':
            s.sendall(msgs.encode())
            data = s.recv(1024)
            print('Server received', repr(data))
        else:
            break

