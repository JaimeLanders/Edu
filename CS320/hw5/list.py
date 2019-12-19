class List:
    def __str__(self):
        return '[' + self.commaElements() + ']'

class Nil(List):
    """ Represents an empty list. """
    def commaElements(self):
        return ''
    def commaCons(self, s):
        return s
    def zipNil(self, other):
#        print("Nil().zipNil\n") # DEBUG
        return Nil()
        print("Nil().zipNil\n") # DEBUG
    def zip(self, other):
#        print("Nil().zip\n") # DEBUG
        return Nil()
#        return self

class Cons(List):
    """ Represents a non-empty list. """
    def __init__(self, head, tail):
        self.head = head
        self.tail = tail
    def commaElements(self):
        return self.tail.commaCons(str(self.head))
    def commaCons(self, s):
        return s + ', ' + self.commaElements()
    def zipNil(other, self):
#        print("Cons().zipNil\n") # DEBUG
        return Cons((self.head, other.head), self.tail.zip(other.tail))
    def zip(self, other):
#        print("Cons().zip\n") # DEBUG
        return other.zipNil(self)

def nums(lo, hi):
    return Cons(lo, nums(lo+1, hi)) if lo < hi else Nil()

#print(nums(0,5))

print(nums(0,0).zip(nums(1,7))) # Case 1: Self is Nil
print(nums(0,6).zip(nums(0,0))) # Case 2a: Other is Nil
print(nums(0,6).zip(nums(1,7))) # Case 2b: Neither is Nil
print(nums(0,6).zip(nums(0,3)))
print(nums(0,3).zip(nums(0,6)))

print("\n")
