#!/usr/bin/env python
import socket
from binascii import hexlify, unhexlify
host="localhost"
# host="10.238.70.221"
port=10000
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind((host,port))
s.listen(5)
sock,addr=s.accept()
print "got connection form ",sock.getpeername()
while 1:
    data=sock.recv(1024)
    if not data:
        break
    else:
        respmsg = hexlify(data)
        print respmsg
        sock.send("server send data: %s" % respmsg)
