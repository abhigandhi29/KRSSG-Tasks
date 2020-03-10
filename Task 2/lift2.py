import time
import threading
import socket
import pickle

#liftloc1=[]
#liftloc2=[]

class Person():

	def __init__(self):
		self.pick=[]
		self.drop=[]
		self.dir=[]

	def pickup(self,n):
		self.pick.append(n)

	def droploc(self,n):
		self.drop.append(n)

	def direc(self,n):
		self.dir.append(n)

	def removele(self,i):
		p.pick.pop(i)
		p.drop.pop(i)
		p.dir.pop(i)			
		
p=Person()
#count3=-1
#print("Enter 1 when entering the elements is over\n")
s= socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((socket.gethostname(),1507))
s.listen(5)
link, adr=s.accept()
def part1():
	while True:
		print('infinity')
		#m=input("Enter elements one by one ")
		global link
		
		m=(pickle.loads(link.recv(4000)))
		if m[0]!='-':	
			p.pickup(int(m[0]))
			if m[2]!='-':
				p.droploc(int(m[2]))
			else :
				p.droploc((-1)*int(m[3]))	
			p.direc(m[1])
		else:
			p.pickup((-1)*int(m[1]))
			if m[3]!='-':
				p.droploc(int(m[3]))
			else :
				p.droploc((-1)*int(m[4]))	
			p.direc(m[2])
		print(p.pick)
		print(p.dir)
		print(p.drop)
def part2():
	class Lift():

		def __init__(self,di):
			self.current_state=0
			self.drop1=[]
			self.direction=di
			self.final_list=[]

		def currentstate(self,n):
			self.current_state=n

		def bestpickup(self):
			value1=10000
			value2=-10000
			count=-1
			if len(p.pick)==0:
				if self.direction=='u':
					return [10000,-1]
				if self.direction=='d':
					return [-10000,-1]		
			else:
				if self.direction=='u':
					for i in range(len(p.pick)):
						if p.pick[i]>=self.current_state-1 and value1>p.pick[i]:
							value1=p.pick[i]
							count=i
					return [value1,count]
				if self.direction=='d':
					for i in range(len(p.pick)):
						if p.pick[i]<=self.current_state+1 and value2<p.pick[i]:
							value2=p.pick[i]
							count=i
					return [value2,count]	

		def bestdrop(self):	

			value1=10000
			value2=-10000
			count=-1
			if len(self.drop1)==0:
				if self.direction=='u':
					return [10000,-1]
				if self.direction=='d':
					return [-10000,-1]			
			else:
				if self.direction=='u':
					for i in range(len(self.drop1)):
						if self.drop1[i]>=self.current_state-1 and value1>self.drop1[i]:
							value1=self.drop1[i]
							count=i
					return [value1,count]
				if self.direction=='d':
					for i in range(len(self.drop1)):
						if self.drop1[i]<=self.current_state+1 and value2<self.drop1[i]:
							value2=self.drop1[i]
							count=i
					return [value2,count]			

		def changedirection(self):
			#print("changing")
			if self.direction=='u':	
				self.direction='d'
			else:
				self.direction='u'			

	class System():

		def __init__(self):
			
			
			lift1=Lift('u')
			lift2=Lift('d')
			t1=threading.Thread(target=self.moves, args=(lift1,1))
			t1.start()	
			time.sleep(0.25)					
			t2=threading.Thread(target=self.moves, args=(lift2,2))
			t2.start()
			t1.join()
			t2.join()

		def moves(self,lift,liftid):
			
			
			loclift=[0]
			while True:
				print("{} and {} and {} and {}".format(len(p.pick),len(lift.drop1),p.pick,lift.drop1))
				
				if(len(p.pick)==0 and len(lift.drop1)==0):
					#print(2)
					if liftid==1:
						print("For lift1:")
						for i in range(len(loclift)-1):
							print("{}-->".format(loclift[i]) ,end=' ')
						if len(loclift)>0:	
							print("{}\n".format(loclift[len(loclift)-1]) ,end=' ')
					if liftid==2:
						print("For lift2:")	
						for i in range(len(loclift)-1):
							print("{}-->".format(loclift[i]) ,end=' ')
						if len(loclift)>0:		
							print("{}\n".format(loclift[len(loclift)-1]) ,end=' ')	
					time.sleep(1)
				else:				

					chance1=lift.bestpickup()
					chance2=lift.bestdrop()
					chance3=lift.direction
					print(chance1)
					print(chance2)
					print(chance3)
					if chance3=='u':
						#print("in it")
						if chance1[0]<chance2[0]:
							lift.drop1.append(p.drop[chance1[1]])
							lift.currentstate(chance1[0])
							loclift.append(chance1[0])
							p.removele(chance1[1])
						if chance1[0]>chance2[0]:
							lift.currentstate(chance2[0])
							lift.drop1.pop(chance2[1])
							loclift.append(chance2[0])
						if chance1[0]==chance2[0] and chance1[0]==10000:
							lift.changedirection()
						if chance1[0]==chance2[0] and chance1[0]!=10000:
							lift.drop1.append(p.drop[chance1[1]])
							lift.currentstate(chance1[0])
							loclift.append(chance1[0])
							p.removele(chance1[1])
							lift.drop1.pop(chance2[1])
							

					if chance3=='d':
						if chance1[0]>chance2[0]:
							lift.drop1.append(p.drop[chance1[1]])
							
							loclift.append(chance1[0])
							p.removele(chance1[1])
							time.sleep(0.5*abs(lift.current_state-chance1[0]))
							lift.currentstate(chance1[0])
						if chance1[0]<chance2[0]:
							
							lift.drop1.pop(chance2[1])
							loclift.append(chance2[0])
							time.sleep(0.5*abs(lift.current_state-chance2[0]))
							lift.currentstate(chance2[0])
						if chance1[0]==chance2[0] and chance1[0]==-10000:
							lift.changedirection()
						if chance1[0]==chance2[0] and chance1[0]!=-10000:
							lift.drop1.append(p.drop[chance1[1]])
							
							loclift.append(chance1[0])
							p.removele(chance1[1])
							lift.drop1.pop(chance2[1])
							time.sleep(0.5*abs(lift.current_state-chance1[0]))
							lift.currentstate(chance1[0])
					print(loclift)
		



	system1=System()

t3=threading.Thread(target=part1, args=())
t3.start()						
t4=threading.Thread(target=part2, args=())
t4.start()	
	
