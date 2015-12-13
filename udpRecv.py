from socket import *
import time

address = ( '169.254.5.12', 5000) #Defind who you are talking to (must match arduino IP and port)
client_socket = socket(AF_INET, SOCK_DGRAM) #Set Up the Socket
client_socket.settimeout(1) #only wait 1 second for a resonse
count=0

client_socket.sendto("start", address) #send command to arduino
while(count<100): #Main Loop
    try:
        rec_data, addr = client_socket.recvfrom(2048) #Read response from arduino
        print rec_data #Print the response from Arduino
        count+=1
    except:
        pass
client_socket.sendto("stop", address) #send command to arduino
client_socket.close()
