# sort a list

# for testing, list maker and list tester
from random import shuffle
def make(n=100):
	ret = list(range(n))
	shuffle(ret)
	return ret
	
# for testing, timer
import time
def speed(f):
	l = make(10000)
	t0 = time.time()
	l = f(l)
	t1 = time.time()
	print(str(f) + ": " + str(t1-t0))

	
# python sort: cheat to win
def psort(l):
	# l.sort()
	# return l
	return sorted(l)

# insertion sort: sort by inserting elements in order into a new list
# easy version
def isort_ez(l):
	# create return list
	ret = []
	# while there's stuff in l
	while l != []:
		# find where min is
		ind = 0
		for i in range(len(l)):
			if l[i] < l[ind]:
				ind = i
		# pop min and add to ret
		ret.append(l.pop(ind))
	return ret
		
# short versions
def isort(l):
	return [l.pop(l.index(min(l))) for x in l]

# can also use an SNL
def isort_snl(l):
	pass
	
# heap sort: sort by inserting elements into a heap then popping from heap
def hsort_heap(l):
	pass
	
# merge sort: sort by merging
def merge(l1,l2):
	ret = []
	while l1 != [] and l2 != []:
		if l1[0] < l2[0]:
			ret.append(l1.pop(0))
		else:
			ret.append(l2.pop(0))
	return ret + l1 + l2
	
def msort_ez(l):
	if len(l) < 2:
		return l
	half = (len(l)//2)
	fore = l[:half]
	back = l[half:]
	fore = msort_ez(fore)
	back = msort_ez(back)
	return merge(fore,back)
	
def msort(l):
	if len(l) < 2:
		return l
	return merge(msort(l[:(len(l)//2)]),msort(l[(len(l)//2):]))
	
# quick sort: sort by pivoting
def qsort(l):
	# list of len 0 or 1 is sorted
	if len(l) < 2:
		return l
	# else pivot
	pivot = l[len(l)//2]
	less, more = [], []
	for i in l:
		if i < pivot:
			less.append(i)
		if i > pivot:
			more.append(i)
	less, more = qsort(less), qsort(more)
	return less + [pivot] + more
	
# swap sort, an "in place" qsort
def ssort(l):
	def swap(i,j):
		if l[i] > l[j] and i < j:
			l[i], l[j] = l[j], l[i]
		return 
	def help(i,j): # start index, end index, pivot. return when i-j sorted
		if max(i+1,j) > len(l):
			return
		if i+1 >= j: # base case
			swap(i,j)
			return
		old_i, old_j = i, j
		pivot = l[i + (j-i)//2]
		while i + 1 < j:
			while l[i] < pivot: # find a big i
				i += 1
			while l[j] >= pivot and j > i + 1: # find a little j
				j -= 1
			swap(i,j)
		help(old_i,i)
		help(i+1, old_j)
		return
	help(0,len(l)-1)
	return l
		
for i in [psort, isort, msort, qsort, ssort]:
	speed(i)
