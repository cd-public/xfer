# hash.py
from operator import *

class HashTable:

    def __init__(self):
        self.t = [set() for n in range(4)]
        
    def __rehash(self, f1, f2):
        if f1(sum([len(l) for l in self.t]), len(self.t) // 2):
            f, self.t = [n for l in self.t for n in l], [set() for n in range(f2(len(self.t),2))]
            [self.insert(n) for n in f]
        
    def insert(self,arg):
        self.t[hash(arg)%len(self.t)].add(arg), self.__rehash(gt,mul)
                
    def remove(self,arg):
        self.t[hash(arg)%len(self.t)].discard(arg), self.__rehash(lt,floordiv)
                
    def contains(self,arg):
        return arg in self.t[hash(arg)%len(self.t)]
