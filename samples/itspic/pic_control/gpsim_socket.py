import socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 0x1234))

# helper functions
def ParseInt(buf):
    if buf[0:3] == "$03" :
        return eval("0x"+buf[3:11])

    return 0

s.send("help\n")
print s.recv(20)

s.send("$"+"f4"+"p18f6520.porte")
r = s.recv(20)
print "received:" + r + " decoded as " + str(ParseInt(r))


# String object
#s.send("$0205HELLO")
#print s.recv(20)

#s.send("portb\n")
#print s.recv(20)

# Symbol Command 
#s.send("$"+"91"+"0300000023")
#r = s.recv(20)
#print type(r)
#print "received:" + r + " decoded as " + str(ParseInt(r))

#s.send("$0105")
#print s.recv(20)

# String object
#s.send("$0205HELLO")
#print s.recv(20)


#s.send("$" + "f0" + "f81")#"p18f6520.porte")
#r = s.recv(20)
#print "received:" + r + " decoded as " + str(ParseInt(r))

s.close()
