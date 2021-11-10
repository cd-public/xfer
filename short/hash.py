# hash.py

class HashTable:

    def __init__(self):
        self.t = [set() for n in range(4)]
        
    def insert(self,arg):
        self.t[hash(arg)%len(self.t)].add(arg)
        if sum([len(l) for l in self.t]) > len(self.t) // 2:
            f = [n for l in self.t for n in l]
            self.t = [set() for n in range(len(self.t) * 2)]
            for n in f:
                self.insert(n)
                
    def remove(self,arg):
        self.t[hash(arg)%len(self.t)].discard(arg)
        if sum([len(l) for l in self.t]) < len(self.t) // 2:
            f = [n for l in self.t for n in l]
            self.t = [set() for n in range(len(self.t) // 2)]
            for n in f:
                self.insert(n)
                
    def contains(self,arg):
        return arg in self.t[hash(arg)%len(self.t)]
