# provided, could be named "BST", feel free to edit
class node:

	# provided, feel free to edit
	def __repr__(self):
		lstr = ""
		mstr = ""
		if self.kids[0] != None:
			lstr = "(" + self.kids[0].__repr__() + ") <- "
		if self.kids[1] != None:
			mstr = " -> (" + self.kids[1].__repr__() + ")"
		return lstr + str(self.data) + mstr
	
	# provided, feel free to edit
	def __str__(self):
		return self.__repr__()

	# provided, feel free to edit
	def __init__(self, d):
		self.data = d # piece of data (not None)
		self.kids = [None, None]
		
	# calculate size of the BST - the number of elements it contains
	# * always greater than zero
	def size(self):
		return 1 + sum([k.size() for k in filter(None, self.kids)])
			
	# calculate size of the BST - the number of elements in the longest single path
	# * always greater than zero	
	def depth(self):
		return 1 + max([0] + [k.depth() for k in filter(None, self.kids)])
	
	# finds where d should be, helper for insert/contains
	def traverse(self, d):
		if d != self.data and self.kids[int(d > self.data)]: # if not d and appropriate child exists...
				return self.kids[int(d > self.data)].traverse(d) # recurse on appropriate child
		return self
	
	# given d, return the BST containing all elements in the BST and also d
	# * may ignore the case of duplicates, like adding "2" twice
	# * may assume added elements are of comparable types
	def insert(self, d):
		self.traverse(d).kids[int(d > self.traverse(d).data)] = node(d) # find relevant site then insert
		# return value handled by wrapper

	# given d, return true if d is in the BST, return false otherwise
	# * may assume added elements are of comparable types		
	def contains(self, d):
		return self.traverse(d).data == d # find relevant site then check if d is there
		
	# helper for min/max	
	def getX(self, ind):
		if self.kids[ind]:
			return self.kids[ind].getX(ind)
		return self.data
		
	# return the minimum value in the bst
	def getMin(self):
		return self.getX(0)
	
	# return the maximum value in the bst
	def getMax(self):
		return self.getX(1)
		
	def remove(self, d):
		if not self.kids[0] and d == self.data: 		# 0, R child cases
			return self.kids[1]
		elif d == self.data:							# L, 2 child cases
			d = self.data = self.kids[0].getX(1)
		self.kids[int(d > self.data)] = self.kids[int(d > self.data)].remove(d)
		return self
		
# provided as a curiousity, an outer class to wrap node and allow BSTs to be of size zero
# feel free to edit
class BST:
	
	def __repr__(self):
		return "BST: " + self.node.__repr__()
	
	def __str__(self):
		return "BST: " + self.node.__str__()

	def __init__(self, d=None):
		if d == None:
			self.node = None # always a node or None
		else:
			self.node = node(d) # always a node or None
		
	def size(self):
		if self.node == None:
			return 0
		return self.node.size()
	
	def depth(self):
		if self.node == None:
			return 0
		return self.node.depth()
	
	# this returns self for the autograder as a convenience
	def insert(self, d):
		if self.node == None:
			self.node = node(d)
		else:
			self.node.insert(d)
		return self
		
	def contains(self, d):
		if self.node == None:
			return False
		return self.node.contains(d)
	
	# returns None if the BST contains no min
	def getMin(self):
		if self.node == None:
			return
		return self.node.getMin()
	
	# returns None if the BST contains no max
	def getMax(self):
		if self.node == None:
			return
		return self.node.getMax()
	
	# this returns self for the autograder as a convenience
	def remove(self, d):
		if self.node == None:
			return
		self.node = self.node.remove(d)
		return self
