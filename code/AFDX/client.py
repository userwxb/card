#!/usr/bin/env python
import socket
from binascii import hexlify, unhexlify
respmsg = '80cc00070000000081000001460200c83a02c0003b02c001510200014e0400000001'
respmsg = unhexlify(respmsg)

host="localhost"
# host="10.238.70.221"
port=10000
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((host,port))
while True:
    sendstr=raw_input("input send string\n")
    if sendstr == "C":
        break
    s.send(respmsg)
    rec=s.recv(4096)
    print "recieve data: %s\n" % rec
s.close()


