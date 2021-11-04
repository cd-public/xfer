class Heap:

	def __init__(self, ins=None):
		self.arr = [None]
		if ins != None:
			for n in ins:
				self.insert(n)
				
	def __swap(self, i, j):
		temp = self.arr[i]
		self.arr[i] = self.arr[j]
		self.arr[j] = temp
		return
				
	def insert(self, n):
		self.arr.append(n)
		ind = len(self.arr) - 1
		while (ind > 1):
			if self.arr[ind] < self.arr[ind//2]:
				self.__swap(ind, ind//2)
				ind = ind//2
			else:
				return
		return
	
	def pop(self):
		# two base cases
		if len(self.arr) < 3:
			if self.arr == [None]:
				return
			else:
				return self.arr.pop()
		ret = self.arr[1]
		self.arr[1] = self.arr.pop()
		ind = 1
		while (ind*2 < len(self.arr)):
			next = self.arr.index(min(self.arr[ind*2:ind*2+2]))
			if self.arr[ind] > self.arr[next]:
				self.__swap(next, ind)
				ind = next
			else:
				return ret
		return ret
		
	def toList(self):
		l = []
		while self.arr != [None]:
			l.append(self.pop())
		return l
