class List:
    def __str__(self):
        return '[' + self.commaElements() + ']'
    def length(self):
        return self.lengthAcc(0)
    def sum(self):
        return self.sumAcc(0)
    def reverse(self):
        return self.revOnto(Nil())
    def eqNil(self):
        return False
    def eqCons(other, self):
        return False

class Nil(List):
    """ Represents an empty list. """
#    def __str__(self):
#        return 'Nil()'
#        return ''
    def commaElements(self):
        return ''
    def commaCons(self, s):
        return s
    def length(self):
        """ There are no elements in an empty list. """
        return 0
    def append(self, other):
        return other
    def __add__(self, other):
        return other
    def map(self, f):
        return self
    def filter(self, pred):
        return self
    def lengthAcc(self, a):
        return a
    def sumAcc(self, a):
        return a
    def revOnto(self, other):
        return other
    def eqNil(self):
        return True
    def __eq__(self, other):
        return other.eqNil()
    def zip(self, other):
        return other
#        return Nil

class Cons(List):
    """ Represents a non-empty list. """
    def __init__(self, head, tail):
        self.head = head
        self.tail = tail
#    def __str__(self):
#        return 'Cons(' + str(self.head) + ', ' + str(self.tail) + ')'
    def commaElements(self):
        return self.tail.commaCons(str(self.head))
    def commaCons(self, s):
        return s + ', ' + self.commaElements()
    def length(self):
        """ Count the elements in this list. """
        return 1 + self.tail.length()
    def append(self, other):
        return Cons(self.head, self.tail.append(other))
    def __add__(self, other):
        return Cons(self.head, self.tail.append(other))
    def map(self, f):
        return Cons(f(self.head), self.tail.map(f))
    def filter(self, pred):
        if pred(self.head):
            return Cons(self.head, self.tail.filter(pred))
        else:
            return self.tail.filter(pred)
    def lengthAcc(self, a):
        return self.tail.lengthAcc(1+a)
    def sumAcc(self, a):
        return self.tail.sumAcc(a + self.head) # Solution
    def revOnto(self, other):
        return self.tail.revOnto(Cons(self.head, other)) # Solution
    def eqCons(other, self):
        return self.head==other.head and self.tail==other.tail
    def __eq__(self, other):
        return other.eqCons(self)
    def zip(self, other):
        return self
#        return '(' + str(self.head) + ', ' + str(other.head) + ')'
#        return '(' + str(self.head) + ', ' + str(other.tail) + ')'
#        return Cons(self.head,  self.tail.zip(other))
#        return self.head.zip(other.head)

alist = Cons(1, Cons(2, Cons(3, Nil())))
blist = Cons(4, Cons(5, Cons(6, Cons(7, Nil()))))
clist = Nil()

print("\n")
#print("alist = " + alist)
print(alist)
#print(alist.length())
print(blist)
#print(blist.length())
print(clist)
#print(clist.length())
print("\n=====\n")

def nums(lo, hi):
    return Cons(lo, nums(lo+1, hi)) if lo < hi else Nil()

#print(nums(0,5))

#def powers2(n):
#    def loop(a, i):
#        return Cons(a, loop(2*a, i-1)) if i>0 else Nil()
#    return loop(1, n)

#print(powers2(6))

#print(alist.append(blist))
#print(blist.append(alist))
#print(clist.append(alist))
#print(clist.append(blist))

#print(alist + blist)
#print(blist + alist)
#print(clist + alist)
#print(clist + blist)

#--------
# STEP 6:

#def square(x):
#    return x * x

#print(alist.map(square))
#print(blist.map(square))
#print(clist.map(square))
#print(alist.map(lambda x: x+1))

#def isEven(x):
#    return (x % 2) == 0

#print(alist.filter(isEven))
#print(blist.filter(isEven))
#print(clist.filter(isEven))
#print(alist.filter(lambda x: not(isEven(x))))

#--------
# STEP 7:

#print(alist.lengthAcc(0))
#print(blist.lengthAcc(0))
#print(clist.lengthAcc(0))

#print(alist.sumAcc(1))
#print(blist.sumAcc(2))
#print(clist.sumAcc(3))

#print(alist.revOnto(blist))
#print(clist.revOnto(alist))
#print(alist.revOnto(clist))

#--------
# STEP 8:

#print(alist.length())
#print(blist.length())
#print(clist.length())

#print(alist.sum())
#print(blist.sum())
#print(clist.sum())

#print(alist.reverse())
#print(blist.reverse())
#print(clist.reverse())

#--------
# STEP 10:

#print(alist == alist)
#print(alist == blist)
#print(alist == clist)
#print(clist == clist)

#--------
# STEP 10:

print(nums(0,6).zip(nums(1,7)))
print(nums(0,6).zip(nums(0,3)))
print(nums(0,3).zip(nums(0,6)))

print("\n")
