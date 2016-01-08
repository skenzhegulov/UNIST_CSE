import string
import random

def id_generator():
	return ''.join(random.choice(string.ascii_lowercase) for _ in range(5))

N = input()
Names = []
Ages = []
for i in range(N):
	s = id_generator()
	if Names.count(s)>0:
		continue
	Names.append(s)
	Ages.append(random.randint(1,100))

print len(Names)
