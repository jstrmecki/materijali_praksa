import random
import time
import itertools
A = []
n = int(float(input()))
for i in range(n):
       A.append(int(float(input())))
x = int(float(input()))
N = [0 for i in range(n)]
count = 0
i = 0
start_time = 0
def random_search():
    global start_time
    global count
    start_time = time.time()
    while count < n:
        i = random.randint(0,n-1)
        if A[i] == x:
            return i
        if N[i] == 0:
            N[i] = 1
            count += 1
    return False
random_search()
elapsed_time = time.time() - start_time
print(elapsed_time)
start_time = 0

def deterministic_search():
    global start_time
    start_time = time.time()
    for i in range(n):
        if A[i] == x:
            return i
    return False
deterministic_search()
elapsed_time = time.time() - start_time
print(elapsed_time)

start_time = 0

def permute_search():
    global start_time
    start_time = time.time()
    random.shuffle(A,random.random)
    for i in range(n):
        if A[i] == x:
            return i
    return False

permute_search()
elapsed_time = time.time() - start_time
print(elapsed_time)