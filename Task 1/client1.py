import socket
import pickle

n= int(input ("Number of elements in list: "))
client_list=[]
for i in range(n):
	client_list.append(input("Enter the list one by one: "))
s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((socket.gethostname(),1504))
list_bytes=pickle.dumps(1)
s.send(list_bytes)
list_bytes=pickle.dumps(client_list)
s.send(list_bytes)


print(pickle.loads(s.recv(4000)))  	
