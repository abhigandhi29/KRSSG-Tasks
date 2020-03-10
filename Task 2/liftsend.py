import socket
import pickle

s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(),1507))

while True:

	
	m= input("Enter elemnts one by one: ")
	print(m)
	bytes1=pickle.dumps(m)
	s.send(bytes1)
	