#!/usr/bin/python
# UDP Echo Server -  udpserver.py
# code by www.cppblog.com/jerryma
import socket, traceback
import time 
import fcntl
import struct

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(
        s.fileno(),
        0x8915,  # SIOCGIFADDR
        struct.pack('256s', ifname[:15])
    )[20:24])

host = ''
port = 10002
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))
while True:
        message, address = s.recvfrom(8192)
	ip = get_ip_address('wlan0')
 	s.sendto("Hi I'm Pi My Addr is "+ip,address)
	#print ("HI"+ip)
        #print ("Got data from", address, ": ", message)
        #s.sendto(message, address)
