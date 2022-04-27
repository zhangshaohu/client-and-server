# Introduction 

This assignment has two versions of server program including a c and a python application.
Python code was checked by the flake8 and c code was checked by cppcheck linter.

The ID and password of three users ware pre-stored in user_database.json file. 
The password could be encrypted but I didn't implement it. The message will be 
logged in a generated text file. e.g., log_24_Apr_2022_22_48_42.txt.

Once the server program is running, the client will ask you input your 
identifier (i.e., fireeye) and the server will check the identifier enrolled 
in the database. If you put wrong  identifier, it will keep asking your correct one. 
The password (i.e., 12345) input  has same design flow as the identifier input. 
The message will be logged as soon as you input correct identifier and password.

This assignment has been tested in both Ubuntu 18.04.6 LTS and Windows 10. There is no
need to install extral libraries if Python 3 and gcc compiler were installed. 

## Run

User identifier: fireeye

Password: 12345



### Python program 

If you implement both client and server in a local computer, you may open one 
terminal and implement it.
 
python server.py <host> <port>

for example

python server.py 127.0.0.1 50003

Open another terminal in the same computer:

python client.py <host> <port>

python client.py 127.0.0.1 50003


You may run different computer using the server's IP address, for example,

python client.py 10.132.8.204 50003


 


### C program 

The c progrom is its simple version with the fixed local host (127.0.0.1) 
and port number(50003). The program use defaut user identifier(fireeye)
and password (12345). The message will be logged in the log.txt file.
You may run the server application as: 

gcc server.c -o server

./server

Open another terminal in the same computer:

python client.py 127.0.0.1 50003

### Output

#### The client teminal would look like
 
Please enter your ID:

123

Received b'False'

Your ID is not correct!

Please enter your ID:

fireeye

Received b' Your ID is correct'

Enter your user password:

test

Received  b'False'

Your password is not correct!

Enter your user password:

12345

Received  b' Your password is correct'

Please type your message(type <exit> to stop):

Hello!

Server received b'Hello!'

Please type your message(type <exit> to stop):

How are you?

Server received b'How are you?'

Please type your message(type <exit> to stop):

exit

#### The server terminal would look like

Received:  b'123'

Received:  b'fireeye'

Received:  b'test'

Received:  b'12345'

Log:  Hello!

Log:  How are you?



