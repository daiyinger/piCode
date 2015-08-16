from socket import *
txString ='''ss
ssssssssssssssssssssssssssssssssssssssssssssssssss
ssssssssssssssssssssssssssssssssssssssssssssssssss
ssssssssssssssssssssssssssssssssssssssssssssssssss
ssssssssssssssssssssssssssssssssssssssssssssssssss
ssssssssssssssssssssssssssssssssssssssssssssssssss
fsfsfsfsfsfsfsfsfasfssssssssssssssssssssssssssssss
asfasfasfasfasfasfasfasfasfasssssssssssssssfdfafas
ssssssssssssssssssssssssssssssssssssssssssssssssss
ssssssssssssssssssssssssssssssssssssssssssssssssss
dddddddddddddddddddddddddddssssssssssssssdddddddss'''
HOST = '192.168.1.108'
#HOST = 'localhost'
PORT = 1025
BUFSIZE = 1024
ADDR = (HOST, PORT)

tcpSocket = socket(AF_INET, SOCK_DGRAM)
#tcpSocket.connect(ADDR)

#txData = []
while True:
	#txData = range(0,512)
	#txData = array.array(' ', ' '*1024) 	
	tcpSocket.sendto(txString,ADDR)
	dataRecv = tcpSocket.recvfrom(BUFSIZE)
	if not dataRecv:
		break
	if dataRecv != txString:
		break
	#Sleep(1)
tcpSocket.close()
