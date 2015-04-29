#!/usr/bin/env python
import socket
host="localhost"
port=10000
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((host,port))
while True:
    sendstr=raw_input("input send string\n")
    if sendstr == "C":
        break
    s.send(sendstr)
    rec=s.recv(4096)
    print "recieve data: %s\n" % rec
s.close()
