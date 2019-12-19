import pic

class Prop:
  pass

class TRUE(Prop):
  def __str__(self):
    return 'TRUE'
  def apic(self):
    return pic.apic('TRUE')
  def vars(self):
    return ''
  def eval(self):
    return True
  def __eq__(self, other):
    return other == True

class FALSE(Prop):
  def __str__(self):
    return 'FALSE'
  def apic(self):
    return pic.apic('FALSE')
  def vars(self):
    return ''
  def eval(self):
    return False
  def __eq__(self, other):
    return other == False

class VAR(Prop):
  def __init__(self, name):
    self.name = name
  def __str__(self):
    return self.name
  def apic(self):
    return pic.apic(self.name)
  def vars(self):
    vs = []
    vs.append(self.name)
    return vs
  def eval(self, env):
    return env[self.name]
  def __eq__(self, other):
      return self.name == other.name

class AND(Prop):
  def __init__(self, p, q):
    self.p = p
    self.q = q
  def __str__(self):
    return 'AND ' + str(self.p) + ' ' + str(self.q)
  def apic(self):
    return self.p.apic().binaryNode('AND', self.q.apic())
  def vars(self):
    return self.p.vars() + self.q.vars()
  def eval(self, env):
    return self.p.eval(env) and self.q.eval(env)
  def __eq__(self, other):
    return self.p == other.p

class OR(Prop):
  def __init__(self, p, q):
    self.p = p
    self.q = q
  def __str__(self):
    return 'OR ' + str(self.p) + ' ' + str(self.q)
  def apic(self):
    return self.p.apic().binaryNode('OR', self.q.apic())
  def vars(self):
    return self.p.vars() + self.q.vars()
  def eval(self, env):
    return self.p.eval(env) or self.q.eval(env)
  def __eq__(self, other):
    return self.p == other.p

class NOT(Prop):
  def __init__(self, p):
    self.p  = p
  def __str__(self):
    return 'NOT ' + str(self.p)
  def apic(self):
    return self.p.apic().unaryNode('NOT')
  def vars(self):
    return self.p.vars()
  def eval(self, env):
    return not self.p.eval(env)
  def __eq__(self, other):
#    return self.p == other.p
    return self.p == other.eval

# The next section of code constructs some Prop abstract
# syntax trees ...
t       = TRUE()
f       = FALSE()
a       = VAR("A")
b       = VAR("B")
c       = NOT(a)
d       = NOT(b)
left    = AND(a, NOT(b))
right   = AND(NOT(a), b)
example = OR(left, right)

#print(t)
#print(f)
#print(a)
#print(b)
#print(c)
#print(d)
#print(left)
#print(right)
#print(example)

#print('\n')

# vars test:
#print(t.vars())
#print(f.vars())
#print(a.vars())
#print(b.vars())
#print(c.vars())
#print(d.vars())
#print(left.vars())
#print(right.vars())
#print(example.vars())

# eval tests:
#print(t.eval())
#print(f.eval())
#print(a.eval({'A': True, 'B': False}))
#print(b.eval({'A': True, 'B': False}))
#print(c.eval({'A': True, 'B': False}))
#print(d.eval({'A': True, 'B': False}))
#print(left.eval({'A': True, 'B': False}))
#print(right.eval({'A': True, 'B': False}))
#print(example.eval({'A': True, 'B': False}))

# The following should print True ... but you'll need to
# make some changes to the code before it works properly.
# Working:
print(TRUE() == TRUE())
print(TRUE() == FALSE())
print(FALSE() == FALSE())
print(FALSE() == TRUE())
print(VAR("A") == VAR("A"))
print(VAR("A") == VAR("B"))
print(VAR("B") == VAR("B"))
print(NOT(TRUE()) == NOT(TRUE()))
print(NOT(TRUE()) == NOT(FALSE()))
print(NOT(FALSE()) == NOT(FALSE()))
print(NOT(FALSE()) == NOT(TRUE()))
print(AND(VAR("A"), VAR("B")) == AND(VAR("A"), VAR("B")))
print(AND(VAR("A"), VAR("B")) == AND(VAR("B"), VAR("A")))
print(example == example)
print(left == left)
print(right == right)

# Not working:
print(NOT(TRUE()) == FALSE())
#print(example == right)
#print(left == right)
#print(right == left)

# Print out the example expression in text and tree forms:
#print(example)
#print(example.apic())

# ... and then puts some of them together in a list:
list = [TRUE(), TRUE(), left, right, OR(left, right), example]

# Here is a function that you can use for testing.  It takes a list
# of Prop values as inputs, and then displays (a) some diagrams
# showing the structure of each of the expressions; and (b) a table
# that shows the results of comparing each of the Prop values in
# the list against all of the other items.
def eqTests(list):
  # Construct and print a picture of all the trees in list:  (You are
  # not expected to understand exactly how this part of the code works)
  pics = pic.hstrut(0)
  for p in list:
    pics = pics.top(pic.hstrut(3).top(p.apic().pic))
  print(pics)
  # Compare the examples in the given list with one another and display
  # the results in a simple table:
  for l in list:
    for r in list:
      print('Y' if l==r else '-', end='\t')
    print(l)

# Run some tests:
#eqTests(list)
