--------------------------------------------------------------------

> module GrammarScratch where
> import GrammarToolkit

Some sample grammars:

> g0 = "A ->"
> g1 = "A -> a A ; A ->"
> g2 = "E -> num ; E -> E + E; E -> - E ; E -> ( E )"
> g3 = "P -> true ; P -> not P ; P -> and P P"
> g4 = "P -> true ; P -> false; P -> not P ; P -> P and P"
> g5 = "P -> P & N; P -> N; N -> ~ N; N -> t"
> g6 = "P -> N & P; P -> N; N -> ~ N; N -> t"
> g7 = "L -> x ; L -> L L ; L -> \\ x . L ; L -> ( L )"

A grammar for a language that is not regular:

> brackets = "B -> ; B -> [ B ]"

Lab 2:

> eg = "E -> n ; E -> E + E ; E -> E * E ; E -> ( E )"    
> eg2 = "E -> E + P; E -> P; P -> P * A; P -> A; A -> n; A -> ( E )"
> ex = "S -> if e then S else S; S -> if e then S; S -> other"

Solution:

> de = "S -> if e then S else S;" ++
>      "S -> if e then S;" ++
>      "S -> other"

Homework 2:

> e2a = "N -> number;" ++
>       "N -> number, N" 


> e2b = "B -> [ ];" ++
>       "B -> [ N ];" ++
>       "N -> number;" ++
>       "N -> number, N"

> e2c = "P ->;" ++
>       "P -> N ;" ++
>       "N -> number .;" ++
>       "N -> number . N" 

> e2d = "L ->;" ++
>       "L -> P;" ++ 
>       "P -> a;" ++ 
>       "P -> b;" ++ 
>       "P -> c;" ++ 
>       "P -> a a;" ++ 
>       "P -> b b;" ++ 
>       "P -> c c;" ++ 
>       "P -> a P a;" ++ 
>       "P -> b P b;" ++ 
>       "P -> c P c" 

       "D -> 9 D"

> e2e = "L -> A;" ++
>       "A ->;" ++
>       "A -> 0 A;" ++
>       "A -> 1 B;" ++
>       "A -> 2 C;" ++
>       "A -> 3 A;" ++
>       "A -> 4 B;" ++
>       "A -> 5 C;" ++
>       "A -> 6 A;" ++
>       "A -> 7 B;" ++
>       "A -> 8 C;" ++
>       "A -> 9 A;" ++
>       "B -> 0 B;" ++
>       "B -> 1 C;" ++
>       "B -> 2 A;" ++
>       "B -> 3 B;" ++
>       "B -> 4 C;" ++
>       "B -> 5 A;" ++
>       "B -> 6 B;" ++
>       "B -> 7 C;" ++
>       "B -> 8 A;" ++
>       "B -> 9 B;" ++
>       "C -> 0 C;" ++
>       "C -> 1 A;" ++
>       "C -> 2 B;" ++
>       "C -> 3 C;" ++
>       "C -> 4 A;" ++
>       "C -> 5 B;" ++
>       "C -> 6 C;" ++
>       "C -> 7 A;" ++
>       "C -> 8 B;" ++
>       "C -> 9 C"

> e2f = "G ->;" ++
>       "G -> P ;" ++ 
>       "G -> P | P;" ++ 
>       "P -> n => W;" ++
>       "W ->;" ++
>       "W -> n W;" ++
>       "W -> t W"

> e3ai = "L -> E;"++
>        "L -> S;"++
>        "E ->;" ++
>        "S -> a;" ++
>        "S -> b;" ++
>        "S -> c;" ++
>        "S -> a S;" ++ 
>        "S -> b S;" ++ 
>        "S -> c S" 

-->        "L -> O;"++
-->        "O -> S | S"

> e3aiv = "L ->;" ++
>         "L -> c;" ++
>         "L -> O;" ++
>         "O -> c | c;" ++
>         "O -> c | ( O )"

> e3av = "L -> E;"++
>        "L -> S;"++
>        "E ->;" ++
>        "S -> a;" ++
>        "S -> b;" ++
>        "S -> c;" ++
>        "S -> S a;" ++ 
>        "S -> S b;" ++ 
>        "S -> S c" 

> e3b = "L -> ;" ++
>       "L -> E;" ++
>       "E -> c;" ++
>       "E -> G;" ++
>       "E -> R;" ++
>       "G -> (c);" ++
>       "G -> (c*);"++
>       "R -> c*;" ++
>       "R -> G *"

-->       "G -> ( S );" ++
-->       "E -> S;" ++
-->       "S -> S c" 

-->       "R -> G *;" ++
-->       "G -> ( c );" ++
-->       "E -> A;" ++
-->       "A -> E | A"

> e3b1 = "E -> P | E;" ++
>        "E -> E P;" ++
>        "E -> P *;" ++
>        "E -> P;" ++
>        "P -> A *;" ++
>        "P -> A;" ++
>        "A -> ( E );" ++
>        "A -> c"

> e3b2 = "E -> P | E;" ++
>        "E -> E P;" ++
>        "E -> P;" ++
>        "P -> A *;" ++
>        "P -> A;" ++
>        "A -> ( E );" ++
>        "A -> c"

> e3b3 = "E -> c;"++
>        "E -> R;" ++
>        "E -> P;" ++
>        "R -> P *;" ++
>        "R -> c *;" ++
>        "P -> ( c * );" ++
>        "P -> ( c )"


--------------------------------------------------------------------

The GrammarToolkit defines types Grammar, Prod, Symbol for
representing grammars (no surprise!), productions, and symbols
(which includes both terminals and nonterminals).  It also
provides the following operations:

* start        :: Grammar -> Symbol
  prods        :: Grammar -> [Prod]
  terminals    :: Grammar -> [String]
  nonterminals :: Grammar -> [String]

  Access the components of a grammar.

* readGrammar :: String -> Grammar

  Construct a grammar from a string.

* grammar      :: String -> IO ()
  printGrammar :: Grammar -> IO ()

  Display a grammar.

* derivationTree :: Int -> String -> Pic

  Display a tree with all derivations  

* sentences :: Int -> String -> IO ()
  sentence  :: Int -> String -> IO ()

  Display derivable sentences.

* langSentences :: Int -> String -> IO ()
  langSentence  :: Int -> String -> IO ()

  Display derivable sentences in the language (terminals only).

* parseTrees :: Int -> String -> Pic
  parseTree  :: Int -> String -> Pic

  Display derivable parse trees.

* langTrees :: Int -> String -> Pic
  langTree  :: Int -> String -> Pic

  Display derivable parse trees in the language (terminals only).

* sentenceDerivations :: Int -> String -> IO ()
  sentenceDerivation  :: Int -> String -> IO ()

  Display derivations for all sentences.

* derivationsToLevel :: Int -> String -> IO ()

  Display all the derivations up to length n.

* langDerivations :: Int -> String -> IO ()
  langDerivation  :: Int -> String -> IO ()

  Display derivations for sentences in the language (terminals only).

* treeDerivations :: Int -> String -> Pic
  treeDerivation  :: Int -> String -> Pic

  Display derivations with parse trees.

* treeLangDerivations :: Int -> String -> Pic
  treeLangDerivation  :: Int -> String -> Pic

  Display derivations with parse trees for sentences that only
  contain terminal symbols.

* ambigExamples :: Int -> String -> Pic

  Search for examples of ambiguity in the first n derivations from
  the grammar.

--------------------------------------------------------------------
