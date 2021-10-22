class HashTable:

	def __repr__(self):
		return "HashTable:" +  str(self.table)
		
	def __str__(self):
		return self.__repr__()

	def __init__(self):
		self.max = 4
		self.size = 0
		self.table = [None] * self.max
		
	def __getKey(self,x):
		return hash(x) % self.max
		
	def __rehash(self, m):
		# make sure m is valid
		if m <= 4:
			return
		# set new size
		self.max = m
		# save old elements
		old = self.table
		# create new table
		self.table = [None] * self.max
		self.size = 0
		# move old elements to new table
		for i in old:
			if i != None:
				self.insert(i)
		return
		
	# use linear probing
	def insert(self, x):
		# rehash if half full
		self.size = self.size + 1
		if self.size > (self.max // 2):
			self.__rehash(self.max * 2)
		loc = self.__getKey(x)
		# probe if collision
		while (self.table[loc] != None):
			loc = (loc + 1) % self.max
		# add element to table
		self.table[loc] = x
		return
		
	# use linear probing	
	def remove(self, x):
		self.size = self.size - 1
		# location of element to remove
		loc = self.__getKey(x)
		# probe if collision
		while (self.table[loc] != None and self.table[loc] != x):
			loc = (loc + 1) % self.max
		# need to fix linear probing - look for None or swap
		fix = (loc + 1) % self.max
		# need to find a None to end linear probing
		while (self.table[fix] != None):
			# may find elements that can't be placed at loc
			if (self.__getKey(self.table[fix]) > loc):
				fix = (fix + 1) % self.max
			# may find elements we need to shuffle earlier
			else:
				# in this case, fix points to an element that can be placed at loc
				self.table[loc] = self.table[fix]
				# new look again for an empty
				loc = fix
				fix = (loc + 1) % self.max
		self.table[loc] = None
		# rehash if necessary
		if self.size < (self.max // 4):
			self.__rehash(self.max // 2)
		return
				
	def contains(self, x):
		loc = self.__getKey(x)
		# probe if collision
		while (self.table[loc] != None):
			if self.table[loc] == x:
				return True
			loc = (loc + 1) % self.max
		return False
