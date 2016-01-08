import string
import random

def id_generator():
	return ''.join(random.choice(string.ascii_lowercase) for _ in range(5))

N = input()
Ages = {}
for i in range(N):
	s = id_generator()
	if s in Ages:
		continue
	Ages[s] = random.randint(1,100)

print len(Ages)
