import socket
import pickle
import threading

count1=0
count2=0
count3=0
sum_store=[]
client_list=[]
t=[]
link_client=0
data_send=[]

sume=0
n= int(input("Enteer number of minions "))
s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostname(),1504))
s.listen(n+1)

def distribute():
	global count1
	global count2
	global data_send
	global client_list
	k=int(len(client_list)/n)
	l=len(client_list)%n
	
	   
	for i in range(n):
		minions_list=[]
		count1+=1
		if count1<=l:
			for j in range(k+1):
				minions_list.append(client_list[count2+j])
			count2+=k+1
		if count1>l and count1<=n:
			for j in range(k):
				minions_list.append(client_list[count2+j])
			count2+=k
		data_send.append(pickle.dumps(minions_list))
	print(len(data_send))
	print(3)		


def connect(count3):
	global link_client	
	global client_list
	global data_send
	
	link, adr=s.accept()
	msg=int(pickle.loads(link.recv(5)))
	if msg==0:
		print(1)
		while True:	
			if len(data_send)==n:
				print(2)
				minions(count3,data_send[count3],link)
				break
	if msg==1:
		link_client=link
		client_list=pickle.loads(link.recv(4000))
		distribute()

def minions(i,bytes,link):
	
	global sum_store
	print(pickle.loads(bytes))
	link.send(bytes)
	sum_store.append(int(pickle.loads(link.recv(4000))))

def sum_taker():
	sume=0
	for t in range(len(sum_store)):
		sume=sume+sum_store[t]
	print(sume)
	final_bytes=pickle.dumps(sume)
	link_client.send(final_bytes)


for i in range(n+1):
	t.append(threading.Thread(target=connect, args=(count3,)))
	print(5)
	t[i].start()
	count3+=1
for i in range(n+1):
	print(6)
	t[i].join()

sum_taker()	