def binadd (A, B):
	C = [0]*(len(A)+1)
	carry = 0
	for i in range(len(A)-1, -1, -1):
		C[i+1] = (A[i] + B[i]  + carry)%2
		if A[i] + B[i] == 2:
			carry = 1
		else:
			carry = 0
	C[0] = carry
	
	print(C)

binadd([1,0,1,0,1,0,1,0], [1,1,0,0,1,1,0,0])