"""
The server program supports three message types
including dentification, Authentication and data
message.
python server.py Host Port
python server.py 127.0.0.1 50005
@author Shaohu Zhang

"""

import socket
import sys
import json
from time import gmtime, strftime


# HOST = "127.0.0.1"     # Host
# PORT = 49996           # non-privileged port
HOST = sys.argv[1]
PORT = int(sys.argv[2])


def verify_user(id, data):
    """
    verify the exsting user ID stored in the json file

    :param user ID, ID list
    :return bool, password
    """
    res = False
    pw = ''
    # Iterating through the json list
    for db in data:
        if(db['id'] == id):
            res = True
            pw = db['password']
    return res, pw


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
    s.bind((HOST, PORT))
    s.listen(1)
except OSError as msg:
    print(msg)
    s.close()
    s = None
if s is None:
    print('could not open socket')
    sys.exit(1)
conn, addr = s.accept()
# print(conn, addr)
file = 'user_database.json'
log_file = strftime("log_%d_%b_%Y_%H_%M_%S", gmtime())+'.txt'
# Opening JSON file
userFile = open(file)
logFile = open(log_file, 'a')
# returns JSON object as a dictionary
data = json.load(userFile)
with conn:
    print('Connected by', addr)
    while True:
        user_id = conn.recv(1024)
        print("Received: ", repr(user_id))
        is_user, pw = verify_user(user_id.decode(), data)
        if not is_user:
            conn.send(b'False')
            # print("The ID is not correct")
        else:
            conn.send(b' Your ID is correct')
            break
    while True:
        password = conn.recv(1024)
        print("Received: ", repr(password))
        if password.decode() != pw:
            conn.send(b'False')
        else:
            conn.send(b' Your password is correct')
            break
    with open(log_file, 'a') as f:
        while True:
            data = conn.recv(1024)
            if not data:
                break
            t = strftime("%d %b %Y %H:%M:%S", gmtime())  # global time
            logFile.write(t + ', ' + data.decode() + '\n')
            print("Log: ", data.decode())
            conn.send(data)
userFile.close()
s.close()
