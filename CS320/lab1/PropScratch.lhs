-----------------------------------------------------------

> module PropScratch where
> import Pic
> import Prop
> import Data.List

You can add definitions here as you experiment with Prop.

> a = VAR "A"
> b = VAR "B"
> c = VAR "C"
> d = VAR "D"
> ex0 = AND a b
> ex1 = OR a b
> ex2 = AND a (NOT b)
> ex3 = AND (NOT a) b
> ex4 = OR ex2 ex3 
> ex5 = AND (OR a b) (OR c d)  
> ex6 = AND (AND a b) (AND c d)  

-----

Lab 1:

> answer = OR (NOT a) (AND silly bczero)   
> rest = FALSE   
> bczero = AND (NOT b) (NOT c)
> silly = OR d TRUE

An example Prop value using the abstract syntax constructors:

> exp0 = OR (AND (NOT (VAR "A")) (VAR "B"))
>           (AND (VAR "A") (VAR "B"))

-----
Homework 1:

Question 2a:

> exp1 = AND (VAR "A") (VAR "B")
> exp2 = AND (VAR "A") (NOT (VAR "B"))
> exp3 = AND (NOT (VAR "A")) (VAR "B")
> exp4 = AND (NOT (VAR "A")) (NOT (VAR "B"))
> exp5 = AND (NOT (OR (VAR "A") (VAR "B"))) (OR (VAR "A") (VAR "B"))
> exp6 = OR (VAR "A") (VAR "B")
> exp7 = OR (VAR "A") (NOT (VAR "B"))
> exp8 = OR (NOT(VAR "A")) (VAR "B")
> exp9 = OR (NOT(VAR "A")) (NOT (VAR "B"))
> exp10 = OR (NOT (OR (VAR "A") (VAR "B"))) (OR (VAR "A") (VAR "B"))
> exp11 = OR (VAR "A") (AND (VAR "A") (VAR "B"))
> exp12 = NOT(OR (VAR "A") (AND (VAR "A") (VAR "B")))
> exp13 = AND (OR (VAR "A") (VAR "B")) (VAR "B")
> exp14 = NOT (AND (OR (VAR "A") (VAR "B")) (VAR "B"))
> exp15 = NOT (AND (NOT (AND (VAR "A") (NOT (AND (VAR "A") (VAR "B"))))) (NOT (AND (NOT (AND (VAR "A") (VAR "B"))) (VAR "B"))))
> exp16 = AND (NOT (AND (VAR "A") (NOT (AND (VAR "A") (VAR "B"))))) (NOT (AND (NOT (AND (VAR "A") (VAR "B"))) (VAR "B")))
> exp17 = AND (NOT (AND (VAR "B") (NOT (AND (VAR "B") (VAR "A"))))) (NOT (AND (NOT (AND (VAR "B") (VAR "A"))) (VAR "A")))

> exp2a = [exp1, exp2, exp3]

Question 3a:

--> env0 = [(a, False), (b, True)]

> env0 = [("A", False), ("B", True)]

> exp18 = AND (NOT (VAR "A")) (NOT (VAR "B"))
> exp19 = AND (AND (NOT (VAR "A")) (NOT (VAR "B"))) TRUE
> exp20 = AND (AND (NOT (VAR "A")) (NOT (VAR "B"))) (VAR "B") 
> exp21 = AND (AND (NOT (VAR "A")) (NOT (VAR "B"))) (OR (VAR "A") (VAR "B"))
> exp22 = AND (OR (VAR "A") (VAR "B")) (AND (NOT (VAR "A")) (NOT (VAR "B")))
> exp23 = AND TRUE (AND (OR (VAR "A") (VAR "B")) (AND (NOT (VAR "A")) (NOT (VAR "B"))))

-----

Some sample environments:

--> env0 = [("A", True), ("B", False)]

> env1
>  = [ ("A", True),
>      ("B", False),
>      ("C", False),
>      ("D", True) ]

Note that this is a literate file.  In particular, this
means that (1) code lines must begin with a ">" in the
first column; and (2) there must be at least one blank
line between any code line and any other line of text.

We can even add definitions that describe new ways to
build circuits:

> xor    :: Prop -> Prop -> Prop
> xor p q = OR (AND p (NOT q)) (AND (NOT p) q)

-----------------------------------------------------------
For reference, the functions that you can use include:

* AND   :: Prop -> Prop -> Prop
  OR    :: Prop -> Prop -> Prop
  NOT   :: Prop -> Prop
  TRUE  :: Prop
  FALSE :: Prop
  VAR   :: String -> Prop

  The "constructors" for the Prop type.

* vars :: Prop -> [String]

  List the variables appearing in a given Prop value.

* listProps :: [Prop] -> IO ()

  Display a list of Prop values, each one on a different
  line with a distinct line number.

* picTree  :: Prop -> Pic

  Draw the abstract syntax tree for a given Prop value.

* picTrees :: [Prop] -> Pic

  Draw the abstract syntax trees for a list of Prop values.

* truthTable :: Prop -> Pic

  Display the truth table for a given Prop value.

* truthTables :: [Prop] -> Pic

  Display the truth tables for a list of Prop values.

* eval :: Env -> Prop -> Bool

  Display the value of a given Prop value using the
  specified environment.  The environment must provide
  a value for every variable in the given Prop.

* reduce :: Env -> Prop -> [Prop]

  Display all the expressions that can be reached from
  the given Prop value in a single step.  Variables
  may be reduced using information in the environment,
  if provided, but are otherwise treated as (unknown)
  constants.

* normalize :: Env -> Prop -> [Prop]

  Attempt to calculate a normal form for a given Prop
  value, returning the list of all the steps in the
  reduction sequence.

* normalForms :: Env -> Prop -> [Prop]

  Return a list of all normal forms that can be obtained
  by changing the order in which expressions are reduced.
  Is it possible for a single expression to reduce to
  different results if you change the order of evaluation?

* props :: [String] -> [Prop]

  Return a list of all Prop values that can be constructed
  using variables whose names appear in the input list.
  This will typically produce a very long list of
  expressions (some might even say "infinite" :-) so you
  are encouraged to use this in combination with the take
  operator, as in:  take 10 (props ["A", "B"])

-----------------------------------------------------------
